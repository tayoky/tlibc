#ifndef _FTW_H
#define _FTW_H

#define FTW_F   1
#define FTW_D   2
#define FTW_DNR 3
#define FTW_NS  4
#define FTW_SL  5
#define FTW_DP  6
#define FTW_SLN 7


#if defined(_XOPEN_SOURCE) && _XOPEN_SOURCE >= 500
#define FTW_PHYS  0x01
#define FTW_MOUNT 0x02
#define FTW_CHDIR 0x04
#define FTW_DEPTH 0x08
#ifdef _GNU_SOURCE
#define FTW_ACTIONRETVAL 0x10
#endif

#ifdef _GNU_SOURCE
#define FTW_CONTINUE      0
#define FTW_STOP          1
#define FTW_SKIP_SUBTREE  2
#define FTW_SKIP_SIBLINGS 3
#endif

struct FTW {
	int base;
	int level;
};
#endif

int ftw(const char *path, int (*fn)(const char *path, const struct stat *ptr, int flag), int ndirs);
extern int nftw (const char *path, int (*fn)(const char *path, const struct stat *ptr, int flags, struct FTW *ftwbuf), int ndirs, int flags);

#endif
