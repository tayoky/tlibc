#include <pty.h>
#include <syscall.h>
#include <errno.h>

int openpty(int *amaster, int *aslave, char *name,const struct termios *termp,const struct winsize *winp){
	return __set_errno(__syscall5(SYS_openpty,(long)amaster,(long)aslave,(long)name,(long)termp,(long)winp));
}