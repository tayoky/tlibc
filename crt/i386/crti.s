.section .init
.globl _init
.type _init @function
_init:
	push %ebp
	movq %esp, %ebp
	/* crtbegin.o's init section here */

.section .fini
.globl _fini
.type _fini @function
_fini:
	push %ebp
	movd %esp, %ebp
	/* crtbegin.o's fini section here */
