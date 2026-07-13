#include <unistd.h>
#include <stdarg.h>
#include <errno.h>

long syscall(long number, ...) {
	va_list args;
	va_start(args, number);
	long arg1 = va_arg(args, long);
	long arg2 = va_arg(args, long);
	long arg3 = va_arg(args, long);
	long arg4 = va_arg(args, long);
	long arg5 = va_arg(args, long);
	long arg6 = va_arg(args, long);
	va_end(args);

	long ret = 0;
#ifdef __x86_64__
	// TODO
#elif defined(__aarch64__)
	register long num asm("x8") = number;
	register long r0 asm("x0")  = arg1;
	register long r1 asm("x1")  = arg2;
	register long r2 asm("x2")  = arg3;
	register long r3 asm("x3")  = arg4;
	register long r4 asm("x4")  = arg5;
	register long r5 asm("x5")  = arg6;
	asm("svc #0" : "=r"(r0) : "r"(num), "r"(r0), "r"(r1), "r"(r2), "r"(r3), "r"(r4), "r"(r5) : "memory", "x6", "x7");
	ret = r0;
#else
	ret = -ENOSYS;
#endif
	return ret < 0 ? __set_errno(ret) : ret;
}
