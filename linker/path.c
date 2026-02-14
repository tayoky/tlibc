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

static int try_lib_path(const char *path) {
	const char *cur = lib_path;
	while (*cur) {
		const char *end = strchr(cur, ';');
		if (!end) end = strchr(cur, '\0');

		if (end == cur + 1) {
			// skip empty path like ";;"
			cur = end;
			continue;
		}

		char *dir = strndup(cur, end - cur);
		int fd = try_dir(dir, path);
		free(dir);
		if (fd >= 0) return fd;
		cur = end;
	}
	return -1;
}

int open_lib(const char *path) {
	if (strchr(path, '/')) {
		// it's aready a path
		return open(path, O_RDONLY);
	} else {
		int fd = -1;
		if (lib_path) fd = try_lib_path(path);
		if (fd >= 0) return fd;
		fd = try_dir("/usr/lib", path);
		if (fd >= 0) return fd;
		return try_dir("/lib", path);
	}
}
