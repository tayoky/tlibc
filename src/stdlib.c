#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <errno.h>
#include <limits.h>

static char *brk_ptr = (char *)0xFF0000000;
static void (*atexit_funcs[64])(void);
static int atexit_count = 0;

int atexit(void (*func)(void)){
	if(atexit_count >= 64){
		return -1;
	}
	atexit_funcs[atexit_count] = func;
	atexit_count++;
	return 0;
}

void exit(int status){
	for(int i=atexit_count-1; i>=0; i--){
		atexit_funcs[i]();
	}
	_exit(status);
}

void _Exit(int status){
	_exit(status);
}

typedef struct heap_segment_struct{
	uint64_t magic;
	uint64_t lenght;
	struct heap_segment_struct *next;
	struct heap_segment_struct *prev;
}heap_segment;

typedef struct {
	uintptr_t start;
	uintptr_t lenght;
	heap_segment *first_seg;
}heap_info;

heap_info heap;

#define PAGE_SIZE 4096
#define PAGE_ALIGN_UP(x) (((x) + PAGE_SIZE - 1) / PAGE_SIZE * PAGE_SIZE)
#define HEAP_SEG_MAGIC_FREE      0x1308
#define HEAP_SEG_MAGIC_ALLOCATED 0x0505


void __init_heap(void){
	//get the heap start and initial size
	heap.start = (uintptr_t)brk_ptr;
	mmap(brk_ptr,PAGE_SIZE,PROT_WRITE | PROT_READ,MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED,0,0);
	brk_ptr += PAGE_SIZE;
	heap.lenght = PAGE_SIZE;

	//init the first seg
	heap.first_seg = (heap_segment *)heap.start;
	heap.first_seg->magic = HEAP_SEG_MAGIC_FREE;
	heap.first_seg->lenght = heap.lenght - sizeof(heap_segment);
	heap.first_seg->prev = NULL;
	heap.first_seg->next = NULL;
}

void *malloc(size_t amount){
	if(!amount){
		return NULL;
	}
	//align amount
	if(amount & 0b111){
		amount += 8 - (amount & 0b111);
	}
	heap_segment *current_seg = heap.first_seg;

	while (current_seg->lenght < amount || current_seg->magic != HEAP_SEG_MAGIC_FREE){
		if(current_seg->next == NULL){
			//no more segment need to make heap bigger
			//if last is free make it bigger else create a new seg from scratch
			if(current_seg->magic == HEAP_SEG_MAGIC_FREE){
				mmap(brk_ptr,PAGE_ALIGN_UP(amount - current_seg->lenght + sizeof(heap_segment) + 8),PROT_WRITE | PROT_READ,MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED,0,0);
				brk_ptr += PAGE_ALIGN_UP(amount - current_seg->lenght + sizeof(heap_segment) + 8);
				current_seg->lenght += PAGE_ALIGN_UP(amount - current_seg->lenght + sizeof(heap_segment) + 8);
			} else {
				mmap(brk_ptr,PAGE_ALIGN_UP(amount + sizeof(heap_segment) * 2  + 8),PROT_WRITE | PROT_READ,MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED,0,0);
				brk_ptr += PAGE_ALIGN_UP(amount + sizeof(heap_segment) * 2  + 8);
				heap_segment *new_seg = (heap_segment *)((uintptr_t)current_seg + current_seg->lenght + sizeof(heap_segment));
				new_seg->lenght = PAGE_ALIGN_UP(amount + sizeof(heap_segment) * 2  + 8) - sizeof(heap_segment);
				new_seg->magic = HEAP_SEG_MAGIC_FREE;
				new_seg->next = NULL;
				new_seg->prev = current_seg;
				current_seg->next = new_seg;
				current_seg = current_seg->next;
			}
			break;
		}
		current_seg = current_seg->next;
	}

	//we find a good segment

	//if big enougth cut it
	if(current_seg->lenght >= amount + sizeof(heap_segment) + 8){
		//big enougth
		heap_segment *new_seg = (heap_segment *)((uint64_t)current_seg + amount + sizeof(heap_segment));
		new_seg->lenght = current_seg->lenght - (sizeof(heap_segment) + amount);
		current_seg->lenght = amount;
		new_seg->magic = HEAP_SEG_MAGIC_FREE;

		if(current_seg->next){
			current_seg->next->prev = new_seg;
		}
		new_seg->next = current_seg->next;
		new_seg->prev = current_seg;
		current_seg->next = new_seg;
	}

	current_seg->magic = HEAP_SEG_MAGIC_ALLOCATED;
	return (void *)current_seg + sizeof(heap_segment);
}

void free(void *ptr){
	if(!ptr)return;
	
	heap_segment *current_seg = (heap_segment *)((uintptr_t)ptr - sizeof(heap_segment));
	if(current_seg->magic != HEAP_SEG_MAGIC_ALLOCATED)return;

	current_seg->magic = HEAP_SEG_MAGIC_FREE;

	if(current_seg->next && current_seg->next->magic == HEAP_SEG_MAGIC_FREE){
		//merge with next
		current_seg->lenght += current_seg->next->lenght + sizeof(heap_segment);

		if(current_seg->next->next){
			current_seg->next->next->prev = current_seg;
		}
		current_seg->next = current_seg->next->next;
	}

	if(current_seg->prev && current_seg->prev->magic == HEAP_SEG_MAGIC_FREE){
		//merge with prev
		current_seg->prev->lenght += current_seg->lenght + sizeof(heap_segment);

		if(current_seg->next){
			current_seg->next->prev = current_seg->prev;
		}
		current_seg->prev->next = current_seg->next;
	}
}

void *calloc(size_t num,size_t size){
	size *= num;
	void *buf = malloc(size);
	memset(buf,0,size);
	return buf;
}

void *realloc(void *ptr,size_t new_size){
	if(!ptr){
		return malloc(new_size);
	}
	if(!new_size){
		free(ptr);
		return NULL;
	}
	void *new_buf = malloc(new_size);
	if(!new_buf){
		return NULL;
	}

	size_t old_size = ((heap_segment*)((uintptr_t)ptr - sizeof(heap_segment)))->lenght;

	if(new_size > old_size){
		memcpy(new_buf,ptr,old_size);
	} else {
		memcpy(new_buf,ptr,new_size);
	}
	free(ptr);
	return new_buf;
}

void abort(void){
	return exit(EXIT_FAILURE);
}


int system(const char *command){
	char *shell = getenv("SHELL");
	if(!shell){
		shell = "/bin/sh";
	}
	if(command == NULL){
		//check if a shell is availible
		return system("echo test") == 0;
	} else {
		pid_t child = fork();
		if(!child){
			char *argv[] = {
				shell,
				"-c",
				(char *)command,
				NULL
			};
			execvp(shell,(const char * const*)argv);
			//pass errno trought the parent
			exit(127 + errno);
		}
		if(child < 0){
			return -1;
		}
		int status = 0;
		waitpid(child,&status,0);
		if(WEXITSTATUS(status) > 127){
			errno = WEXITSTATUS(status) - 127;
			return -1;
		}
		return WEXITSTATUS(status);
	}
}

#define xabs(type,name) type name(type x){\
	type mask = x >> ((sizeof(type) * CHAR_BIT) - 1);\
	return (x^mask) - mask;\
}

xabs(int,abs)
xabs(long,labs)
xabs(long long,llabs)
