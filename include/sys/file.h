#ifndef _SYS_FILE_H
#define _SYS_FILE_H

#define LOCK_SH 0x1
#define LOCK_EX 0x2
#define LOCK_NB 0x4
#define LOCK_UN 0x8

int flock(int fd, int op);

#endif
