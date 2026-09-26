#include <stdio-internal.h>
#include <sysdeps.h>
#include <assert.h>
#include <tlibc.h>

void funlockfile(FILE *filehandle) {
	assert(filehandle->thread == (futex_val_t)__get_uthread()->tid);
	filehandle->lock_count--;
	if (filehandle->lock_count == 0) {
		atomic_store(&filehandle->thread, 0);
		sys_futex_wake(&filehandle->thread, 1);
	}
}
