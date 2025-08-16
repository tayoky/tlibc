.section .text
.globl _start
.type _start @function
_start:
	bl __init_tlibc
.size _start, .-_start
