TOP = $(CURDIR)/..
TMAKE_DIR = $(TOP)/make
include $(TMAKE_DIR)/tlibc-init.mk

LIB = k
SRCDIRS = $(TOP)/libc/ $(TOP)/libc/string/ $(TOP)/libc/ctype $(TOP)/libc/stdio $(TOP)/libc/stdlib
SRCS = errno.c memset.c memcpy.c memchr.c memcmp.c strcat.c strlen.c strnlen.c strcpy.c strncpy.c strcmp.c strncmp.c strchr.c strstr.c strncasecmp.c strtok_r.c ctype.c vsnprintf.c snprintf.c vsprintf.c sprintf.c strto.c
SHARED = no
CFLAGS += \
	-std=gnu11 \
	-ffreestanding \
	-fno-stack-protector \
	-fno-stack-check \
	-fno-PIC \
	-fno-omit-frame-pointer \
	-fsanitize=undefined \
	-D__LIBK__=1

ifeq ($(ARCH),x86_64)
CFLAGS += -mcmodel=kernel
endif

include $(TMAKE_DIR)/tmake-lib.mk
