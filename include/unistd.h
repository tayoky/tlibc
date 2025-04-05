#ifndef UNISTD_H
#define UNISTD_H

#include <sys/type.h>
#include <sys/types.h>

#ifndef SEEK_SET
#define SEEK_SET 0
#endif
#ifndef SEEK_CUR
#define SEEK_CUR 1
#endif
#ifndef SEEK_END
#define SEEK_END 2
#endif

typedef long  intptr_t;

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

int dup(int oldfd);
int dup2(int oldfd, int newfd);

void *sbrk(intptr_t increment);

void _exit(int status);

int close(int fd);

unsigned int sleep(unsigned int seconds);
int usleep(useconds_t usec);

int pipe(int pipefd[2]);

int execve(const char *pathname,const char * const argv[],const char * const envp[]);

pid_t fork(void);

int mkdir(const char *pathname,mode_t mode);

//not syscall exec

int execl(const char *pathname, const char *arg, ... /*, (char *) NULL */);
int execlp(const char *file, const char *arg, ... /*, (char *) NULL */);
int execle(const char *pathname, const char *arg, ... /*, (char *) NULL, char *const envp[] */);
int execv(const char *pathname, const char *const argv[]);
int execvp(const char *file, const char *const argv[]);
int execvpe(const char *file, const char *const argv[],const char *const envp[]);

//cwd management

char *getcwd(char *buf, size_t size);
int chdir(const char *path);

#ifndef NULL
#define NULL ((void*)0)
#endif

extern char **__environ;

#endif
