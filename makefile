MAKEFLAGS += --no-builtin-rules

SYSROOT = sysroot
TARGET = stanix

#first get all the src
SRC_C = $(shell find src -maxdepth 1 -name "*.c") $(shell find src/stdio -name "*.c") $(shell find src/${TARGET} -name "*.c")
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
	-m64 \
	-march=x86-64 \
	-mno-80387 \
	-mno-mmx \
	-mno-sse \
	-mno-sse2 \
	-mno-red-zone \
	-mcmodel=kernel\
	-nostdlib
CFLAGS += --sysroot=./ -isystem ./include -isystem ./include/${TARGET}

all : ${OUT} crt0.o

${OUT} : ${OBJ}
	ar rcs ${OUT} ${OBJ}

%.o : %.c
	${CC} ${CFLAGS} -r -o $@ -g -c $^
%.o : %.s
	${NASM} ${ASMFLAGS} $< -o $@

clean : 
	rm -f ${OBJ}

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