#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>
#include <pwd.h>
#include <stdio.h>
#include <string.h>

static struct passwd _pwbuf;
static char _buf[1048];
static FILE *passwd_file = NULL;
static int is_master = 0;

static long parse_long(const char *str) {
	char *end;
	long l = strtol(str, &end, 10);
	if (end == str || *end) {
		return -1;
	}
	return l;
}

int fgetpwent_r(FILE *stream, struct passwd *pwbuf, char *buf, size_t size, struct passwd **pwbufp) {
	if (pwbufp) *pwbufp = NULL;
	fgets(buf, size, stream);
	memset(pwbuf, 0, sizeof(struct passwd));
	pwbuf->pw_name   = strsep(&buf, ":");
	pwbuf->pw_passwd = strsep(&buf, ":");
	pwbuf->pw_uid    = parse_long(strsep(&buf, ":"));
	pwbuf->pw_gid    = parse_long(strsep(&buf, ":"));
	if (is_master) {
		pwbuf->pw_class  = strsep(&buf, ":");
		pwbuf->pw_change = parse_long(strsep(&buf, ":"));
		pwbuf->pw_expire = parse_long(strsep(&buf, ":"));
	}
	pwbuf->pw_gecos  = strsep(&buf, ":");
	pwbuf->pw_dir    = strsep(&buf, ":");
	pwbuf->pw_shell  = strsep(&buf, ":\n");
	if (!pwbuf->pw_shell || pwbuf->pw_uid < 0 || pwbuf->pw_gid < 0 || pwbuf->pw_change < 0 || pwbuf->pw_expire < 0) {
		errno = EILSEQ;
		return -1;
	}
	if (pwbufp) *pwbufp = pwbuf;
	return 0;
}

struct passwd *fgetpwent(FILE *stream) {
	if (fgetpwent_r(stream, &_pwbuf, _buf, sizeof(_buf), NULL) < 0) {
		return NULL;
	} else {
		return &_pwbuf;
	}
}

void setpwent(void) {
	if (passwd_file) {
		rewind(passwd_file);
	} else {
		// try master first
		// master only exist on BSD/Stanix
		// and is only for root user
		passwd_file = fopen("/etc/master.passwd", "r");
		if (passwd_file) {
			is_master = 1;
			return;
		}
		passwd_file = fopen("/etc/passwd", "r");
		is_master = 0;
	}
}

void endpwent(void) {
	if (passwd_file) {
		fclose(passwd_file);
		passwd_file = NULL;
	}
}

int getpwent_r(struct passwd *pwbuf, char *buf, size_t size, struct passwd **pwbufp) {
	if (!passwd_file) setpwent();
	return fgetpwent_r(passwd_file, pwbuf, buf, size, pwbufp);
}

struct passwd *getpwent(void) {
	if (!passwd_file) setpwent();
	return fgetpwent(passwd_file);
}

int getpwuid_r(uid_t uid, struct passwd *pwd, char *buffer, size_t bufsize, struct passwd **result) {
	setpwent();
	for (;;) {
		int ret;
		if ((ret = getpwent_r(pwd, buffer, bufsize, result)) < 0) {
			return ret;
		}
		if (pwd->pw_uid == uid) {
			return 0;
		}
	}
	return 0;
}

struct passwd *getpwuid(uid_t uid) {
	struct passwd *ret;
	getpwuid_r(uid, &_pwbuf, _buf, sizeof(_buf), &ret);
	return ret;
}

int getpwnam_r(const char *name, struct passwd *pwd, char *buffer, size_t bufsize, struct passwd **result) {
	setpwent();
	for (;;) {
		int ret;
		if ((ret = getpwent_r(pwd, buffer, bufsize, result)) < 0) {
			return ret;
		}
		if (!strcmp(name, pwd->pw_name)) {
			return 0;
		}
	}
	return 0;
}

struct passwd *getpwnam(const char *name) {
	struct passwd *ret;
	getpwnam_r(name, &_pwbuf, _buf, sizeof(_buf), &ret);
	return ret;
}

int putpwent(const struct passwd *restrict pwbuf, FILE *restrict stream) {
	return fprintf(stream, "%s:%s:%ld:%ld:%s:%s:%s\n", pwbuf->pw_name, pwbuf->pw_passwd, pwbuf->pw_uid, pwbuf->pw_gid, pwbuf->pw_gecos, pwbuf->pw_dir, pwbuf->pw_shell) < 0 ? -1 : 0;
}
