.globl sys_arch_get_tls
.type sys_arch_get_tls @function
sys_arch_get_tls:
	mrs x0, tpidr_el0
	ret
