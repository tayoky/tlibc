#ifndef UNISTD_H
#define UNISTD_H

#ifndef SSIZE_T_DEFINED
#define SSIZE_T_DEFINED
typedef long ssize_t;
#endif

#ifndef SIZE_T_DEFINED
#define SIZE_T_DEFINED
typedef unsigned long size_t;
#endif

#ifndef SEEK_SET
#define SEEK_SET 0
#endif
#ifndef SEEK_CUR
#define SEEK_CUR 1
#endif
#ifndef SEEK_END
#define SEEK_END 2
#endif

#ifndef OFF_T_DEFINED
#define OFF_T_DEFINED
typedef unsigned long off_t;
#endif

#ifndef INTPTR_T_DEFINED
#define INTPTR_T_DEFINED
typedef long long  intptr_t;
#endif

#ifndef STDIN_FILENO
#define STDIN_FILENO 0
#endif
#ifndef STDOUT_FILENO
#define STDOUT_FILENO 1
#endif
#ifndef STDERR_FILENO
#define STDERR_FILENO 2
#endif

off_t lseek(int fd, off_t offset, int whence);

ssize_t read(int fd, const void *buffer, size_t count);
ssize_t write(int fd, const void *buffer, size_t count);

void *sbrk(intptr_t increment);

void _exit(int status);

#ifndef NULL
#define NULL ((void*)0)
#endif

#endif