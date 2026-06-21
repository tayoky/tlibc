// we cannot include stdio.h
// cause we might stub stdio functions
typedef struct _FILE FILE;
extern FILE *stderr;
int fprintf(FILE *stream, const char *fmt, ...);


#define STUB(name) \
	int name() { \
		fprintf(stderr, "tlibc : STUB " #name " was called\n"); \
		return 0; \
	}

STUB(ftw)
STUB(flock)
STUB(utime)
STUB(clock)
STUB(alarm)
STUB(popen)
STUB(pclose)
STUB(sched_yield)

STUB(pthread_cond_init)
STUB(pthread_cond_destroy)
STUB(pthread_cond_broadcast)
STUB(pthread_cond_signal)
STUB(pthread_cond_timedwait)
STUB(pthread_cond_wait)
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
