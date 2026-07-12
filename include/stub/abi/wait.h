#ifndef _ABI_WAIT_H
#define _ABI_WAIT_H

// Stub wait ABI

#define WNOHANG 0x01

#define WIFEXITED(status)   (status & (1UL << 16))
#define WIFSIGNALED(status) (status & (1UL << 17))
#define WCOREDUMP(status)   (status & (1UL << 18))
#define WIFSTOPPED(status)  (status & (1UL << 19))

#define WEXITSTATUS(status) (status & 0xFFFF)
#define WTERMSIG WEXITSTATUS
#define WSTOPSIG WEXITSTATUS

#endif
