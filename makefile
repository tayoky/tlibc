MAKEFLAGS += --no-builtin-rules

#first get all the src
SRC_C = $(shell find -name "*.c")
SRC_ASM = $(shell find -name "*.s")
OBJ = ${SRC_C:.c=.o} ${SRC_ASM:.s=.o}

OUT = tlibc.a

#util
CC = gcc
LD = ld
NASM = nasm

#ld flags
LDFLAGS += \
	-m elf_x86_64 \
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
	-mcmodel=kernel
CFLAGS += -I ./include

all : ${OUT}

${OUT} : ${OBJ}
	${LD} ${LDFLAGS} -o tlibc.o ${OBJ}
	ar rcs ${OUT} tlibc.o

%.o : %.c
	${CC} ${CFLAGS} -r -o $@ -g -c $^
%.o : %.s
	${NASM} ${ASMFLAGS} $< -o $@

clean : 
	rm -f ${OBJ}