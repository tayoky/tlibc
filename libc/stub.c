// we cannot include stdio.h
// cause we might stub stdio functions
#include <errno.h>
typedef struct _FILE FILE;
extern FILE *stderr;
int fprintf(FILE *stream, const char *fmt, ...);

__attribute__((visibility("hidden"))) int __stub(const char *func) {
	fprintf(stderr, "tlibc : %s stub was called\n", func);
	return __set_errno(-ENOSYS);
}


#define STUB(name) \
	__attribute__((weak)) int name() { \
		__stub(#name); \
		return 0; \
	}
#ifndef __DL_TLIBC__
STUB(ftw)
STUB(sync)
STUB(flock)
STUB(utime)
STUB(clock)
STUB(alarm)
STUB(popen)
STUB(pclose)
STUB(sched_yield)
STUB(sched_get_priority_max)
STUB(sched_get_priority_min)

STUB(pthread_detach)
STUB(pthread_rwlock_timedwrlock)
STUB(pthread_rwlock_timedrdlock)
STUB(pthread_setname_np)
STUB(pthread_getname_np)
STUB(pthread_getschedparam)
STUB(pthread_setschedparam)

STUB(open_memstream)

STUB(openlog)
STUB(closelog)
STUB(vsyslog)
STUB(setlogmask)

STUB(__system_property_get)
STUB(__stack_chk_fail)

STUB(__tls_get_addr)
#endif
