.section .text
.globl _start
.type _start @function
.hidden main
_start:
	mov %rsp, %rdi
	lea main(%rip), %rsi
	call __init_tlibc
.size _start, .-_start
