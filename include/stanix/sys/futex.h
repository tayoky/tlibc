#include <sys/types.h>

#define FUTEX_WAIT 1
#define FUTEX_WAKE 2

int futex(long *addr, int op, long val);
