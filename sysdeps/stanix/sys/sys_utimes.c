#include <sys/time.h>
#include <sysdeps.h>
#include <errno.h>
#include <syscall.h>

int utimes(const char *filename, const struct timeval times[2]) {
    return __set_errno(__syscall2(SYS_utimes, (long)filename, (long)times));
}
