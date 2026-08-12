#ifndef _ABI_SIGNAL_H
#define _ABI_SIGNAL_H

// Stanix signal ABI

#include <sys/types.h>

#define _NSIG 33 //counting 0 (mask is 1-32)
#define NSIG _NSIG

#define	SIGHUP	  1	 //hangup
#define	SIGINT	  2	 //interrupt
#define	SIGQUIT	  3	 //quit
#define	SIGILL	  4	 //illegal instruction (not reset when caught)
#define	SIGTRAP	  5	 //trace trap (not reset when caught)
#define	SIGABRT	  6	 //abort()
#define SIGCAT    7  //meow
#define	SIGFPE	  8	 //floating point exception
#define	SIGKILL	  9	 //kill (cannot be caught or ignored)
#define	SIGBUS	  10 //bus error
#define	SIGSEGV	  11 //segmentation violation
#define	SIGSYS	  12 //bad argument to system call
#define	SIGPIPE	  13 //write on a pipe with no one to read it
#define	SIGALRM	  14 //alarm clock
#define	SIGTERM	  15 //software termination signal from kill
#define	SIGURG	  16 //urgent condition on IO channel
#define	SIGSTOP	  17 //sendable stop signal not from tty
#define	SIGTSTP	  18 //stop signal from tty
#define	SIGCONT	  19 //continue a stopped process
#define	SIGCHLD	  20 //to parent on child stop or exit
#define	SIGTTIN	  21 //to readers pgrp upon background tty read
#define	SIGTTOU	  22 //like TTIN for output if (tp->t_local&LTOSTOP)
#define	SIGPOLL	  23 //input/output possible signal
#define	SIGXCPU	  24 //exceeded CPU time limit
#define	SIGXFSZ	  25 //exceeded file size limit
#define	SIGVTALRM 26 //virtual time alarm
#define	SIGPROF	  27 //profiling time alarm
#define SIGWINCH  28 //window size changes
#define SIGINFO	  29 //information request
#define SIGUSR1   30 //user defined signal 1
#define SIGUSR2   31 //user defined signal 2
#define SIGTHR    32 //thread library AST


#define	SIG_DFL		(void (*)(int))0
#define	SIG_IGN		(void (*)(int))1
#define	SIG_ERR		(void (*)(int))-1

//we use int so it work both on 64bit and 32bit system
typedef unsigned int sigset_t;

union sigval {
	int	sival_int;	    //integer value
	void	*sival_ptr;	//pointer value
};

typedef struct {
	int si_signo;          //signal number
	int si_code;           //signal code
	int si_errno;          //error value
	pid_t si_pid;          //sending process pid
	uid_t si_uid;          //real user id of the sending process
	void *si_addr;         //faulting address (signal specific)
	int si_status;         //exit status
	long si_band;          //unused
	union sigval si_value; //signal value/argument
} siginfo_t;

struct	sigaction {
	union {		/* signal handler */
		void	(*__sa_handler)(int);
		void	(*__sa_sigaction)(int, siginfo_t *, void *);
	} __sigaction_u;
	sigset_t sa_mask; /* signal mask to apply*/
	int	sa_flags;     /* see signal options below*/
};

typedef struct {
	void  *ss_sp;     /* base address of stack */
	int    ss_flags;  /* flags */
	size_t ss_size;   /* number of bytes in stack */
} stack_t;

//little trick so we can use .sa_handler and .sa_sigaction
#define sa_handler      __sigaction_u.__sa_handler
#define sa_sigaction    __sigaction_u.__sa_sigaction

#define sigmask(m)	(1U << ((m)-1))

//sigprocmask action
#define	SIG_BLOCK	1 //block specified signal set
#define	SIG_UNBLOCK	2 //unblock specified signal set
#define	SIG_SETMASK	3 //set specified signal set

#define SA_NOCLDSTOP 0x01
#define SA_ONSTACK   0x02
#define SA_RESETHAND 0x04
#define SA_RESTART   0x08
#define SA_SIGINFO   0x10
#define SA_NOCLDWAIT 0x20
#define SA_NODEFER   0x40

#define ILL_ILLOPC   1
#define ILL_ILLOPN   2
#define ILL_ILLADR   3
#define ILL_ILLTRP   4
#define ILL_PRVOPC   5
#define ILL_PRVREG   6
#define ILL_COPROC   7
#define ILL_BADSTK   8

#define FPE_INTDIV   9
#define FPE_INTOVF  10
#define FPE_FLTDIV  11
#define FPE_FLTOVF  12
#define FPE_FLTUND  13
#define FPE_FLTRES  14
#define FPE_FLTINV  15
#define FPE_FLTSUB  16

#define SEGV_MAPERR 17
#define SEGV_ACCERR 18

#define BUS_ADRALN  19
#define BUS_ADRERR  20
#define BUS_OBJERR  21

#define TRAP_BRKPT  22
#define TRAP_TRACE  23

#define CLD_EXITED  24
#define CLD_KILLED  25
#define CLD_DUMPED  26
#define CLD_TRAPPED 27
#define CLD_STOPPED 28
#define CLD_CONTINUED 29

#define POLL_IN     30
#define POLL_OUT    31
#define POLL_MSG    32
#define POLL_ERR    33
#define POLL_PRI    34
#define POLL_HUP    35

#define SI_USER     36
#define SI_QUEUE    37
#define SI_TIMER    38
#define SI_ASYNCIO  39
#define SI_MESGQ    40

typedef void (*sighandler_t)(int);
typedef int sig_atomic_t;

#endif
