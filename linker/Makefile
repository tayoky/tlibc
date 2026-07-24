TOP = $(CURDIR)/..
TMAKE_DIR = $(TOP)/make
include $(TMAKE_DIR)/tlibc-init.mk
include $(TMAKE_DIR)/tlibc-sysdeps.mk

# libc objects used by linker
DL_DEPS = tlibc.c stub.c auxv.c cxa.c uthread.c sys_arch_get_tls.s open.c errno.c ctype.c \
	read.c write.c lseek.c close.c _exit.c \
	getuid.c geteuid.c getgid.c getegid.c getpid.c \
	mmap.c mprotect.c munmap.c \
	strcmp.c strncmp.c strchr.c strrchr.c strcpy.c strlen.c strnlen.c \
	memset.c memcmp.c memchr.c memcpy.c \
	vsnprintf.c vsprintf.c sprintf.c fwrite.c __fileio_write.c fflush.c \
	puts.c putchar.c fputs.c fputc.c stdio.c vfprintf.c fprintf.c \
	exit.c environ.c getenv.c

CFLAGS += -I.
CFLAGS += -D__LD_TLIBC__=1 -fPIC -mgeneral-regs-only -fvisibility=hidden
LDFLAGS += -static-libgcc -Wl,--no-dynamic-linker,-z,now,-Bsymbolic,-e,_start

LIB = ld-tlibc
SHARED_LIB = ld-tlibc.so
SRCDIRS += $(TOP)/libc/ $(TOP)/libc/pthread/ $(TOP)/libc/$(ARCH)/ \
	  $(TOP)/libc/fcntl/ $(TOP)/libc/ctype/ $(TOP)/libc/unistd/ \
	  $(TOP)/libc/sys/ \
	  $(TOP)/libc/string/ $(TOP)/libc/stdio/ $(TOP)/libc/stdlib/
SRCS += $(TOP)/crt/$(ARCH)/crt0-$(TARGET).s $(DL_DEPS) $(wildcard *.c) abi/$(ARCH)-$(TARGET).s
STATIC = no
include $(TMAKE_DIR)/tmake-lib.mk
