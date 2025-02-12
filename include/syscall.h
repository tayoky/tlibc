#ifndef SYSCALL_H
#define SYSCALL_H

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

#define SYS_exit  0
#define SYS_open  1
#define SYS_close 2
#define SYS_read  3
#define SYS_write 4
#define SYS_seek  5
#define SYS_dup   6
#define SYS_dup2  7
#define SYS_sbrk  8

#endif