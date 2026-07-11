#ifndef _SYSDEPS_H
#define _SYSDEPS_H

#include <sys/types.h>
#include <tlibcnoreturn.h>

#ifndef __TLIBC__
#error "header for internal use only"
#endif

#define SYSDEP __attribute__((visibility("hidden"), weak))

SYSDEP int sys_new_thread(void (*fn)(void*), void *stack, int flags, void *arg, pid_t *child_tid);
SYSDEP TLIBC_NORETURN void sys_thread_exit(void);
SYSDEP int sys_join_thread(pid_t tid, void **arg);
SYSDEP int sys_set_tls(void *tls);

#endif
