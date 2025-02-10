global _start
extern main
_start:
	call __tlibc_init
	call main
	mov rdi, rax ;mov arg0 = return value of main
	xor rax,rax ; syscall exit
	int 80h
__tlibc_init:
	ret