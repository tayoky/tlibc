TOP = $(CURDIR)/..
TMAKE_DIR = $(TOP)/make
include $(TMAKE_DIR)/tlibc-init.mk
include $(TMAKE_DIR)/tlibc-sysdeps.mk

C_DIRS = ctype libgen libintl time stdlib string wchar stdio unistd locale pwd pthread dl fcntl sys signal $(ARCH)
C_SRCS += $(foreach DIR,$(C_DIRS), $(wildcard $(DIR)/*.[cs])) $(wildcard *.c)

LIB = c
SRCDIRS += $(C_DIRS)
SRCS += $(notdir $(C_SRCS))
include $(TMAKE_DIR)/tmake-lib.mk
