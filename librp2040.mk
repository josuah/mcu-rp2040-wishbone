OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump
CC = arm-none-eabi-gcc -mthumb -mcpu=cortex-m0plus -msoft-float
LD = arm-none-eabi-ld
GDB = arm-none-eabi-gdb
OPENOCD = openocd -f board/pico-debug.cfg
MNT = /mnt

flash: firmware.uf2
	mount ${MNT} && cp firmware.uf2 ${MNT}

firmware.elf: ${OBJ}
	${LD} -Map=firmware.map --gc-sections -Tlibrp2040.ld -nostdlib -static ${LDFLAGS} -o $@ ${OBJ}

.SUFFIXES: .c .s .S .o .elf .asm .uf2

.S.o:
	${CC} ${CPPFLAGS} ${CFLAGS} -c -o $@ $<

.c.o:
	${CC} ${CPPFLAGS} ${CFLAGS} -ffunction-sections -fdata-sections -c -o $@ $<

.elf.asm:
	${OBJDUMP} -z -d $< >$@

.elf.uf2:
	elf2uf2 $< $@
