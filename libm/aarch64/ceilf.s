.globl ceilf
.type ceilf @function
ceilf:
	frintp s0, s0
	ret
.size ceilf, .-ceilf
