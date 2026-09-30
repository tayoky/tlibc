#ifndef _SYS_MMAN_H
#define _SYS_MMAN_H

#include <features.h>
#include <sys/types.h>
#include <abi/mman.h>

#define MAP_FAILED (void *)-1

void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
int munmap(void *addr, size_t length);
int mprotect(void *addr, size_t size, int prot);
#if defined(_DEFAULT_SOURCE)
#define MADV_NORMAL     0
#define MADV_RANDOM     1
#define MADV_SEQUENTIAL 2
#define MADV_WILLNEED   3
#define MADV_DONTNEED   4
int madvise(void *addr, size_t size, int advice);
#endif
#if defined(_POSIX_X_SOURCE) && _POSIX_C_SOURCE >= 200112L
#define POSIX_MADV_NORMAL     0
#define POSIX_MADV_RANDOM     1
#define POSIX_MADV_SEQUENTIAL 2
#define POSIX_MADV_WILLNEED   3
#define POSIX_MADV_DONTNEED   4
int posix_madvise(void *addr, size_t size, int advice);
#endif
int shm_open(const char *name, int oflag, mode_t mode);
int shm_unlink(const char *name);

#endif
