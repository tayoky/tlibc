#ifndef SYS_WAIT_H
#define SYS_WAIT_H

#include <sys/types.h>

#define WIFEXITED(status)   (status & (1UL << 32))
#define WIFSIGNALED(status) (status & (1UL << 33))
#define WCOREDUMP(status)   (status & (1UL << 34))
#define WIFSTOPPED(status)  (status & (1UL << 35))

#define WEXITSTATUS(status) (status & 0xFFFFFFFF)
#define WTERMSIG WEXITSTATUS
#define WSTOPSIG WEXITSTATUS

pid_t waitpid(pid_t pid, int *status, int options);
pid_t wait(int *status);

#endif
