#include <string.h>
#include <signal.h>
#include <libintl.h>
#include <stdio.h>

#define N_(str) str

static char *signames[NSIG] = {
	[SIGHUP]  = N_("Hangup"),
	[SIGINT]  = N_("Interrupt"),
	[SIGQUIT] = N_("Quit"),
	[SIGILL]  = N_("Illegal instruction"),
	[SIGTRAP] = N_("Trace trap"),
	[SIGABRT] = N_("Aborted"),
#ifdef SIGCAT
	[SIGCAT]  = N_("Meow"),
#endif
	[SIGFPE]  = N_("Floating point exception"),
	[SIGKILL] = N_("Killed"),
	[SIGBUS]  = N_("Bus error"),
	[SIGSEGV] = N_("Segmentation fault"),
	[SIGSYS]  = N_("Bas system call"),
	[SIGPIPE] = N_("Broken pipe"),
	[SIGALRM] = N_("Alarm clock"),
	[SIGTERM] = N_("Terminated"),
	[SIGURG]  = N_("Urgent condition"),
	[SIGSTOP] = N_("Stoped (signal)"),
	[SIGTSTP] = N_("Stoped"),
	[SIGCONT] = N_("Continued"),
	[SIGCHLD] = N_("Child terminated"),
	[SIGTTIN] = N_("Background read"),
	[SIGTTOU] = N_("Background write"),
#ifdef SIGPOLL
	[SIGPOLL] = N_("Poll event"),
#endif
#ifdef SIGIO
	[SIGIO]   = N_("IO data available"),
#endif
	[SIGXCPU] = N_("Exceeded CPU time limit"),
	[SIGXFSZ] = N_("Exceeded file size limit"),
	[SIGVTALRM] = N_("Virtual time alarm"),
	[SIGPROF]   = N_("Profiling time alarm"),
	[SIGWINCH]  = N_("Window size changes"),
#ifdef SIGINFO
	[SIGINFO] = N_("Information request"),
#endif
	[SIGUSR1] = N_("User signal 1"),
	[SIGUSR2] = N_("User signal 2"),
#ifdef SIGTHR
	[SIGTHR]  = N_("Thread library AST"),
#endif
};

char *strsignal(int signum) {
	if (signum >= NSIG || signum <= 0 || !signames[signum]) {
		static char buf[32];
		sprintf(buf, "%d", signum);
		return buf;
	}
	return dgettext("tlibc", signames[signum]);
}
