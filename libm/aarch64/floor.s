.globl floor
.type floor @function
floor:
	frintm d0, d0
	ret
.size floor, .-floor
