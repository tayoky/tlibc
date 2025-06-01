.section .text
.globl sqrt
.type sqrt @function
sqrt:
	fsqrt d0 ,d0
	ret
.size sqrt, .-sqrt
