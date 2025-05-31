.section .text
.globl sqrt
.type sqrt @function
sqrt:
	sqrtsd xxm0, xxm0
	ret
