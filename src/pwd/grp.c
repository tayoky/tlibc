#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <grp.h>

static struct group _gbuf;
static char _buf[1048];
static FILE *grp_file = NULL;

#define OUT(c) if(size > 0){\
            *(unsigned char *)buf = c;\
            buf++;\
            size--;\
        } else {\
            return __set_errno(-ERANGE);\
        }
#define PARSE_STR(var,end) var = buf;\
    while((c = fgetc(stream)) != end){\
        if(c == EOF)return -1;\
        OUT(c);\
    }\
    OUT('\0');
#define PARSE_INT(var,end) var = 0;\
    while((c = fgetc(stream)) != end){\
        if(c == EOF)return -1;\
        var *= 10;\
        var += c - '0';\
    }


int fgetgrent_r(FILE *stream, struct group *gbuf, char *buf, size_t size, struct group **gbufp) {
	int c = 0;
	if (gbufp) *gbufp = NULL;
	PARSE_STR(gbuf->gr_name, ':');
	PARSE_INT(gbuf->gr_gid, ':');
	PARSE_STR(gbuf->gr_passwd, ':');
	char *users;
	PARSE_STR(users, '\n');

	// now we can cut
	int users_count = 1;
	char *ptr = users;
	while (ptr) {
		if (*ptr == ',') {
			*ptr = '\0';
			users_count++;
		}
		ptr++;
	}

	// do some padding
	uintptr_t padding = (uintptr_t)buf % sizeof(char *);
	if (padding) {
		padding = sizeof(char*) - padding;
		if (size < sizeof(char*) * (users_count + 1)) {
			return __set_errno(-ERANGE);
		}
		buf += padding;
		size -= padding;
	}
	if (size < sizeof(char*) * (users_count + 1)) {
		return __set_errno(-ERANGE);
	}

	gbuf->gr_mem = (char**)buf;
	ptr = users;
	for (int i=0; i<users_count; i++) {
		gbuf->gr_mem[i] = ptr;
		ptr += strlen(ptr) + 1;
	}
	gbuf->gr_mem[users_count] = NULL;
	if (gbufp) *gbufp = gbuf;
	return 0;
}

struct group *fgetgrent(FILE *stream){
    if (fgetgrent_r(stream, &_gbuf, _buf, sizeof(_buf), NULL) < 0) {
        return NULL;
    } else {
        return &_gbuf;
    }
}

void setgrent(void) {
    if (grp_file) {
        rewind(grp_file);
    } else {
        grp_file = fopen("/etc/group","r");
    }
}

void endgrent(void) {
    if (grp_file) {
        fclose(grp_file);
        grp_file = NULL;
    }
}

int getgrent_r(struct group *gbuf, char *buf, size_t size, struct group **gbufp) {
    if (!grp_file) setgrent();
    return fgetgrent_r(grp_file, gbuf, buf, size, gbufp);
}

struct group *getgrent(void) {
	if (!grp_file) setgrent();
	return fgetgrent(grp_file);
}

int getgrgid_r(gid_t gid, struct group *gbuf, char *buf, size_t size, struct group **gbufp) {
	setgrent();
	for (;;) {
		int ret;
		if ((ret = getgrent_r(gbuf, buf, size, gbufp)) < 0) {
			return ret;
		}
		if (gbuf->gr_gid == gid) {
			return 0;
		}
	}
}

struct group *getgrgid(gid_t gid) {
	struct group *gbufp;
	getgrgid_r(gid, &_gbuf, _buf, sizeof(_buf), &gbufp);
	return gbufp;
}

int getgrnam_r(const char *name, struct group *gbuf, char *buf, size_t size, struct group **gbufp) {
	setgrent();
	for (;;) {
		int ret;
		if ((ret = getgrent_r(gbuf, buf, size, gbufp)) < 0) {
			return ret;
		}
		if (!strcmp(gbuf->gr_name, name)) {
			return 0;
		}
	}
}

struct group *getgrnam(const char *name) {
	struct group *gbufp;
	getgrnam_r(name, &_gbuf, _buf, sizeof(_buf), &gbufp);
	return gbufp;
}
