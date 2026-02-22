.globl ceil
.type ceil @function
ceil:
	frintp d0, d0
	ret
.size ceil, .-ceil

.globl ceilf
.type ceilf @function
ceilf:
	frintp s0, s0
	ret
.size ceilf, .-ceilf
