MAKEFLAGS += --no-builtin-rules

NEED_CONF= yes
ifneq ($(findstring $(MAKECMDGOALS),clean),)
NEED_CONF= no
endif
ifneq ($(findstring $(MAKECMDGOALS),header),)
ifeq ($(wildcard config.mk),)
NEED_CONF= no
endif
endif

ifeq ($(NEED_CONF),yes)
include config.mk
endif

TARGET = stanix

BUILDDIR = build

# first get all the sources
C_SRC_DIR = ctype libgen time stdlib string wchar stdio unistd locale pwd pthread dl $(TARGET) $(ARCH)
C_SRC = $(shell find libc -maxdepth 1 -name "*.c") $(foreach DIR, $(C_SRC_DIR), $(shell find libc/$(DIR) -name "*.c" -or -name "*.s"))
C_OBJ = $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(C_SRC))))
C_SHARED_OBJ = $(addprefix $(BUILDDIR)/shared-, $(addsuffix .o, $(basename $(C_SRC))))

# objects used in libk
K_SRC = errno.o string/memset.o string/memcpy.o string/memchr.o string/memcmp.o string/strcat.o string/strlen.o  string/strnlen.o string/strcpy.o string/strncpy.o string/strcmp.o string/strncmp.o string/strncasecmp.o ctype/ctype.o stdio/vsnprintf.o stdio/snprintf.o stdio/vsprintf.o stdio/sprintf.o stdlib/strto.o
K_OBJ = $(foreach FILE, $(K_SRC), $(BUILDDIR)/libk/$(FILE))

#if a file exist in libm/$(ARCH) don't take the generic version in libm/generic
M_ARCH_SRC = $(shell find libm/$(ARCH) -name "*.c" -or -name "*.s")
M_SRC = $(M_ARCH_SRC) $(filter-out $(foreach FILE,$(M_ARCH_SRC),libm/generic/$(shell basename $(basename $(FILE))).%),$(shell find libm/generic -name "*.c" ))
M_OBJ = $(addprefix $(BUILDDIR)/,$(addsuffix .o, $(basename $(M_SRC))))
M_SHARED_OBJ = $(addprefix $(BUILDDIR)/shared-, $(addsuffix .o, $(basename $(M_SRC))))

# libc object used by linker
DL_DEPS = tlibc pthread/uthread $(ARCH)/__get_uthread errno ctype/ctype \
	string/strcmp string/strchr string/strcpy string/strlen string/strnlen \
	string/memset string/memcmp string/memchr string/memcpy \
	stdio/vsnprintf stdio/vsprintf stdio/sprintf stdio/fwrite stdio/__fileio_write stdio/fflush\
	stdio/puts stdio/putchar stdio/fputs stdio/fputc stdio/stdio\
	stdlib/exit stdlib/environ stdlib/getenv \
	$(basename $(shell cd libc && find $(TARGET) -name "*.c"))

