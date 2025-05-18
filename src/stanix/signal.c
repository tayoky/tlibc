#include <signal.h>
#include <errno.h>
#include <syscall.h>
#include <unistd.h>

int sigaddset(sigset_t *sigset, int signum){
	*sigset |= sigmask(signum);
	return 0;
}

int sigdelset(sigset_t *sigset, int signum){
	*sigset &= ~sigmask(signum);
	return 0;
}

int sigemptyset(sigset_t *sigset){
	*sigset = 0;
	return 0;
}

int sigfillset(sigset_t *sigset){
	*sigset = (sigset_t)(-1);
	return 0;
}

int sigprocmask(int how, const sigset_t *set, sigset_t *oldset){
	return __set_errno(__syscall3(SYS_sigprogmask,how,(long)set,(long)oldset));
}

int sigpending(sigset_t *set){
	return __set_errno(__syscall1(SYS_sigpending,(long)set));
}

int kill(pid_t pid, int sig){
	return __set_errno(__syscall2(SYS_kill,pid,sig));
}

int raise(int sig){
	return kill(getpid(),sig);
}

int sigaction(int signum, const struct sigaction *act,struct sigaction * oldact){
	return __set_errno(__syscall3(SYS_sigaction,signum,(long)act,(long)oldact));
}

sighandler_t signal(int signum, sighandler_t handler){
	//stanix has no signal syscall so we wrap around sigaction
	struct sigaction action = {
		.sa_handler = handler,
		.sa_flags = 0,
		.sa_mask = 0,
	};

	struct sigaction old;

	if(sigaction(signum,&action,&old) < 0){
		return SIG_ERR;
	}
	
	return old.sa_handler;
}