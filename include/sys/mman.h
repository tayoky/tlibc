#ifndef _SYS_MMAN_H
#define _SYS_MMAN_H

#include <abi/mman.h>
#include <sys/types.h>

#define map_failed (void*)-1
#define MAP_FAILED (void*)-1

void *mmap(void *addr,size_t length,int prot,int flags,int fd,off_t offset);
int munmap(void *addr,size_t length);
int mprotect(void *addr,size_t size,int prot);
int shm_open(const char *name, int oflag, mode_t mode);
int shm_unlink(const char *name);

#endif
