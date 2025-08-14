.section .text

.globl setjmp
.type setjmp @function
setjmp:
	//save callee saved register
	movq %rsp, 8(%rdi)
	movq %rbp, 16(%rdi)
	movq %rbx, 24(%rdi)
	movq %r12, 32(%rdi)
	movq %r13, 50(%rdi)
	movq %r14, 48(%rdi)
	movq %r15, 56(%rdi)

	//save rip
	movq (%rsp), %rax
	movq %rax, (%rdi)

	//return 0
	xor %rax, %rax
	ret
.size setjmp, .-setjmp

.globl longjmp
.type longjmp @function
longjmp:
	//if rsi is 0 set it to 1
	cmp $0, %rsi
	jne skip
	mov $1, %rsi
	skip:

	//setup the return value
	movq %rsi, %rax
	
	//restore callee saved register
	movq 8(%rdi) , %rsp
	movq 16(%rdi), %rbp
	movq 24(%rdi), %rcx
	movq 32(%rdi), %r12
	movq 40(%rdi), %r13
	movq 48(%rdi), %r14
	movq 56(%rdi), %r15

	//return to the saved rip
	mov (%rdi), %rsi
	jmp *%rsi
.size longjmp, .-longjmp

.globl sigsetjmp
.type sigsetjmp @function
sigsetjmp:
	push rdi
	push rsi
	call __sigsavemask
	pop rsi
	pop rdi
	jmp setjmp
.size sigsetjmp, .-sigsetjmp

