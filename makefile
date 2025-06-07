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

ifeq (${NEED_CONF},yes)
include config.mk
endif

TARGET = stanix

#first get all the src
C_SRC_DIR = stdio ${TARGET} ${ARCH}
C_SRC = $(shell find src -maxdepth 1 -name "*.c") $(foreach DIR, ${C_SRC_DIR}, $(shell find src/${DIR} -name "*.c" -or -name "*.s"))
C_OBJ = $(addsuffix .o, $(basename ${C_SRC}))

#if a file exist in math/${ARCH} don't take the generic version in math/generic
M_ARCH_SRC = $(shell find math/${ARCH} -name "*.c" -or -name "*.s")
M_SRC = ${M_ARCH_SRC} $(filter-out $(foreach FILE,${M_ARCH_SRC},%/$(shell basename $(basename ${FILE})).%),$(shell find math/generic -name "*.c" ))
M_OBJ = $(addsuffix .o, $(basename ${M_SRC}))

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
	-I include/${TARGET}

all : header tlibc.a libm.a crt/${ARCH}/crti.o crt/${ARCH}/crtn.o crt/${ARCH}/crt0-${TARGET}.o

test-m:
	@echo "C_SRC = ${C_SRC}"
	echo ${M_SRC}
	echo ${M_ARCH_SRC}
	echo $(foreach FILE,${M_ARCH_SRC},%/$(shell basename $(basename ${FILE})).%)
tlibc.a : ${C_OBJ}
	${AR} rcs $@ $^
libm.a : ${M_OBJ}
	${AR} rcs $@ $^
%.o : %.c
	${CC} ${CFLAGS} -D${ARCH} -o $@ -c $^
%.o : %.s
	${AS} ${ASFLAGS} $^ -o $@

clean : 
	rm -f ${C_OBJ} ${M_OBJ} crt0.o

#install the header
header :
	@mkdir -p ${PREFIX}/include/sys
	@echo "//TARGET=${TARGET}" > config.h
	@echo "//ARCH=${ARCH}" >> config.h
	@echo "//DATE=$(shell date)" >> config.h
	@echo ""  >> config.h
	@$(foreach FILE , $(shell echo include/*.h include/${TARGET}/*.h) , cat credit.h config.h ${FILE} > ${PREFIX}/include/$(shell basename ${FILE}) && echo "[installing $(shell basename ${FILE})]" &&) true
	@$(foreach FILE , $(shell echo include/${TARGET}/sys/*.h) , cat credit.h config.h ${FILE} > ${PREFIX}/include/sys/$(shell basename ${FILE}) && echo "[installing sys/$(shell basename ${FILE})]" &&) true
install : header all
	@mkdir -p ${PREFIX}/lib
	@echo "[install crti.o]"
	@cp crt/${ARCH}/crti.o ${PREFIX}/lib
	@echo "[install crtn.o]"
	@cp crt/${ARCH}/crtn.o ${PREFIX}/lib
	@echo "[install crt0.o]"
	@cp crt/${ARCH}/crt0-${TARGET}.o ${PREFIX}/lib/crt0.o
	@echo "[install libc.a]"
	@cp tlibc.a ${PREFIX}/lib/libc.a
	@echo "[install libm.a]"
	@cp libm.a ${PREFIX}/lib/libm.a
config.mk :
	$(error run ./configure before running make)
.mk :
