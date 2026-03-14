//crt 0 for aarch64-linux

.section .text
.globl _start
.type _start @function
_start:
	sub sp, sp, 16
	stp x0, x1, [sp]
	bl __init_tlibc
	ldp x0, x1, [sp]
	add sp, sp, 16
.size _start, .-_start
