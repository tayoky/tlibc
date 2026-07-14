#ifndef _SYSDEPS_H
#define _SYSDEPS_H

#include <abi/futex.h>
#include <abi/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <tlibcnoreturn.h>
#include <stdarg.h>
#include <poll.h>
#include <signal.h>
#include <errno.h>

#ifndef __TLIBC__
#error "header for internal use only"
#endif

#define TLIBC_WEAK __attribute__((weak))
#define SYSDEP __attribute__((visibility("hidden")))

//#define CALL_SYSDEP(name, args) name ? name args : __set_errno(-ENOSYS)

struct winsize;
struct termios;
struct dirent;
struct stat;

typedef TLIBC_FUTEX_TYPE futex_val_t;
typedef _Atomic(TLIBC_FUTEX_TYPE) futex_atomic_t;

SYSDEP pid_t sys_gettid(void);
SYSDEP int sys_new_thread(void (*fn)(void*), void *stack, int flags, void *arg, pid_t *child_tid);
SYSDEP TLIBC_NORETURN void sys_thread_exit(void);
SYSDEP int sys_join_thread(pid_t tid, void **arg);
SYSDEP int sys_futex_wait(futex_atomic_t *addr, futex_val_t val);
SYSDEP int sys_futex_wake(futex_atomic_t *addr, int count);
SYSDEP void *sys_arch_get_tls(void);
SYSDEP int sys_set_tls(void *tls);
SYSDEP void *sys_get_tls(void);
SYSDEP int sys_stat(const char *pathname, struct stat *st);
SYSDEP int sys_lstat(const char *pathname, struct stat *st);
SYSDEP int sys_fstat(int fd, struct stat *st);
SYSDEP int sys_fstatat(int fd, const char *restrict path, struct stat *restrict st, int flags);
SYSDEP int sys_chmod(const char *pathname, mode_t mode);
SYSDEP int sys_lchmod(const char *pathname, mode_t mode);
SYSDEP int sys_fchmod(int fd, mode_t mode);
SYSDEP int sys_chown(const char *pathname, uid_t owner, gid_t group);
SYSDEP int sys_lchown(const char *pathname, uid_t owner, gid_t group);
SYSDEP int sys_fchown(int fd, uid_t owner, gid_t group);
SYSDEP int sys_link(const char *oldpath, const char *newpath);
SYSDEP int sys_unlink(const char *pathname);
SYSDEP int sys_rmdir(const char *pathname);
SYSDEP int sys_rename(const char *oldpath, const char *newpath);
SYSDEP int sys_mkdir(const char *pathname, mode_t mode);
SYSDEP int sys_mknod(const char *pathname, mode_t mode, dev_t dev);
SYSDEP int sys_getcwd(char *buf, size_t size);
SYSDEP int sys_open(const char *pathname, int flags, mode_t mode);
SYSDEP int sys_openat(int dirfd, const char *pathname, int flags, mode_t mode);
SYSDEP int sys_close(int fd);
SYSDEP ssize_t sys_read(int fd, const void *buffer, size_t count);
SYSDEP ssize_t sys_write(int fd, const void *buffer, size_t count);
SYSDEP off_t sys_lseek(int fd, off_t offset, int whence);
SYSDEP int sys_fcntl(int fd, int op, va_list args);
SYSDEP int sys_ioctl(int fd, unsigned long op, void *arg);
SYSDEP int sys_readdir(int fd, struct dirent *entry, long index);

SYSDEP int sys_socket(int domain, int type, int protocol);
SYSDEP int sys_bind(int socket, const struct sockaddr *address, socklen_t address_len);
SYSDEP int sys_listen(int socket, int backlog);
SYSDEP int sys_accept(int socket, struct sockaddr *address, socklen_t *address_len);
SYSDEP int sys_connect(int socket, const struct sockaddr *address, socklen_t address_len);
SYSDEP ssize_t sys_recvmsg(int socket, struct msghdr *message, int flags);
SYSDEP ssize_t sys_sendmsg(int socket, const struct msghdr *message, int flags);
SYSDEP int sys_getpeername(int socket, struct sockaddr *address, socklen_t *address_len);
SYSDEP int sys_getsockname(int socket, struct sockaddr *address, socklen_t *address_len);
SYSDEP int sys_getsockopt(int socket, int level, int option_name, void *option_value, socklen_t *option_len);
SYSDEP int sys_setsockopt(int socket, int level, int option_name, const void *option_value, socklen_t option_len);
SYSDEP int sys_shutdown(int socket, int how);

SYSDEP int sys_isatty(int fd);
SYSDEP int sys_poll(struct pollfd *fds, nfds_t nfds, int timeout);
SYSDEP int sys_openpty(int *amaster, int *aslave, char *name, const struct termios *termp, const struct winsize *winp);
SYSDEP int sys_ttyname_r(int fd, char *buf, size_t size);
SYSDEP void *sys_mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
SYSDEP int sys_munmap(void *addr, size_t length);
SYSDEP int sys_mprotect(void *addr, size_t size, int prot);
SYSDEP pid_t sys_getpid(void);
SYSDEP pid_t sys_getpgid(pid_t pid);
SYSDEP int sys_setpgid(pid_t pid, pid_t pgid);
SYSDEP pid_t sys_fork(void);
SYSDEP int sys_execve(const char *pathname, char *const *argv, char *const *envp);
SYSDEP TLIBC_NORETURN void sys_exit(int status);
SYSDEP pid_t sys_waitpid(pid_t pid, int *status, int options);
SYSDEP int sys_clock_gettime(clockid_t clockid, struct timespec *tp);
SYSDEP int sys_clock_settime(clockid_t clockid, const struct timespec *tp);
SYSDEP int sys_usleep(useconds_t usec);
SYSDEP int sys_nanosleep(const struct timespec *duration, struct timespec *rem);

SYSDEP sighandler_t sys_signal(int signum, sighandler_t handler);
SYSDEP int sys_sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
SYSDEP int sys_kill(pid_t pid, int sig);
SYSDEP int sys_sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
SYSDEP int sys_sigpending(sigset_t *set);
SYSDEP int sys_sigsuspend(const sigset_t *mask);
SYSDEP int sys_sigwait(const sigset_t *set, int *sig);

// user management
SYSDEP uid_t sys_getuid(void);
SYSDEP uid_t sys_geteuid(void);
SYSDEP gid_t sys_getgid(void);
SYSDEP gid_t sys_getegid(void);
SYSDEP int sys_setuid(uid_t uid);
SYSDEP int sys_seteuid(uid_t uid);
SYSDEP int sys_setgid(gid_t gid);
SYSDEP int sys_setegid(gid_t gid);

#endif
