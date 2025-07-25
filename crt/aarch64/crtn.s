.section .init
	/* crtend.o's init section here */
	ldp x29, x30, [sp]
	add sp, sp, 16
	ret

.section .fini
	/* crtbegin.o's fini section here */
	ldp x29, x30, [sp]
	add sp, sp, 16
	ret
