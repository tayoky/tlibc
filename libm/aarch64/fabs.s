.globl fabs
.type fabs @function
fabs:
	fabs d0, d0
	ret
.size fabs, .-fabs

.globl fabsf
.type fabsf @function
fabsf:
	fabs s0, s0
	ret
.size fabsf, .-fabsf
