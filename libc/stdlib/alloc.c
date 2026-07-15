#include <sys/mman.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>

struct bin;

struct node {
	struct node *next;
};

struct slab {
	struct slab *next;
	struct slab *prev;
	struct node *free;
	struct bin *bin;
	size_t allocated_count;
	int state;
};

#define SLAB_NULL    0
#define SLAB_FREE    1
#define SLAB_PARTIAL 2
#define SLAB_FULL    3

struct bin {
	size_t size;
	struct slab *full;
	struct slab *partial;
	struct slab *free;
};

struct alloc {
	// size is actually a block ptr for aligned allocs
	// it is unsafe to touch size before checking slab is non NULL
	size_t size;
	struct slab *slab;
};

#define ALLOC_ALIGNED 0x1

#define PAGE_ALIGN_UP(x) ((((x) + PAGE_SIZE - 1) / PAGE_SIZE) * PAGE_SIZE)

#define BIN_SIZES_COUNT 8
#define SLAB_SIZE 8192
#define BIN(n) {.size = n, .full = NULL, .partial = NULL, .free = NULL}
static struct bin bins[BIN_SIZES_COUNT] = {
	BIN(16),
	BIN(32),
	BIN(64),
	BIN(96),
	BIN(128),
	BIN(256),
	BIN(512),
	BIN(1024),
};

static struct alloc *get_alloc(void *ptr) {
	struct alloc *alloc = ptr;
	alloc--;
	return alloc;
}

static struct bin *get_bin(size_t size) {
	for (size_t i=0; i<BIN_SIZES_COUNT; i++) {
		if (size <= bins[i].size) {
			return &bins[i];
		}
	}
	return NULL;
}

static void *slab_allocate(struct slab *slab) {
	if (!slab || !slab->free) return NULL;
	slab->allocated_count++;
	struct node *node = slab->free;
	slab->free = node->next;

	// we need to store the slab ptr before the node
	struct alloc *alloc = get_alloc(node);
	alloc->slab = slab;
	return node;
}

static void slab_free(struct slab *slab, void *ptr) {
	slab->allocated_count--;
	struct node *node = ptr;
	node->next = slab->free;
	slab->free = node;
}

static size_t align_size(size_t size) {
	if (size % 16) {
		size += 16 - (size % 16);
	}
	return size;
}

static struct slab *slab_new(struct bin *bin) {
	struct slab *slab = mmap(NULL, SLAB_SIZE, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, 0, 0);
	if (slab == MAP_FAILED) return NULL;
	memset(slab, 0, sizeof(struct slab));
	slab->bin = bin;
	
	// we need to make space between each element of the slab
	// to put the slab pointer
	// note that we reserve space for the pointer but it is set in slab_allocate
	for (uintptr_t addr=align_size(sizeof(struct slab)+sizeof(struct slab*)); addr+bin->size<=SLAB_SIZE; addr += align_size(bin->size + sizeof(struct slab *))) {
		struct node *node = (struct node *)(((char*)slab) + addr);
		node->next = slab->free;
		slab->free = node;
	}
	
	return slab;
}

static void slab_remove_from(struct slab *slab, struct slab **list) {
	if (slab->prev) {
		slab->prev->next = slab->next;
	} else {
		*list = slab->next;
	}
	if (slab->next) {
		slab->next->prev = slab->prev;
	}
}

static void slab_add_to(struct slab *slab, struct slab **list) {
	slab->prev = NULL;
	slab->next = *list;
	if (*list) {
		(*list)->prev = slab;
	}
	*list = slab;
}

static void slab_move(struct bin *bin, struct slab *slab, int state) {
	switch (slab->state) {
	case SLAB_FREE:
		slab_remove_from(slab, &bin->free);
		break;
	case SLAB_PARTIAL:
		slab_remove_from(slab, &bin->partial);
		break;
	case SLAB_FULL:
		slab_remove_from(slab, &bin->full);
		break;
	}
	slab->state = state;
	switch (slab->state) {
	case SLAB_FREE:
		slab_add_to(slab, &bin->free);
		break;
	case SLAB_PARTIAL:
		slab_add_to(slab, &bin->partial);
		break;
	case SLAB_FULL:
		slab_add_to(slab, &bin->full);
		break;
	}
}

