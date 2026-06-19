#include <stdlib.h>

typedef struct reg {
	void (*func)(void *);
	void *arg;
	void *d;
} reg_t;

static reg_t *regs = NULL;
static size_t reg_count = 0;
static size_t reg_capacity = 0;

int __cxa_atexit(void (*func)(void *), void *arg, void *d) {
	if (reg_count == reg_capacity) {
		reg_capacity = reg_capacity != 0 ? 2 * reg_capacity : 1;
		void *new_regs = realloc(regs, sizeof(reg_t) * reg_capacity);
		if (!new_regs) return -1;
		regs = new_regs;
	}
	regs[reg_count].func = func;
	regs[reg_count].arg = arg;
	regs[reg_count++].d = d;
	return 0;
}

void __cxa_finalize(void *d) {
	for (size_t i = reg_count; i > 0; i--) {
		reg_t *reg = &regs[i - 1];
		if (!reg->func) continue;
		if (d && reg->d != d) continue;
		reg->func(reg->arg);
		reg->func = NULL;
	}
}
