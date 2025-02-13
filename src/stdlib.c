#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

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
	uint64_t start;
	uint64_t lenght;
	heap_segment *first_seg;
}heap_info;

heap_info heap;

#define INITIAL_HEAP_SIZE 4096
#define HEAP_SEG_MAGIC_FREE      0x1308
#define HEAP_SEG_MAGIC_ALLOCATED 0x0505


void init_heap(void){
	//get the heap start and initial size
	heap.start = sbrk(INITIAL_HEAP_SIZE);
	heap.lenght = INITIAL_HEAP_SIZE;

	//init the first seg
	heap.first_seg = (heap_segment *)heap.start;
	heap.first_seg->magic = HEAP_SEG_MAGIC_FREE;
	heap.first_seg->lenght = heap.lenght - sizeof(heap_segment);
	heap.first_seg->prev = NULL;
	heap.first_seg->next = NULL;
}

void *malloc(size_t amount){
	heap_segment *current_seg = heap.first_seg;

	while (current_seg->lenght < amount || current_seg->magic != HEAP_SEG_MAGIC_FREE){
		if(current_seg->next == NULL){
			//no more segment need to make kheap bigger
			uint64_t old_heap_size = sbrk(amount - current_seg->lenght + sizeof(heap_segment) + 1);
			current_seg->lenght += sbrk(0) - old_heap_size;
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