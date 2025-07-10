#ifndef DIRENT_H
#define DIRENT_H

struct dirent {
	char d_name[256]; // pretty sure it should use limtit.h::PATH_MAX
	int d_ino; //stub inode don't exist in stanix
};

struct _DIR;
typedef struct _DIR DIR;


//WTF !!!! there are no raw readdir syscall ????

DIR *opendir(const char *pathname);
int closedir(DIR *dir);
struct dirent *readdir(DIR *dir);
void seekdir(DIR *dir,long int offset);
long int telldir(DIR *dir);
void rewinddir(DIR *dir);

#endif
