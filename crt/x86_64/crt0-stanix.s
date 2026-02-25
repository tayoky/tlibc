.section .text
.globl _start
.type _start @function
.hidden main
_start:
	lea main(%rip), %r8
	call __init_tlibc
.size _start, .-_start
