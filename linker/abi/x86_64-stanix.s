.section .text
.globl abi_enter
.type abi_enter @function
abi_enter:
	push %rbp
	mov %rsp, %rbp
	mov %rdi, %rax
	mov %rsi, %rdi
	mov %rdx, %rsi
	mov %rcx, %rdx
	mov %r8 , %rcx
	jmp *%rax
.size abi_enter, .-abi_enter
