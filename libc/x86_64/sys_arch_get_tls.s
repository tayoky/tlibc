.section .text

.globl sys_arch_get_tls
.hidden sys_arch_get_tls
.type sys_arch_get_tls @function
sys_arch_get_tls:
    movq %fs:0, %rax
    ret
.size sys_arch_get_tls, .-sys_arch_get_tls
