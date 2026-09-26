#include <stdio-internal.h>
#include <sysdeps.h>
#include <tlibc.h>

int ftrylockfile(FILE *filehandle) {
	pid_t tid = __get_uthread()->tid;
	futex_val_t expected = 0;
	if (atomic_compare_exchange_strong(&filehandle->thread, &expected, (futex_val_t)tid)) {
		filehandle->lock_count = 1;
		return 0;
	} else if (expected == tid) {
		filehandle->lock_count++;
		return 0;
	} else {
		return 1;
	}
}
