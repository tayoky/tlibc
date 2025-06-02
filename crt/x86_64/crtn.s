.section .init
	/* crtend.o's init section here */
	pop %rbp
	ret

.section .fini
	/* crtbegin.o's fini section here */
	pop %rbp
	ret
