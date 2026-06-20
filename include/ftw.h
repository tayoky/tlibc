#ifndef _FTW_H
#define _FTW_H

#define FTW_D   0x01
#define FTW_DNR 0x02
#define FTW_F   0x04
#define FTW_SL  0x08
#define FTW_NS  0x10

int ftw(const char *path, int (*fn)(const char *path, const struct stat *ptr, int flag), int ndirs);

#endif
