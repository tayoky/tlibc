#ifndef _SYSCALL_H
#define _SYSCALL_H

#ifdef __x86_64__
static inline long __syscall0(long n)
{
	long ret;
	asm volatile ("int $0x80" : "=a"(ret) : "a"(n) : "rcx", "r11", "memory");
	return ret;
}

static inline long __syscall1(long n, long a1)
{
	long ret;
	asm volatile ("int $0x80" : "=a"(ret) : "a"(n), "D"(a1) : "memory");
	return ret;
}

static inline long __syscall2(long n, long a1, long a2)
{
	long ret;
	asm volatile ("int $0x80" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2) : "rcx", "r11", "memory");
	return ret;
}

static inline long __syscall3(long n,long a1,long a2,long a3) { 
    long ret; 
    asm volatile ("int $0x80"  : "=a"(ret)  : "a"(n), "D"(a1), "S"(a2), "d"(a3) : "memory"); 
    return ret; 
}
static inline long __syscall4(long n,long a1,long a2,long a3,long a4) { 
    long ret; 
    asm volatile ("int $0x80"  : "=a"(ret)  : "a"(n), "D"(a1), "S"(a2), "d"(a3), "c"(a4): "memory"); 
    return ret; 
}
static inline long __syscall5(long n,long a1,long a2,long a3,long a4,long a5) { 
    long ret; 
	register long r8 __asm__("r8") = a5;
    asm volatile ("int $0x80"  : "=a"(ret)  : "a"(n), "D"(a1), "S"(a2), "d"(a3), "c"(a4), "r" (r8): "memory"); 
    return ret; 
}
#elif defined(__aarch64__)
static inline long __syscall0(long n)
{
	long ret;
	//asm("svc" : "=0"(ret) : "8"(n) : "memory");
	return ret;
}

static inline long __syscall1(long n, long a1)
{
	long ret;
	//asm volatile ("svc" :  "=a"(ret) : "a"(n), "D"(a1) : "memory");
	return ret;
}

static inline long __syscall2(long n, long a1, long a2)
{
	long ret;
	//asm volatile ("svc" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2) : "rcx", "r11", "memory");
	return ret;
}

static inline long __syscall3(long n,long a1,long a2,long a3) { 
    long ret; 
    //asm volatile ("svc"  : "=a"(ret)  : "a"(n), "D"(a1), "S"(a2), "d"(a3) : "memory"); 
    return ret; 
}

static inline long __syscall5(long n,long a1,long a2,long a3,long a4,long a5){
	long ret;
	//asm volatile ("svc" : "=0" (ret) : "8" (n), "0" (a1), "1"(a2), "2"(a3), "3"(a4), "4"(a5) : "memory");
	return ret;
}
#else
#error unsupported architecture
#endif

#define SYS_exit         0
#define SYS_open         1
#define SYS_close        2
#define SYS_read         3
#define SYS_write        4
#define SYS_seek         5
#define SYS_dup          6
#define SYS_dup2         7
#define SYS_sbrk         8
#define SYS_ioctl        9
#define SYS_usleep       10
#define SYS_sleepuntil   11
#define SYS_gettimeofday 12
#define SYS_settimeofday 13
#define SYS_pipe         14
#define SYS_execve       15
#define SYS_fork         16
#define SYS_mkdir        17
#define SYS_unlink       18
#define SYS_rmdir        19
#define SYS_readdir      20
#define SYS_stat         21
#define SYS_fstat        22
#define SYS_getcwd       23
#define SYS_chdir        24
#define SYS_waitpid      25
#define SYS_insmod       26
#define SYS_rmmod        27
#define SYS_isatty       28
#define SYS_openpty      29
#define SYS_poll         30
#define SYS_sigprogmask  31
#define SYS_sigaction    32
#define SYS_sigwait      33
#define SYS_sigsuspend   34
#define SYS_sigpending   35
#define SYS_kill         36
#define SYS_getpid       37
#define SYS_mount        38
#define SYS_umount       39

#endif
