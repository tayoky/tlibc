.globl trunc
.type trunc @function
trunc:
	frintz d0, d0
	ret
.size trunc, .-trunc
