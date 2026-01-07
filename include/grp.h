#ifndef _GRP_H
#define _GRP_H

#include <sys/types.h>

struct group {
	char *gr_name;
	char *gr_passwd;
	gid_t gr_gid;
	char **gr_mem;
};

struct group *getgrgid(gid_t gid);
struct group *getgrnam(const char *name);
int getgrgid_r(gid_t gid, struct group *gbuf, char *buf, size_t size, struct group **gbufp);
int getgrnam_r(const char *name, struct group *gbuf, char *buf, size_t size, struct group **gbufp);

void setgrent(void);
void endgrent(void);
struct group *getgrent(void);
int getgrent_r(struct group *gbuf, char *buf, size_t size, struct group **gbufp);

struct group *fgetgrent(FILE *stream);
int fgetgrent_r(FILE *stream, struct group *gbuf, char *buf, size_t size, struct group **gbufp);

#endif
