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

.section .init_array
.globl _init_array_start
_init_array_start:

.section .fini_array
.globl _fini_array_start
_fini_array_start:
