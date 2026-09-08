.section .text
.hidden enter_program
.globl enter_program
.type enter_program @function
enter_program:
// reset the stack
	mov $0, %rbp
	mov %rsi, %rsp

// jump to the entry point
	jmp *%rdi
.size enter_program, .-enter_program
