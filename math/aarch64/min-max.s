.globl fmin
.type fmin @function
fmin:
	fminnm d0, d0, d1
	ret
.size fmin, .-fmin

.globl fminf
.type fminf @function
fminf:
	fminnm s0, s0, s1
	ret
.size fminf, .-fminf

.globl fmax
.type fmax @function
fmax:
	fmaxnm d0, d0, d1
	ret
.size fmax, .-fmax

.globl fmaxf
.type fmaxf @function
fmaxf:
	fmaxnm s0, s0, s1
	ret
.size fmaxf, .-fmaxf
