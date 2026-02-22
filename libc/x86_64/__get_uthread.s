.section .text

.globl __get_uthread
.type __get_uthread @function
__get_uthread:
    movq %fs:0, %rax
    ret
.size __get_uthread, .-__get_uthread