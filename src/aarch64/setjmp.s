.globl setjmp
.type setjmp @function
setjmp:
	//save return address
	str lr, [x0]

	//save callee saved register
	mov x1, sp
	str x1 , [x0,8]
	str fp , [x0,16]
	str x19, [x0,24]
	str x20, [x0,32]
	str x21, [x0,40]
	str x22, [x0,48]
	str x23, [x0,56]
	str x24, [x0,64]
	str x25, [x0,72]
	str x26, [x0,80]
	str x27, [x0,88]
	str x28, [x0,96]

	//return 0
	mov x0, xzr
	ret
.size setjmp, .-setjmp

.globl longjmp
.type longjmp @function
longjmp:
	//if x1 is 0 set it to 1
	cmp x1, xzr
	bne skip
	mov x1, xzr
	skip:

	//restore callee saved register
	ldr x2 , [x0,8]
	mov sp , x2
	ldr fp , [x0,16]
	ldr x19, [x0,24]
	ldr x20, [x0,32]
	ldr x21, [x0,40]
	ldr x22, [x0,48]
	ldr x23, [x0,56]
	ldr x24, [x0,64]
	ldr x25, [x0,72]
	ldr x26, [x0,80]
	ldr x27, [x0,88]
	ldr x28, [x0,96]

	//return the specified value
	mov x0, x1
	ret
.size longjmp, .-longjmp
