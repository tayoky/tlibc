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
	[SIGBUS]  = N_("Bus error"),
#ifdef SIGCAT
	[SIGCAT]  = N_("Meow"),
#endif
	[SIGFPE]  = N_("Floating point exception"),
	[SIGKILL] = N_("Killed"),
	[SIGUSR1] = N_("User signal 1"),
	[SIGSEGV] = N_("Segmentation fault"),
	[SIGUSR2] = N_("User signal 2"),
	[SIGPIPE] = N_("Broken pipe"),
	[SIGALRM] = N_("Alarm clock"),
	[SIGTERM] = N_("Terminated"),
#ifdef SIGSTKFLT
	[SIGSTKFLT] = N_("Stack fault on coprocessor"),
#endif
	[SIGCHLD] = N_("Child terminated"),
	[SIGCONT] = N_("Continued"),
	[SIGSTOP] = N_("Stoped (signal)"),
	[SIGTSTP] = N_("Stoped"),
	[SIGTTIN] = N_("Background read"),
	[SIGTTOU] = N_("Background write"),
	[SIGURG]  = N_("Urgent condition"),
	[SIGXCPU] = N_("Exceeded CPU time limit"),
	[SIGXFSZ] = N_("Exceeded file size limit"),
	[SIGVTALRM] = N_("Virtual time alarm"),
	[SIGPROF]   = N_("Profiling time alarm"),
	[SIGWINCH]  = N_("Window size changes"),
#ifdef SIGIO
	[SIGIO]   = N_("IO data available"),
#endif
#if defined(SIGPOLL) && SIGPOLL != SIGIO
	[SIGPOLL] = N_("Poll event"),
#endif
#ifdef SIGINFO
	[SIGINFO] = N_("Information request"),
#endif
#ifdef SIGPWR
	[SIGPWR]  = N_("Power failure"),
#endif
	[SIGSYS]  = N_("Bas system call"),
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
