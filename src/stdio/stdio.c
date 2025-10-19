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

FILE *stdin = &_stdin;
FILE *stdout = &_stdout;
FILE *stderr = &_stderr;

FILE *__streams = NULL;
