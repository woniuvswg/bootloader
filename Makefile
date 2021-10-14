CC = arm-linux-gcc
LD = arm-linux-ld
OBJCOPY = arm-linux-objcopy 
OBJDUMP = arm-linux-objdump

VPATH += driver  
INCDIR := $(shell pwd)/include
DRIVERDIR := $(shell pwd)/include/driver
CFLAGS := -Wall -o2 -fno-builtin  -I $(INCDIR) -I $(DRIVERDIR)
CPPFLAGS := -nostdinc -nostdlib
 
export CC LD OBJCOPY OBJDUMP CFLAGS CPPFLAGS

objs := start.o init.o nand.o uart.o led.o boot.o

boot.bin: $(objs)
	$(LD) -Tboot.lds -o boot.elf $^
	$(OBJCOPY) -O binary -S boot.elf $@
	$(OBJDUMP) -D -m arm boot.elf > boot.dis

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

%.o: %.S
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

.PHONY: clean allclean

clean:
	rm -rf *.o *.bin *.elf *.dis

allclean:
	rm -rf *