CFLAGS = -Wall -Wextra -Wconversion -std=c99 -pedantic -ggdb
OBJ = arm32_aeabi_divmod.o libc.o librp2040.o \
	firmware.o

all: firmware.elf firmware.asm

clean:
	rm -f *.o *.asm *.elf *.map *.uf2

ocd:
	${OPENOCD}

gdb:
	${GDB} -x script.gdb

include librp2040.mk
