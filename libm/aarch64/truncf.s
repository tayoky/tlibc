.globl truncf
.type truncf @function
truncf:
	frintz s0, s0
	ret
.size truncf, .-truncf
