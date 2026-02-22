#include <sys/shutdown.h>
#include <syscall.h>
#include <errno.h>

int stanix_shutdown(int flags) {
    return __set_errno(__syscall1(SYS_sys_shutdown, flags));
}
