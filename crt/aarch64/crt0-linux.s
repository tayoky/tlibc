//crt 0 for aarch64-linux

.section .text
.globl _start
.type _start @func
_start:
	sub sp, sp, 16
	stp x0, x1, [sp]
	bl __tlibc_init
	ldp x0, x1, [sp]
	add sp, sp, 16
.size _start, .-_start
