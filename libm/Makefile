TOP = $(CURDIR)/..
TMAKE_DIR = $(TOP)/make
include $(TMAKE_DIR)/tlibc-init.mk

#if a file exist in $(ARCH) don't take the generic version in generic
ARCH_SRCS = $(wildcard $(ARCH)/*.[sc])
SRCS = $(ARCH_SRCS) $(filter-out $(ARCH_SRCS:$(ARCH)/%.s=generic/%.c),$(wildcard generic/*.c))

LIB = m
LDFLAGS += -lc -Wl,-lgcc_s
include $(TMAKE_DIR)/tmake-lib.mk
