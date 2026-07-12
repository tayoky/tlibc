#ifndef _SYSDEPS_H
#define _SYSDEPS_H

#include <sys/types.h>
#include <tlibcnoreturn.h>
#include <stdarg.h>
#include <errno.h>

#ifndef __TLIBC__
#error "header for internal use only"
#endif

#define SYSDEP __attribute__((visibility("hidden"), weak))

#define CALL_SYSDEP(name, args) name ? name args : __set_errno(-ENOSYS)

SYSDEP int sys_new_thread(void (*fn)(void*), void *stack, int flags, void *arg, pid_t *child_tid);
SYSDEP TLIBC_NORETURN void sys_thread_exit(void);
SYSDEP int sys_join_thread(pid_t tid, void **arg);
SYSDEP int sys_set_tls(void *tls);

SYSDEP int sys_open(const char *pathname, int flags, mode_t mode);
SYSDEP int sys_openat(int dirfd, const char *pathname, int flags, mode_t mode);
SYSDEP int sys_fcntl(int fd, int op, va_list args);


#endif
