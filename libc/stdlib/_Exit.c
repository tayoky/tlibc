#include <stdlib.h>
#include <tlibcnoreturn.h>
#include <unistd.h>

TLIBC_NORETURN void _Exit(int status) {
	_exit(status);
}
