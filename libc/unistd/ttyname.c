#include <unistd.h>
#include <dirent.h>
#include <limits.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sysdeps.h>

static int search_dev(const char *dirpath, dev_t dev, char *buf, size_t size) {
	struct dirent *entry;
	DIR *dir = opendir(dirpath);
	if (!dir) return 0;

	while ((entry = readdir(dir))) {
		char full_path[PATH_MAX];
		snprintf(full_path, sizeof(full_path), "%s/%s", dirpath, entry->d_name);
		struct stat st;
		if (stat(full_path, &st) < 0) continue;
		if (st.st_rdev == dev) {
			if (size < strlen(full_path) + 1) {
				return __set_errno(-ERANGE);
			}
			strcpy(buf, full_path);
			return 1;
		}
	}

	closedir(dir);
	return 0;
}

int ttyname_r(int fd, char *buf, size_t size) {
	if (sys_ttyname_r) {
		return sys_ttyname_r(fd, buf, size);
	} else {
		struct stat st;
		int ret = fstat(fd, &st);
		if (ret < 0) return -1;
		
		ret = search_dev("/dev", st.st_rdev, buf, size);
		if (ret < 0) return ret;
		if (ret == 1) return 0;
		ret = search_dev("/dev/pts", st.st_rdev, buf, size);
		if (ret < 0) return ret;
		if (ret == 1) return 0;
		ret = search_dev("/devices", st.st_rdev, buf, size);
		if (ret < 0) return ret;
		if (ret == 1) return 0;
		return __set_errno(-ENODEV);
	}
}

char *ttyname(int fd) {
	static char buf[PATH_MAX];
	return ttyname_r(fd, buf, sizeof(buf)) >= 0 ? buf : NULL;
}
