MAKEFLAGS += --no-builtin-rules

ifeq ($(findstring $(MAKECMDGOALS),clean header),)
include config.mk
endif

TARGET = stanix

#first get all the src
C_SRC_DIR = stdio ${TARGET} ${ARCH}
C_SRC = $(shell find src -maxdepth 1 -name "*.c") $(foreach DIR, ${C_SRC_DIR}, $(shell find src/${DIR} -name "*.c" -or -name "*.s"))
C_OBJ = $(addsuffix .o, $(basename ${C_SRC}))
M_SRC_DIR = generic ${ARCH}
M_SRC = $(shell find math -maxdepth 1 -name "*.c") $(foreach DIR, ${M_SRC_DIR}, $(shell find math/${DIR} -name "*.c" -or -name "*.s"))
M_OBJ = $(addsuffix .o, $(basename ${M_SRC}))

#ld flags
LDFLAGS += \
	-nostdlib \
	-static \

#cc flags
CFLAGS = -Wall \
	-Wextra \
	-std=gnu11 \
	-ffreestanding \
	-fno-stack-protector \
	-fno-stack-check \
	-fno-PIC \
	-nostdlib 

CFLAGS += --sysroot=${SYSROOT} -isystem ${SYSROOT}/include -isystem ${SYSROOT}/usr/include/ -I ./include/

all : header tlibc.a libm.a crt0.o
	echo ${C_OBJ}

tlibc.a : ${C_OBJ}
	${AR} rcs $@ $^
libm.a : ${M_OBJ}
	${AR} rcs $@ $^
%.o : %.c
	${CC} ${CFLAGS} -D${ARCH} -o $@ -c $^
%.o : %.s
	${AS} ${ASFLAGS} $^ -o $@

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
	cp crt*.o ${PREFIX}/lib 
	cp tlibc.a ${PREFIX}/lib/libc.a
	cp libm.a ${PREFIX}/lib/libm.a
config.mk :
	$(error run ./configure before running make)
.mk :
