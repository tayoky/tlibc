global _start
_start:
	call __tlibc_init
	call main
__tlibc_init
	ret