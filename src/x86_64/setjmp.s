.section .text

.globl setjmp
.type setjmp @function
setjmp:
	;save callee saved register
	movq %rsp, 8(%rdi)
	movq %rbp, 16(%rdi)
	movq %r12, 24(%rdi)
	movq %r13, 32(%rdi)
	movq %r14, 40(%rdi)
	movq %r15, 48(%rdi)

	;save rip
	movq (%rsp), %rax
	movq %rax, (%rdi)

	;return 0
	xor %rax, %rax
	ret
.size setjmp, .-setjmp

.globl longjmp
.type longjmp @function
longjmp:
	;if rsi is 0 set it to 1
	cmp %rsi, $0
	jne skip
	mov $1, %rsi
	skip:

	;setup the return value
	movq %rsi, %rax
	
	;restore callee saved register
	movq 8(%rdi) , %rsp
	movq 16(%rdi), %rbp
	movq 24(%rdi), %r12
	movq 32(%rdi), %r13
	movq 40(%rdi), %r14
	movq 48(%rdi), %r15

	;return to the saved rip
	mov (%rdi), %rsi
	jmp *%rsi
.size longjmp, .-longjmp
