.section .text
.globl sqrt
.type sqrt @function
sqrt:
	fsqrt d0 ,d0
	ret
.size sqrt, .-sqrt

.globl sqrtf
.type sqrtf @function
sqrtf:
	fsqrt s0, s0
	ret
.size sqrtf, .-sqrtf
