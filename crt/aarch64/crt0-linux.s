//crt 0 for aarch64-linux

.section .text
.globl _start
.type _start @function
_start:
	mov x0, sp
	adrp x1, main
	add x1, x1, :lo12:main
	bl __init_tlibc
.size _start, .-_start
