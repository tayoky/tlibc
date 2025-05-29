MAKEFLAGS += --no-builtin-rules

ifeq ($(findstring $(MAKECMDGOALS),clean header),)
include config.mk
endif

TARGET = stanix

#first get all the src
SRC_C = $(shell find src -maxdepth 1 -name "*.c") $(shell find src/stdio -name "*.c") $(shell find src/${TARGET} -name "*.c") $(shell find src/math -name "*.c")
SRC_ASM = $(shell find src -maxdepth 1 -name "*.s") src/setjmp/${ARCH}.s
OBJ = ${SRC_C:.c=.o} ${SRC_ASM:.s=.o}

OUT = tlibc.a

#default nasm
NASM = nasm

#ld flags
LDFLAGS += \
	-nostdlib \
	-static \
#nasm flags
ASMFLAGS += -Wall \
	-f elf64

#cc flags
CFLAGS = -Wall \
	-Wextra \
	-std=gnu11 \
	-ffreestanding \
	-fno-stack-protector \
	-fno-stack-check \
	-fno-PIC \
	-nostdlib 
ifeq ($(findstring $(MAKECMDGOALS),clean header),)
include ${ARCH}.mk
endif

CFLAGS += --sysroot=${SYSROOT} -isystem ${SYSROOT}/include -isystem ${SYSROOT}/usr/include/ -I ./include/

all : header ${OUT} crt0.o

${OUT} : ${OBJ}
	${AR} rcs ${OUT} ${OBJ}

%.o : %.c
	${CC} ${CFLAGS} -D${ARCH} -o $@ -c $^
%.o : %.s
	${NASM} ${ASMFLAGS} $< -o $@

clean : 
	rm -f ${OBJ} crt0.o

#install the header
header :
	mkdir -p ${PREFIX}/include/sys
	@echo "//TARGET=${TARGET}" > config.h
	@echo "//ARCH=${ARCH}" >> config.h
	@echo "//DATE=$(shell date)" >> config.h
	@echo ""  >> config.h
	@$(foreach FILE , $(shell echo include/*.h include/${TARGET}/*.h) , cat credit.h config.h ${FILE} > ${PREFIX}/include/$(shell basename ${FILE}) && echo "[installing $(shell basename ${FILE})]" &&) true
	@$(foreach FILE , $(shell echo include/${TARGET}/sys/*.h) , cat credit.h config.h ${FILE} > ${PREFIX}/include/sys/$(shell basename ${FILE}) && echo "[installing sys/$(shell basename ${FILE})]" &&) true
#	cp ./include/*.h ${PREFIX}/include
#	cp ./include/${TARGET}/*.h ${PREFIX}/include
#	cp ./include/${TARGET}/sys/*.h ${PREFIX}/include/sys
install : header all
	mkdir -p ${PREFIX}/lib 
	cp crt0.o ${PREFIX}/lib 
	cp ${OUT} ${PREFIX}/lib/libc.a
config.mk :
	$(error run ./configure before running make)
.mk :
