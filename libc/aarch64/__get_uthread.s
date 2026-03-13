.globl __get_uthread
.type __get_uthread @function
__get_uthread:
	mrs x0, tpidr_el0
	ret
