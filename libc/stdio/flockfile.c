#include <stdio-internal.h>
#include <sysdeps.h>
#include <tlibc.h>

void flockfile(FILE *filehandle) {
	pid_t tid = __get_uthread()->tid;
	for (;;) {
		futex_val_t expected = 0;
		if (atomic_compare_exchange_strong(&filehandle->thread, &expected, (futex_val_t)tid)) {
			// we acquired the lock !
			filehandle->lock_count = 1;
			return;
		}
		// maybee we already own it
		if (expected == (futex_val_t)tid) {
			filehandle->lock_count++;
			return;
		}
		if (sys_futex_wait(&filehandle->thread, expected) < 0 && errno != EAGAIN);
	}
}
