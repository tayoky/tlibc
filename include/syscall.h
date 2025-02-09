#ifndef SYSCALL_H
#define SYSCALL_H

#include <stdint.h>

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

#endif