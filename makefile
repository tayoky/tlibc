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
C_SRC = $(wildcard libc/*.c) $(foreach DIR, $(C_SRC_DIR), $(wildcard libc/$(DIR)/**.[cs]))
C_OBJ = $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(C_SRC))))
C_SHARED_OBJ = $(addprefix $(BUILDDIR)/shared-, $(addsuffix .o, $(basename $(C_SRC))))

# objects used in libk
K_SRC = errno.o string/memset.o string/memcpy.o string/memchr.o string/memcmp.o string/strcat.o string/strlen.o  string/strnlen.o string/strcpy.o string/strncpy.o string/strcmp.o string/strncmp.o string/strncasecmp.o ctype/ctype.o stdio/vsnprintf.o stdio/snprintf.o stdio/vsprintf.o stdio/sprintf.o stdlib/strto.o
K_OBJ = $(foreach FILE, $(K_SRC), $(BUILDDIR)/libk/$(FILE))

#if a file exist in libm/$(ARCH) don't take the generic version in libm/generic
M_ARCH_SRC = $(wildcard libm/$(ARCH)/**.[cs])
M_SRC = $(M_ARCH_SRC) $(filter-out $(foreach FILE,$(M_ARCH_SRC),libm/generic/$(shell basename $(basename $(FILE))).%),$(wildcard libm/generic/**.c))
M_OBJ = $(addprefix $(BUILDDIR)/,$(addsuffix .o, $(basename $(M_SRC))))
M_SHARED_OBJ = $(addprefix $(BUILDDIR)/shared-, $(addsuffix .o, $(basename $(M_SRC))))

# libc object used by linker
DL_DEPS = tlibc pthread/uthread $(ARCH)/__get_uthread errno ctype/ctype \
	string/strcmp string/strchr string/strrchr string/strcpy string/strlen string/strnlen \
	string/memset string/memcmp string/memchr string/memcpy \
	stdio/vsnprintf stdio/vsprintf stdio/sprintf stdio/fwrite stdio/__fileio_write stdio/fflush\
	stdio/puts stdio/putchar stdio/fputs stdio/fputc stdio/stdio stdio/vfprintf stdio/fprintf\
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
	-ffreestanding \
	-I include \
	-I include/$(TARGET) \
	-D$(ARCH)=1

STATICFLAGS = -fno-PIC
DYNFLAGS = -fPIC -D__DYNAMIC__=1
SOFLAGS = -nolibc -shared

KFLAGS = -mcmodel=large -D__LIBK__=1 -Dmalloc=kmalloc -Dfree=kfree -ffreestanding
ifeq ($(ARCH),x86_64)
	KFLAGS += -mno-sse -mno-sse2 -mno-80387 -mno-80387
endif

DLFLAGS = -D__DL_TLIBC__=1 -fPIC -mgeneral-regs-only -fvisibility=hidden

ALL = libc.a libk.a libm.a libpthread.a libdl.a $(BUILDDIR)/crt/$(ARCH)/crti.o $(BUILDDIR)/crt/$(ARCH)/crtn.o $(BUILDDIR)/crt/$(ARCH)/crt0-$(TARGET).o

ifeq ($(DYNAMIC),yes)
	ALL += libc.so libm.so ld-tlibc.so
endif

INSTALL_TARGET = header all

ifeq ($(DYNAMIC),yes)
	INSTALL_TARGET += install-dynamic
endif

define install_lib
	@echo "[install $(1)]"
	@cp $(1) "$(PREFIX)/lib/$(1)"
endef

MAKE_DIRS = @mkdir -p $(shell dirname $@)
BUILD_ARCHIVE = $(AR) rcs $@ $^

all : $(ALL)

libc.a : $(C_OBJ)
	$(BUILD_ARCHIVE)

libk.a : $(K_OBJ)
	$(BUILD_ARCHIVE)

libpthread.a : $(BUILDDIR)/stub/pthread.o
	$(BUILD_ARCHIVE)

libdl.a : $(BUILDDIR)/stub/dl.o
	$(BUILD_ARCHIVE)

libm.a : $(M_OBJ)
	$(BUILD_ARCHIVE)

ld-tlibc.so : $(DL_OBJ) $(BUILDDIR)/crt/$(ARCH)/crt0-$(TARGET).o
	$(CC) $(DLFLAGS) -nostdlib -o $@ $^ -shared -static-libgcc -Wl,--no-dynamic-linker,-z,now,-soname,ld-tlibc.so

libc.so : $(C_SHARED_OBJ) ld-tlibc.so
	$(CC) $(DYNFLAGS) $(SOFLAGS) -Wl,-soname,libc.so -o $@ $^

libm.so : $(M_SHARED_OBJ) libc.so
	$(CC) $(DYNFLAGS) $(SOFLAGS) -Wl,-soname,libm.so -o $@ $^

libdl.so : $(BUILDDIR)/shared-stub/dl.o
	$(CC) $(DYNFLAGS) $(SOFLAGS) -Wl,-soname,libdl.so -o $@ $^

libpthread.so : $(BUILDDIR)/shared-stub/pthread.o
	$(CC) $(DYNFLAGS) $(SOFLAGS) -Wl,-soname,libpthread.so -o $@ $^

$(BUILDDIR)/%.o : %.c
	$(MAKE_DIRS)
	$(CC) $(CFLAGS) -o $@ -c $^

$(BUILDDIR)/shared-%.o : %.c
	$(MAKE_DIRS)
	$(CC) $(CFLAGS) -o $@ -c $^

$(BUILDDIR)/shared-%.o : %.s
	$(MAKE_DIRS)
	$(AS) $(ASFLAGS) -o $@ $^

$(BUILDDIR)/%.o : %.s
	$(MAKE_DIRS)
	$(AS) $(ASFLAGS) -o $@ $^
 
$(BUILDDIR)/libk/%.o: libc/%.c
	$(MAKE_DIRS)
	$(CC) $(CFLAGS) -o $@ -c $^

$(BUILDDIR)/linker/%.o : libc/%.c
	$(MAKE_DIRS)
	$(CC) $(CFLAGS) -o $@ -c $^

$(BUILDDIR)/linker/%.o : libc/%.s
	$(MAKE_DIRS)
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

install : $(INSTALL_TARGET)
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

.PHONY : all install install-dynamic header clean
