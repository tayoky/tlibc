.globl floorf
.type floorf @function
floorf:
	frintm s0, s0
	ret
.size floorf, .-floorf
