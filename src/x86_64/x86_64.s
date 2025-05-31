bits 64

section .text

global setjmp
global longjmp

setjmp :
	mov [rdi + 0],  rax
	mov [rdi + 8],  rbp
	mov [rdi + 16], r12
	mov [rdi + 24], r13
	mov [rdi + 32], r14
	mov [rdi + 40], r15

	;save rip
	mov rax, [rsp]
	mov [rdi + 48], rax

	;return 0
	xor rax, rax
	ret
longjmp:
	;if rsi is 0 set it to 1
	cmp rsi, 0
	jne skip
	mov rsi, 1
	skip:

	;setup the return value
	mov rax,rsi

	mov rbp, [rdi + 8]
	mov r12, [rdi + 16]
	mov r13, [rdi + 24]
	mov r14, [rdi + 32]
	mov r15, [rdi + 40]

	;find the address to return to
	mov rsi, [rdi + 48]
	jmp rsi