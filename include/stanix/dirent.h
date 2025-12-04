#ifndef DIRENT_H
#define DIRENT_H

#include <sys/types.h>

struct dirent {
	char d_name[256]; // pretty sure it should use limtit.h::PATH_MAX
	ino_t d_ino; //stub inode don't exist in stanix
	int d_type;
};

struct _DIR;
typedef struct _DIR DIR;

#define DT_UNKNOWN  0
#define DT_REG      1
#define DT_DIR      2
#define DT_FIFO     3
#define DT_SOCK     4
#define DT_CHR      5
#define DT_BLK      6
#define DT_LNK      7


//WTF !!!! there are no raw readdir syscall ????

DIR *opendir(const char *pathname);
int closedir(DIR *dir);
struct dirent *readdir(DIR *dir);
void seekdir(DIR *dir,long int offset);
long int telldir(DIR *dir);
void rewinddir(DIR *dir);

#endif
