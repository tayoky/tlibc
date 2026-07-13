#include <string.h>
#include <signal.h>
#include <stdio.h>

static char *signames[] = {
	[SIGHUP]  = "Hangup",
	[SIGINT]  = "Interrupt",
	[SIGQUIT] = "Quit",
	[SIGILL]  = "Illegal instruction",
	[SIGTRAP] = "Trace trap",
	[SIGABRT] = "Abort",
#ifdef SIGCAT
	[SIGCAT]  = "Meow",
#endif
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
#ifdef SIGPOLL
	[SIGPOLL] = "Poll event",
#endif
#ifdef SIGIO
	[SIGIO]   = "IO data available",
#endif
	[SIGXCPU] = "Exceeded CPU time limit",
	[SIGXFSZ] = "Exceeded file size limit",
	[SIGVTALRM] = "Virtual time alarm",
	[SIGPROF]   = "Profiling time alarm",
	[SIGWINCH]  = "Window size changes",
#ifdef SIGINFO
	[SIGINFO] = "Information request",
#endif
	[SIGUSR1] = "User signal 1",
	[SIGUSR2] = "User signal 2",
#ifdef SIGTHR
	[SIGTHR]  = "Thread library AST",
#endif
};

char *strsignal(int signum) {
	if (signum > NSIG || signum <= 0 || !signames[signum]) {
		static char buf[32];
		sprintf(buf, "%d", signum);
		return buf;
	}
	return signames[signum];
}
