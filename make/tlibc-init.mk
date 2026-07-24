# makefile include to initalize defaults

include $(TMAKE_DIR)/tmake-init.mk

PACKAGE = tlibc

# build for stanix by default
TARGET=stanix

# freestanding environment setup
CFLAGS += -Wall \
	-Wextra \
	-Wno-unused-parameter \
	-std=gnu99 \
	-fno-stack-protector \
	-fno-stack-check \
	-fno-omit-frame-pointer \
	-nostdlib \
	-ffreestanding \
	-I "$(TOP)/include" \
	-I "$(TOP)/include/$(TARGET)" \
	-D$(ARCH)=1 \
	-D__TLIBC__

LDFLAGS += -Wl,--gc-sections

KFLAGS = -mcmodel=large -D__LIBK__=1 -Dmalloc=kmalloc -Dfree=kfree -ffreestanding -fno-PIC
ifeq ($(ARCH),x86_64)
	KFLAGS += -mno-sse -mno-sse2 -mno-80387 -mno-80387
endif
