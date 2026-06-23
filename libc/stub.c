// we cannot include stdio.h
// cause we might stub stdio functions
typedef struct _FILE FILE;
extern FILE *stderr;
int fprintf(FILE *stream, const char *fmt, ...);


#define STUB(name) \
	__attribute__((weak)) int name() { \
		fprintf(stderr, "tlibc : " #name " stub was called\n"); \
		return 0; \
	}

STUB(ftw)
STUB(sync)
STUB(flock)
STUB(utime)
STUB(fstatat)
STUB(clock)
STUB(alarm)
STUB(popen)
STUB(pclose)
STUB(sched_yield)

STUB(pthread_cond_timedwait)
STUB(pthread_detach)
STUB(pthread_cancel)
STUB(pthread_rwlock_timedwrlock)
STUB(pthread_rwlock_timedrdlock)
STUB(pthread_setname_np)
STUB(pthread_getname_np)

STUB(open_memstream)

STUB(openlog)
STUB(closelog)
STUB(vsyslog)
STUB(setlogmask)

STUB(__tls_get_addr)
