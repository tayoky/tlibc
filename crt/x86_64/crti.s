.section .init
.globl _init
.type _init @function
_init:
	push %rbp
	movq %rsp, %rbp
	/* crtbegin.o's init section here */

.section .fini
.globl _fini
.type _fini @function
	push %rbp
	movq %rsp, %rbp
	/* crtbegin.o's fini section here */
