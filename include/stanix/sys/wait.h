#ifndef SYS_WAIT_H
#define SYS_WAIT_H

#include <sys/types.h>

#define WNOHANG 0x01

#define WIFEXITED(status)   (status & (1UL << 16))
#define WIFSIGNALED(status) (status & (1UL << 17))
#define WCOREDUMP(status)   (status & (1UL << 18))
#define WIFSTOPPED(status)  (status & (1UL << 19))

#define WEXITSTATUS(status) (status & 0xFFFF)
#define WTERMSIG WEXITSTATUS
#define WSTOPSIG WEXITSTATUS

pid_t waitpid(pid_t pid, int *status, int options);
pid_t wait(int *status);

#endif
