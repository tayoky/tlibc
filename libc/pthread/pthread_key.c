#include <errno.h>
#include <limits.h>
#include <pthread.h>

// pthread_key_create and pthread_key_delete need to qccess the same bitmap
// so they are kept in the same file

#define BITS_PER_ENTRY (sizeof(unsigned int) * CHAR_BIT)

static unsigned int bitmap[PTHREAD_KEYS_MAX / BITS_PER_ENTRY];
static void (*destructors[PTHREAD_KEYS_MAX])(void *);

static int allocate_bit(void) {
	for (size_t i = 0; i < sizeof(bitmap) / sizeof(unsigned int); i++) {
		if (bitmap[i] == UINT_MAX) continue;
		for (size_t j = 0; j < BITS_PER_ENTRY; j++) {
			if (bitmap[i] & (1 << j)) continue;
			bitmap[i] |= 1 << j;
			return j + i * BITS_PER_ENTRY;
		}
	}
	return -1;
}

static void free_bit(int bit) {
	bitmap[bit / BITS_PER_ENTRY] &= ~(1 << bit % BITS_PER_ENTRY);
}

int pthread_key_create(pthread_key_t *key, void (*destructor)(void *)) {
	int id = allocate_bit();
	if (id < 0) return EAGAIN;

	*key = id + 1;
	destructors[id] = destructor;
	return 0;
}

int pthread_key_delete(pthread_key_t key) {
	if (key == 0 || key > PTHREAD_KEYS_MAX) {
		return EINVAL;
	}
	free_bit(key - 1);
	// TODO : destroy
	return 0;
}
