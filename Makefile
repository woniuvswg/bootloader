CC = arm-linux-gcc
LD = arm-linux-ld
OBJCOPY = arm-linux-objcopy 
OBJDUMP = arm-linux-objdump
VPATH += driver 

INCDIR := include
DRIVERINC := include/driver
DRIVERDIR := driver
CFLAGS := -Wall -o2 -fno-builtin  -I $(INCDIR) -I $(DRIVERINC)
CPPFLAGS := -nostdinc -nostdlib
objs := start.o init.o boot.o $(addprefix $(DRIVERDIR)/, nand.o uart.o led.o)

export CC LD OBJCOPY OBJDUMP CFLAGS CPPFLAGS

all: dobj sobj boot.bin

boot.bin:
	$(LD) -Tboot.lds -o boot.elf $(objs)
	$(OBJCOPY) -O binary -S boot.elf $@
	$(OBJDUMP) -D -m arm boot.elf > boot.dis

dobj: 
	$(MAKE) -C driver
	
sobj: start.o init.o boot.o 

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

%.o: %.S
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

.PHONY: clean allclean
	
clean:
	rm -rf *.o *.bin *.elf *.dis

allclean:
	rm -rf *