.section .init
	/* crtend.o's init section here */
	pop %rbp
	ret

.section .fini
	/* crtbegin.o's fini section here */
	pop %rbp
	ret

.section .init_array
.globl _init_array_end
_init_array_end:

.section .fini_array
.globl _fini_array_end
_fini_array_end:
