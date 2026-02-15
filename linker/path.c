#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "linker.h"

static int try_dir(const char *dir, const char *path) {
	char full_path[strlen(dir) + strlen(path) +1];
	sprintf(full_path, "%s/%s", dir, path);
	return open(full_path, O_RDONLY);
}

static int try_path_list(const char *list, const char *path) {
	while (*list) {
		const char *end = strchr(list, ':');
		if (!end) end = strchr(list, '\0');

		if (end == list + 1) {
			// skip empty path like "::"
			list = end;
			continue;
		}

		char *dir = strndup(list, end - list);
		int fd = try_dir(dir, path);
		free(dir);
		if (fd >= 0) return fd;
		list = end;
	}
	return -1;
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
		fd = try_dir("/usr/lib", path);
		if (fd >= 0) return fd;
		return try_dir("/lib", path);
	}
}
