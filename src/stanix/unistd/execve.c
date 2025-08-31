#include <unistd.h>
#include <syscall.h>
#include <errno.h>

int execve(const char *pathname,const char * const *argv,const char * const *envp){
	return __set_errno(__syscall3(SYS_execve,(long)pathname,(long)argv,(long)envp));
}
