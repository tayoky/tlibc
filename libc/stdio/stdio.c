#include <stdio.h>

static FILE _stdin = {
	.fd = 0,
	.error = 0,
	.eof = 0,
	.unget = EOF,
};
static FILE _stdout = {
	.fd = 1,
	.error = 0,
	.eof = 0,
	.unget = EOF,
};
static FILE _stderr = {
	.fd = 2,
	.error = 0,
	.eof = 0,
	.unget = EOF,
	.buftype = _IONBF,
};

#ifdef __DL_TLIBC__
// we need to avoid pointer in data section
// because dynamic linker cannot have reloc

FILE *stdin;
FILE *stdout;
FILE *stderr;

void __init_stdio(void) {
	stdin  = &_stdin;
	stdout = &_stdout;
	stderr = &_stderr;
}

#else
FILE *stdin  = &_stdin;
FILE *stdout = &_stdout;
FILE *stderr = &_stderr;
#endif

FILE *__streams = NULL;
