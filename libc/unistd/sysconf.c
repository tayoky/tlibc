#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>

long sysconf(int name) {
	switch (name) {
	case _SC_ARG_MAX:
		return ARG_MAX;
	case _SC_CHILD_MAX:
		return CHILD_MAX;
	case _SC_OPEN_MAX:
		return OPEN_MAX;
	case _SC_PAGESIZE:
		return PAGESIZE;
	case _SC_SYMLOOP_MAX:
		return SYMLOOP_MAX;
	case _SC_LINE_MAX:
		return LINE_MAX;
	case _SC_GETPW_R_SIZE_MAX:
		return 4096;
	default:
		if (name <= 250) {
			fprintf(stderr, "tlibc : unimplemented sysconf for %d\n", name);
		}
		return __set_errno(-EINVAL);
	}
}
