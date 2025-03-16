#ifndef SYS_WAIT_H
#define SYS_WAIT_H

#include <sys/types.h>

#define WIFEXITED(status)   status & ((uint64_t)1 << 32)
#define WIFSIGNALED(status) status & ((uint64_t)1 << 33)
#define WCOREDUMP(status)   status & ((uint64_t)1 << 34)
#define WIFSTOPPED(status)  status & ((uint64_t)1 << 35)

#define WEXITSTATUS(status) status & 0xFFFFFFFF
#define WTERMSIG WEXITSTATUS
#define WSTOPSIG WEXITSTATUS

pid_t waitpid(pid_t pid, int *status, int options);
pid_t wait(int *status);

#endif