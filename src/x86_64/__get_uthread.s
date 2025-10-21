.section .text

.globl __get_uthread
.type __get_uthread @function
__get_uthread:
    movq %gs:0, %rax
    ret