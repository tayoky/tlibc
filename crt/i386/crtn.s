.section .init
	/* crtend.o's init section here */
	pop %ebp
	ret

.section .fini
	/* crtbegin.o's fini section here */
	pop %ebp
	ret
