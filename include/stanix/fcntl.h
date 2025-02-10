#ifndef FCNTL_H
#define FCNTL_H

#ifndef MODE_T_DEFINED
#define MODE_T_DEFINED
typedef unsigned long mode_t;
#endif

#define O_RDONLY	00000000
#define O_WRONLY	00000001
#define O_RDWR		00000002
#ifndef O_CREAT
#define O_CREAT		00000100	
#endif
#ifndef O_EXCL
#define O_EXCL		00000200	
#endif
#ifndef O_NOCTTY
#define O_NOCTTY	00000400	
#endif
#ifndef O_TRUNC
#define O_TRUNC		00001000	
#endif
#ifndef O_APPEND
#define O_APPEND	00002000
#endif
#ifndef O_DIRECTORY
#define O_DIRECTORY	00200000	/* must be a directory */
#endif
#ifndef O_NOFOLLOW
#define O_NOFOLLOW	00400000	/* don't follow links */
#endif
#ifndef O_CLOEXEC
#define O_CLOEXEC	02000000	/* set close_on_exec */
#endif


int open(const char *pathname, int flags, ... /* mode_t mode */ );

int creat(const char *pathname, mode_t mode);

#endif