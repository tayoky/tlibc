.globl floor
.type floor @function
floor:
	frintm d0, d0
	ret
.size floor, .-floor

.globl floorf
.type floorf @function
floorf:
	frintm s0, s0
	ret
.size floorf, .-floorf
