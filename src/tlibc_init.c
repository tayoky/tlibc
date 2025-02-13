#include <stdint.h>

void init_heap(void);

void __tlibc_init(int argc){
	init_heap();
}