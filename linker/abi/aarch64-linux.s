.section .text
.hidden abi_enter
.extern memcpy
.globl abi_enter
.type abi_enter @function
abi_enter:
	ret
.size abi_enter, .-abi_enter
