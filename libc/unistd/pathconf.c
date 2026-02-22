#include <unistd.h>
#include <limits.h>
#include <errno.h>

long pathconf(const char *pathname, int varcode){
	(void)pathname;
	switch(varcode){
	case _PC_PATH_MAX:
		return PATH_MAX;
	default:
		return __set_errno(-EINVAL);
	}
}
