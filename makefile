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

BUILDDIR=build

#first get all the src
C_SRC_DIR = ctype libgen time stdlib string wchar stdio unistd locale pwd $(TARGET) $(ARCH)
C_SRC = $(shell find src -maxdepth 1 -name "*.c") $(foreach DIR, $(C_SRC_DIR), $(shell find src/$(DIR) -name "*.c" -or -name "*.s"))
C_OBJ = $(addprefix $(BUILDDIR)/,$(addsuffix .o, $(basename $(C_SRC))))

#object used in libk
K_SRC = ctype/ctype.o string/memcpy.o string/strlen.o string/strcpy.o string/strncpy.o stdio/vsnprintf.o stdio/snprintf.o stdio/vsprintf.o stdio/sprintf.o stdlib/realpath.o
K_OBJ = $(foreach FILE, $(K_SRC), $(BUILDDIR)/src/$(FILE))

#if a file exist in math/$(ARCH) don't take the generic version in math/generic
M_ARCH_SRC = $(shell find math/$(ARCH) -name "*.c" -or -name "*.s")
M_SRC = $(M_ARCH_SRC) $(filter-out $(foreach FILE,$(M_ARCH_SRC),math/generic/$(shell basename $(basename $(FILE))).%),$(shell find math/generic -name "*.c" ))
M_OBJ = $(addprefix $(BUILDDIR)/,$(addsuffix .o, $(basename $(M_SRC))))

#ld flags
LDFLAGS += \
	-nostdlib \
	-static \

#cc flags
CFLAGS += -Wall \
	-Wextra \
	-std=gnu99\
	-ffreestanding \
	-fno-stack-protector \
	-fno-stack-check \
	-fno-PIC \
	-nostdlib \
	-I include \
	-I include/$(TARGET)

all : tlibc.a tlibk.a libm.a $(BUILDDIR)/crt/$(ARCH)/crti.o $(BUILDDIR)/crt/$(ARCH)/crtn.o $(BUILDDIR)/crt/$(ARCH)/crt0-$(TARGET).o

tlibc.a : $(C_OBJ)
	$(AR) rcs $@ $^

tlibk.a : $(K_OBJ)
	$(AR) rcs $@ $^

libm.a : $(M_OBJ)
	$(AR) rcs $@ $^

$(BUILDDIR)/%.o : %.c
	@mkdir -p $(shell dirname $@)
	$(CC) $(CFLAGS) -D$(ARCH) -o $@ -c $^

$(BUILDDIR)/%.o : %.s
	@mkdir -p $(shell dirname $@)
	$(AS) $(ASFLAGS) -o $@ $^

clean : 
	rm -fr $(BUILDDIR)


#install the header
header :
	@mkdir -p $(PREFIX)/include/sys
	@$(foreach FILE , $(shell echo include/*.h include/$(TARGET)/*.h) , cat prologue.h $(FILE) epilogue.h > $(PREFIX)/include/$(shell basename $(FILE)) && echo "[installing $(shell basename $(FILE))]" &&) true
	@$(foreach FILE , $(shell echo include/$(TARGET)/sys/*.h) , cat prologue.h $(FILE) epilogue.h > $(PREFIX)/include/sys/$(shell basename $(FILE)) && echo "[installing sys/$(shell basename $(FILE))]" &&) true
	@cp include/_cdefs.h $(PREFIX)/include/sys/cdefs.h

install : header all
	@mkdir -p $(PREFIX)/lib
	@echo "[install crti.o]"
	@cp $(BUILDDIR)/crt/$(ARCH)/crti.o $(PREFIX)/lib
	@echo "[install crtn.o]"
	@cp $(BUILDDIR)/crt/$(ARCH)/crtn.o $(PREFIX)/lib
	@echo "[install crt0.o]"
	@cp $(BUILDDIR)/crt/$(ARCH)/crt0-$(TARGET).o $(PREFIX)/lib/crt0.o
	@echo "[install libc.a]"
	@cp tlibc.a $(PREFIX)/lib/libc.a
	@echo "[install libm.a]"
	@cp libm.a $(PREFIX)/lib/libm.a
config.mk :
	$(error run ./configure before running make)
.mk :
