TOP = $(CURDIR)/..
TMAKE_DIR = $(TOP)/make
include $(TMAKE_DIR)/tlibc-init.mk

LIB = k
SRCDIRS = $(TOP)/libc/ $(TOP)/libc/string/ $(TOP)/libc/ctype $(TOP)/libc/stdio $(TOP)/libc/stdlib
SRCS = errno.c memset.c memcpy.c memchr.c memcmp.c strcat.c strlen.c strnlen.c strcpy.c strncpy.c strcmp.c strncmp.c strchr.c strstr.c strncasecmp.c ctype.c vsnprintf.c snprintf.c vsprintf.c sprintf.c strto.c
SHARED = no
include $(TMAKE_DIR)/tmake-lib.mk
