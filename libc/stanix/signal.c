#include <signal.h>
#include <errno.h>
#include <syscall.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int sigaddset(sigset_t *sigset, int signum){
	if(signum <= 0 || signum >= NSIG)return __set_errno(-EINVAL);
	*sigset |= sigmask(signum);
	return 0;
}

int sigdelset(sigset_t *sigset, int signum){
	if(signum <= 0 || signum >= NSIG)return __set_errno(-EINVAL);
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

int sigismember(const sigset_t *set, int signum){
	if(signum <= 0 || signum >= NSIG)return __set_errno(-EINVAL);
	return !!(*set & sigmask(signum));
}

int sigprocmask(int how, const sigset_t *set, sigset_t *oldset){
	return __set_errno(__syscall3(SYS_sigprogmask,how,(long)set,(long)oldset));
}

int sigpending(sigset_t *set){
	return __set_errno(__syscall1(SYS_sigpending,(long)set));
}

int sigsuspend(const sigset_t *mask){
	return __set_errno(__syscall1(SYS_sigsuspend,(long)mask));
}

int sigwait(const sigset_t *set, int *sig){
	return __set_errno(__syscall2(SYS_sigwait,(long)set,(long)sig));
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

static char *signames[] = {
	[SIGHUP]  = "Hangup",
	[SIGINT]  = "Interrupt",
	[SIGQUIT] = "Quit",
	[SIGILL	] = "Illegal instruction",
	[SIGTRAP] = "Trace trap",
	[SIGABRT] = "Abort",
	[SIGCAT]  = "Meow",
	[SIGFPE]  = "Floating point exception",
	[SIGKILL] = "Kill",
	[SIGBUS]  = "Bus error",
	[SIGSEGV] = "Segmentation fault",
	[SIGSYS]  = "Bas system call",
	[SIGPIPE] = "Broken pipe",
	[SIGALRM] = "Alarm clock",
	[SIGTERM] = "Terminate",
	[SIGURG]  = "Urgent condition",
	[SIGSTOP] = "Stop",
	[SIGTSTP] = "Stop from tty",
	[SIGCONT] = "Continue",
	[SIGCHLD] = "Child terminated",
	[SIGTTIN] = "Background read",
	[SIGTTOU] = "Background write",
	[SIGPOLL] = "Poll event",
	[SIGXCPU] = "Exceeded CPU time limit",
	[SIGXFSZ] = "Exceeded file size limit",
	[SIGVTALRM] = "Virtual time alarm",
	[SIGPROF]  = "Profiling time alarm",
	[SIGWINCH] =  "Window size changes",
	[SIGINFO]  = "Unformation request",
	[SIGUSR1]  = "User signal 1",
	[SIGUSR2]  = "User signal 2",
	[SIGTHR]   = "thread library AST",
};

char *strsignal(int signum){
	if(signum > NSIG || signum <= 0){
		static char buf[32];
		sprintf(buf,"%d",signum);
		return buf;
	}
	return signames[signum];
}
