#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linker.h"

static int try_dir(const char *dir, const char *path) {
	char full_path[strlen(dir) + strlen(path) + 1];
	sprintf(full_path, "%s/%s", dir, path);
	return open(full_path, O_RDONLY);
}

static int try_path_list(const char *list, const char *path) {
	char *dup = dl_strdup(list);
	char *ptr;
	char *dir = strtok_r(dup, ":", &ptr);
	int fd = -1;
	while (dir) {
		fd = try_dir(dir, path);
		if (fd >= 0) break;
		dir = strtok_r(NULL, ":", &ptr);
	}
	dl_free(dup);
	return fd;
}

int open_lib(const char *path) {
	if (strchr(path, '/')) {
		// it's aready a path
		return open(path, O_RDONLY);
	} else {
		int fd = -1;
		if (rpath) fd = try_path_list(rpath, path);
		if (fd >= 0) return fd;
		if (lib_path) fd = try_path_list(lib_path, path);
		if (fd >= 0) return fd;
		fd = try_dir("/lib", path);
		if (fd >= 0) return fd;
		fd = try_dir("/usr/lib", path);
		if (fd >= 0) return fd;
		return try_dir("/usr/local/lib", path);
	}
}
