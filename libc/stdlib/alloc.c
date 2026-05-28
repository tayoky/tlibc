#include <sys/mman.h>
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

struct big_alloc {
	size_t size;
	// we need to keep the slab ptr last
	// to fake a NULL  slab ptr
	struct slab *slab_ptr;
};

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

static struct bin *get_bin(size_t size) {
	for (size_t i=0; i<BIN_SIZES_COUNT; i++) {
		if (size <= bins[i].size) {
			return &bins[i];
		}
	}
	return NULL;
}

static struct slab *get_slab(void *ptr) {
	struct slab **slab_ptr = ptr;
	slab_ptr--;
	return *slab_ptr;
}

static void *slab_allocate(struct slab *slab) {
	if (!slab || !slab->free) return NULL;
	slab->allocated_count++;
	struct node *node = slab->free;
	slab->free = node->next;

	// we need to store the slab ptr before the node
	struct slab **slab_ptr = (struct slab **)node;
	slab_ptr--;
	*slab_ptr = slab;
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

static struct big_alloc *get_big(void *ptr) {
	struct big_alloc *alloc = ptr;
	alloc--;
	return alloc;
}

static void *big_allocate(size_t size) {
	size_t alloc_size = PAGE_ALIGN_UP(size + sizeof(struct big_alloc));
	struct big_alloc *alloc = mmap(NULL, alloc_size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, 0, 0);
	if (alloc == MAP_FAILED) return NULL;

	// allocations have a NULL slab ptr
	alloc->slab_ptr = NULL;
	alloc->size = alloc_size - sizeof(struct big_alloc);
	return alloc + 1;
}

static void big_free(void *ptr) {
	struct big_alloc *alloc = get_big(ptr);
	munmap(alloc, alloc->size + sizeof(struct big_alloc));
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
	struct slab *slab = get_slab(ptr);
	if (slab) {
		bin_free(slab, ptr);
	} else {
		big_free(ptr);
	}
}

void *realloc(void *ptr, size_t newsize) {
	if (!ptr) return malloc(newsize);
	if (newsize == 0) {
		free(ptr);
		return NULL;
	}

	struct slab *slab = get_slab(ptr);
	if (slab) {
		struct bin *bin = slab->bin;
		if (bin->size >= newsize) {
			// we could decrease size
			// but who care
			return ptr;
		}
		void *new_ptr = malloc(newsize);
		if (!new_ptr) return NULL;
		memcpy(new_ptr, ptr, bin->size);
		slab_free(slab, ptr);
		return new_ptr;
	} else {
		// big alloc
		struct big_alloc *alloc = get_big(ptr);
		if (alloc->size >= newsize) {
			// we could decrease size
			// but who care
			return ptr;
		}

		void *new_ptr = malloc(newsize);
		if (!new_ptr) return NULL;
		memcpy(new_ptr, ptr, alloc->size);
		big_free(ptr);
		return new_ptr;
	}
}
