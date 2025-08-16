.section .text
.globl _start
.type _start @function
_start:
	call __init_tlibc
.size _start, .-_start
