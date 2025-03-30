#ifndef SYSCALL_H
#define SYSCALL_H

#ifdef X86_64
#ifndef x86_64
#define x86_64
#endif
#endif

#ifdef x86_64
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

static inline __syscall3(long n,long a1,long a2,long a3) { 
    long ret; 
    asm volatile ("int $0x80"  : "=a"(ret)  : "a"(n), "D"(a1), "S"(a2), "d"(a3) : "memory"); 
    return ret; 
}
#else
#error unsupported architecture
#endif

#define SYS_exit            0
#define SYS_open            1
#define SYS_close           2
#define SYS_read            3
#define SYS_write           4
#define SYS_seek            5
#define SYS_dup             6
#define SYS_dup2            7
#define SYS_sbrk            8
#define SYS_ioctl           9
#define SYS_usleep          10
#define SYS_sleepuntil      11
#define SYS_gettimeoftheday 12
#define SYS_settimeoftheday 13
#define SYS_pipe            14
#define SYS_execve          15
#define SYS_fork            16
#define SYS_mkdir           17
#define SYS_unlink          18
#define SYS_rmdir           19
#define SYS_readdir         20
#define SYS_stat            21
#define SYS_fstat           22
#define SYS_getcwd          23
#define SYS_chdir           24
#define SYS_waitpid         25

#endif
