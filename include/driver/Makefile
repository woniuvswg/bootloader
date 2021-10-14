CC = arm-linux-gcc

INCDIR := $(shell pwd)/../include/driver
CFLAGS := -Wall -o2 -fno-builtin -I $(INCDIR)
CPPFLAGS := -nostdinc -nostdlib
 
export CC LD OBJCOPY OBJDUMP CFLAGS CPPFLAGS

all : nand.o uart.o led.o

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

.PHONY: clean allclean all

clean:
	rm -rf *.o *.bin *.elf *.dis

allclean:
	rm -rf *