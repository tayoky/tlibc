#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

void exit(int status){
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

#define INITIAL_HEAP_SIZE 4096
#define HEAP_SEG_MAGIC_FREE      0x1308
#define HEAP_SEG_MAGIC_ALLOCATED 0x0505


void __init_heap(void){
	//get the heap start and initial size
	heap.start = (uintptr_t)sbrk(INITIAL_HEAP_SIZE);
	heap.lenght = INITIAL_HEAP_SIZE;

	//init the first seg
	heap.first_seg = (heap_segment *)heap.start;
	heap.first_seg->magic = HEAP_SEG_MAGIC_FREE;
	heap.first_seg->lenght = heap.lenght - sizeof(heap_segment);
	heap.first_seg->prev = NULL;
	heap.first_seg->next = NULL;
}

void *malloc(size_t amount){
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
				uintptr_t old_heap_size = (uintptr_t)sbrk(amount - current_seg->lenght + sizeof(heap_segment) + 1);
				current_seg->lenght += (uintptr_t)sbrk(0) - old_heap_size;
			} else {
				uintptr_t old_heap_size = (uintptr_t)sbrk(amount + sizeof(heap_segment) * 2  + 8);
				heap_segment *new_seg = (heap_segment *)((uintptr_t)current_seg + current_seg->lenght + sizeof(heap_segment));
				new_seg->lenght = (uintptr_t)sbrk(0) - old_heap_size - sizeof(heap_segment);
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
	if(current_seg->lenght >= amount + sizeof(heap_segment) + 1){
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