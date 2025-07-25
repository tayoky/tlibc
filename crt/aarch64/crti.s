.section .init
.globl _init
.type _init @function
_init:
	sub sp, sp, 16
	stp x29, x30, [sp]
	/* crtbegin.o's init section here */

.section .fini
.globl _fini
.type _fini @function
	sub sp, sp, 16
	stp x29, x30, [sp]
	/* crtbegin.o's fini section here */