DL_SRC = $(wildcard linker/*.c) linker/abi/$(ARCH)-$(TARGET)
DL_OBJ = $(addprefix $(BUILDDIR)/,$(addsuffix .o, $(addprefix linker/, $(DL_DEPS)) $(basename $(DL_SRC))))


# ld flags
LDFLAGS += \
	-nostdlib \
	-static \

# cc flags
CFLAGS += -Wall \
	-Wextra \
	-std=gnu99 \
	-fno-stack-protector \
	-fno-stack-check \
	-nostdlib \
	-I include \
	-I include/$(TARGET) \
	-D$(ARCH)=1

STATICFLAGS = -fno-PIC
DYNFLAGS = -fPIC -D__DYNAMIC__=1

KFLAGS = -mcmodel=large -DLIBK -Dmalloc=kmalloc -Dfree=kfree -ffreestanding
ifeq ($(ARCH),x86_64)
	KFLAGS += -mno-sse -mno-sse2 -mno-80387 -mno-80387
endif

DLFLAGS = -D__DL_TLIBC__=1 -fpie -mgeneral-regs-only

ALL = libc.a libk.a libm.a libpthread.a libdl.a $(BUILDDIR)/crt/$(ARCH)/crti.o $(BUILDDIR)/crt/$(ARCH)/crtn.o $(BUILDDIR)/crt/$(ARCH)/crt0-$(TARGET).o

ifeq ($(DYNAMIC),yes)
	ALL += libc.so libm.so ld-tlibc.so
endif

INSTALL_TARGET = all header

ifeq ($(DYNAMIC),yes)
	INSTALL_TARGET += install-dynamic
endif

define install_lib
	@echo "[install $(1)]"
	@cp $(1) "$(PREFIX)/lib/$(1)"
endef

all : $(ALL)

libc.a : $(C_OBJ)
	$(AR) rcs $@ $^

libk.a : $(K_OBJ)
	$(AR) rcs $@ $^

libpthread.a : $(BUILDDIR)/stub/pthread.o
	$(AR) rcs $@ $^

libdl.a : $(BUILDDIR)/stub/dl.o
	$(AR) rcs $@ $^

libm.a : $(M_OBJ)
	$(AR) rcs $@ $^

ld-tlibc.so : $(DL_OBJ) $(BUILDDIR)/crt/$(ARCH)/crt0-$(TARGET).o
	$(CC) -o $@ $^ -nostdlib -pie -static -static-libgcc -Wl,--no-dynamic-linker

libc.so : $(C_SHARED_OBJ)
	$(CC) -shared -o $@ $^ -nostdlib

libm.so : $(M_SHARED_OBJ)
	$(CC) -shared -o $@ $^ -nostdlib

$(BUILDDIR)/%.o : %.c
	@mkdir -p $(shell dirname $@)
	$(CC) $(CFLAGS) -o $@ -c $^

$(BUILDDIR)/shared-%.o : %.c
	@mkdir -p $(shell dirname $@)
	$(CC) $(CFLAGS) -o $@ -c $^

$(BUILDDIR)/shared-%.o : %.s
	@mkdir -p $(shell dirname $@)
	$(AS) $(ASFLAGS) -o $@ $^

$(BUILDDIR)/%.o : %.s
	@mkdir -p $(shell dirname $@)
	$(AS) $(ASFLAGS) -o $@ $^
 
$(BUILDDIR)/libk/%.o: libc/%.c
	@mkdir -p $(shell dirname $@)
	$(CC) $(CFLAGS) -o $@ -c $^

$(BUILDDIR)/linker/%.o : libc/%.c
	@mkdir -p $(shell dirname $@)
	$(CC) $(CFLAGS) -o $@ -c $^

$(BUILDDIR)/linker/%.o : libc/%.s
	@mkdir -p $(shell dirname $@)
	$(AS) $(ASFLAGS) -o $@ $^


$(BUILDDIR)/lib%.o : CFLAGS += $(STATICFLAGS)
$(BUILDDIR)/stub%.o : CFLAGS += $(STATICFLAGS)
$(BUILDDIR)/libk/%.o : CFLAGS += $(KFLAGS)
$(BUILDDIR)/shared-%.o : CFLAGS += $(DYNFLAGS)
$(BUILDDIR)/linker/% : CFLAGS += $(DLFLAGS)

clean : 
	rm -fr $(BUILDDIR)


#install the header
header :
	@mkdir -p $(PREFIX)/include/sys
	@$(foreach FILE , $(shell echo include/*.h include/$(TARGET)/*.h) , cat prologue.h $(FILE) epilogue.h > $(PREFIX)/include/$(shell basename $(FILE)) && echo "[installing $(shell basename $(FILE))]" &&) true
	@$(foreach FILE , $(shell echo include/$(TARGET)/sys/*.h) , cat prologue.h $(FILE) epilogue.h > $(PREFIX)/include/sys/$(shell basename $(FILE)) && echo "[installing sys/$(shell basename $(FILE))]" &&) true
	@cp include/_cdefs.h $(PREFIX)/include/sys/cdefs.h

install-dynamic : header
	@mkdir -p $(PREFIX)/lib
	$(call install_lib,libc.so)
	$(call install_lib,libm.so)
	$(call install_lib,ld-tlibc.so)

install : header all
	@mkdir -p $(PREFIX)/lib
	@echo "[install crti.o]"
	@cp $(BUILDDIR)/crt/$(ARCH)/crti.o $(PREFIX)/lib
	@echo "[install crtn.o]"
	@cp $(BUILDDIR)/crt/$(ARCH)/crtn.o $(PREFIX)/lib
	@echo "[install crt0.o]"
	@cp $(BUILDDIR)/crt/$(ARCH)/crt0-$(TARGET).o $(PREFIX)/lib/crt0.o
	$(call install_lib,libc.a)
	$(call install_lib,libm.a)
	$(call install_lib,libpthread.a)
	$(call install_lib,libdl.a)

config.mk :
	$(error run ./configure before running make)
.mk :
