#include <sys/stat.h>

//when writing this link don't exist in stanix
//so lstat in not implemented
int lstat(const char *pathname,struct stat *st){
	return stat(pathname,st);
}