static void *bin_allocate(struct bin *bin) {
	void *ptr = slab_allocate(bin->partial);
	if (ptr) {
		if (!bin->partial->free) {
			// it's full now
			slab_move(bin, bin->partial, SLAB_FULL);
		}
		return ptr;
	}
	ptr = slab_allocate(bin->free);
	if (ptr) {
		// it's not free anymore
		slab_move(bin, bin->free, SLAB_PARTIAL);
		return ptr;
	}

	// we need to allocate a new slab
	struct slab *slab = slab_new(bin);
	if (!slab) return NULL;
	slab_move(bin, slab, SLAB_PARTIAL);
	return slab_allocate(slab);
}

static void bin_free(struct slab *slab, void *ptr) {
	struct bin *bin = slab->bin;
	slab_free(slab, ptr);
	if (slab->state == SLAB_FULL) {
		// it's not full anymore
		slab_move(bin, slab, SLAB_PARTIAL);
	}
	if (slab->allocated_count == 0) {
		// it's free now
		// TODO : use madvice to set as free
		slab_move(bin, slab, SLAB_FREE);
	}
}

static void *big_allocate(size_t size) {
	size_t alloc_size = PAGE_ALIGN_UP(size + sizeof(struct alloc));
	struct alloc *alloc = mmap(NULL, alloc_size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, 0, 0);
	if (alloc == MAP_FAILED) return NULL;

	// big allocations have a NULL slab ptr
	alloc->slab = NULL;
	alloc->size = alloc_size - sizeof(struct alloc);
	return alloc + 1;
}

static void big_free(struct alloc *alloc) {
	munmap(alloc, alloc->size + sizeof(struct alloc));
}

static void *aligned_get_block(struct alloc *alloc) {
		// in aligned allocations we use size to store ptr to original block
	return (void*)(alloc->size & ~ALLOC_ALIGNED);
}

static void aligned_free(struct alloc *alloc) {
	void *ptr = aligned_get_block(alloc);
	free(ptr);
}

size_t alloc_get_size(struct alloc *alloc) {
	if (alloc->slab) {
		return alloc->slab->bin->size;
	} else if (alloc->size & ALLOC_ALIGNED) {
		// we need to deduce size from the size
		// of the block
		void *block = aligned_get_block(alloc);
		struct alloc *block_alloc = get_alloc(block);
		size_t block_size = alloc_get_size(block_alloc);
		size_t offset = (uintptr_t)alloc - (uintptr_t)block_alloc;
		return block_size - offset;
	} else {
		return alloc->size;
	}
}

void *malloc(size_t size) {
	if (size == 0) return NULL;
	struct bin *bin = get_bin(size);
	if (bin) {
		return bin_allocate(bin);
	} else {
		return big_allocate(size);
	}
}

void free(void *ptr) {
	if (!ptr) return;
	struct alloc *alloc = get_alloc(ptr);
	if (alloc->slab) {
		bin_free(alloc->slab, ptr);
	} else if (alloc->size & ALLOC_ALIGNED) {
		aligned_free(alloc);
	} else {
		big_free(alloc);
	}
}

void *realloc(void *ptr, size_t newsize) {
	if (!ptr) return malloc(newsize);
	if (newsize == 0) {
		free(ptr);
		return NULL;
	}

	struct alloc *alloc = get_alloc(ptr);
	size_t old_size = alloc_get_size(alloc);
	if (old_size >= newsize) {
		// we could decrease size
		// but who care
		return ptr;
	}

	// note that we do not have to guarantee alignment anymore
	// for aligned allocations
	
	void *new_ptr = malloc(newsize);
	if (!new_ptr) return NULL;
	memcpy(new_ptr, ptr, old_size);
	free(ptr);
	return new_ptr;
}

int posix_memalign(void **memptr, size_t alignment, size_t size) {
	if (alignment % sizeof(void *) != 0 || (alignment & (alignment - 1)) != 0) return EINVAL;
	if (size == 0) {
		*memptr = NULL;
		return 0;
	}

	if (alignment <= 16) {
		// malloc already guarantee 16 bytes alignment
		void *ptr = malloc(size);
		if (!ptr) return errno;
		*memptr = ptr;
		return 0;
	}

	size_t total_size = alignment + size;
	void *ptr = malloc(total_size);
	if (!ptr) return errno;
	uintptr_t addr = (uintptr_t)ptr;
	if (addr % alignment != 0) {
		// we need to align
		addr += alignment - (addr % alignment);
		struct alloc *alloc = get_alloc((void*)addr);
		alloc->slab = NULL;
		// in aligned allocs we use size to store real size
		alloc->size = ALLOC_ALIGNED | (uintptr_t)ptr;
		ptr = (void*)addr;
	}
	*memptr = ptr;
	return 0;
}
