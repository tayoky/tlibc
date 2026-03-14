.section .text
.hidden abi_enter
.extern memcpy
.globl abi_enter
.type abi_enter @function
abi_enter:
	push %rbp
	mov %rsp, %rbp

// make place on the stack
	sub %rdx, %rsp

// save entry point
	mov %rdi, %rbx

// copy auxiliary vector
	mov %rsp, %rdi
	call memcpy

	jmp *%rbx
.size abi_enter, .-abi_enter
