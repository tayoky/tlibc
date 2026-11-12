#include <string.h>

void *memset(void *pointer, int value, size_t count) {
	unsigned char *ptr = pointer;
	while (count > 0) {
		*ptr = (unsigned char)value;
		ptr++;
		count--;
	}

	return pointer;
}
