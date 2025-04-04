MAKEFLAGS += --no-builtin-rules

include config.mk

TARGET = stanix

#first get all the src
SRC_C = $(shell find src -maxdepth 1 -name "*.c") $(shell find src/stdio -name "*.c") $(shell find src/${TARGET} -name "*.c") $(shell find src/math -name "*.c")
SRC_ASM = $(shell find src -maxdepth 1 -name "*.s")
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

include ${ARCH}.mk

CFLAGS += --sysroot=${SYSROOT} -isystem ${SYSROOT}/include -isystem ./include/${TARGET}

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
	mkdir -p ${SYSROOT}/usr/include/sys
	cp ./include/*.h ${SYSROOT}/usr/include
	cp ./include/${TARGET}/*.h ${SYSROOT}/usr/include
	cp ./include/${TARGET}/sys/*.h ${SYSROOT}/usr/include/sys
install : header all
	mkdir -p ${SYSROOT}/usr/lib 
	cp crt0.o ${SYSROOT}/usr/lib 
	cp ${OUT} ${SYSROOT}/usr/lib/libc.a
config.mk :
	$(error run ./configure before running make)
.mk :