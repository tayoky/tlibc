.globl round
.type round @function
round:
	frinta d0, d0
	ret
.size round, .-round

.globl roundf
.type roundf @function
roundf:
	frinta s0, s0
	ret
.size roundf, .-roundf
