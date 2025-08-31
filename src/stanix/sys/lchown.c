#include <sys/stat.h>

int lchown(const char *pathname, uid_t owner, gid_t group){
	return chown(pathname,owner,group);
}
