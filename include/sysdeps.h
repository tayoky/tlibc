#ifndef _SYSDEPS_H
#define _SYSDEPS_H

#include <sys/types.h>
#include <tlibcnoreturn.h>
#include <stdarg.h>
#include <poll.h>
#include <errno.h>

#ifndef __TLIBC__
#error "header for internal use only"
#endif

#define SYSDEP __attribute__((visibility("hidden"), weak))

#define CALL_SYSDEP(name, args) name ? name args : __set_errno(-ENOSYS)

struct winsize;
struct termios;
struct dirent;

SYSDEP int sys_new_thread(void (*fn)(void*), void *stack, int flags, void *arg, pid_t *child_tid);
SYSDEP TLIBC_NORETURN void sys_thread_exit(void);
SYSDEP int sys_join_thread(pid_t tid, void **arg);
SYSDEP int sys_set_tls(void *tls);

SYSDEP int sys_open(const char *pathname, int flags, mode_t mode);
SYSDEP int sys_openat(int dirfd, const char *pathname, int flags, mode_t mode);
SYSDEP int sys_close(int fd);
SYSDEP ssize_t sys_read(int fd, const void *buffer, size_t count);
SYSDEP ssize_t sys_write(int fd, const void *buffer, size_t count);
SYSDEP off_t sys_lseek(int fd, off_t offset, int whence);
SYSDEP int sys_fcntl(int fd, int op, va_list args);
SYSDEP int sys_ioctl(int fd, unsigned long op, void *arg);
SYSDEP int sys_readdir(int fd, struct dirent *entry, long index);
SYSDEP int sys_isatty(int fd);
SYSDEP int sys_poll(struct pollfd *fds, nfds_t nfds, int timeout);
SYSDEP int sys_link(const char *oldpath, const char *newpath);
SYSDEP int sys_unlink(const char *pathname);
SYSDEP int sys_rename(const char *oldpath, const char *newpath);
SYSDEP int sys_openpty(int *amaster, int *aslave, char *name, const struct termios *termp, const struct winsize *winp);
SYSDEP int sys_ttyname_r(int fd, char *buf, size_t size);


#endif
