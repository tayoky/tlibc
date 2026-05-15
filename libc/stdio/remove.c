#include <errno.h>
#include <stdio.h>
#include <unistd.h>

int remove(const char *pathname) {
	int ret = unlink(pathname);

	// if it is a dir, use rmdir
	if (ret && errno == EISDIR) {
		ret = rmdir(pathname);
	}

	return ret;
}
