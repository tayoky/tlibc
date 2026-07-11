#ifndef _DIRENT_H
#define _DIRENT_H

#include <abi/dirent.h>
#include <sys/types.h>

struct _DIR;
typedef struct _DIR DIR;

DIR *opendir(const char *pathname);
int closedir(DIR *dir);
struct dirent *readdir(DIR *dir);
void seekdir(DIR *dir,long int offset);
long int telldir(DIR *dir);
void rewinddir(DIR *dir);
int dirfd(DIR *dir);

#endif
