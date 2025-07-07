AS = aarch64-elf-as
CC = aarch64-elf-gcc
LD = aarch64-elf-ld 
OBJCOPY = aarch64-elf-objcopy 

CFLAGS = -ffreestanding -nostdlib -nostartfiles -O2
LDFLAGS = -T link.ld 

SRC = start.s main.c 
OBJ = start.o main.o 

all: kernel8.img

start.o: start.s
	$(AS) $< -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

kernel8.elf: $(OBJ)
	$(LD) $(LDFLAGS) -o $@ $^

kernel8.img: kernel8.elf
	$(OBJCOPY) -O binary $< $@

clean:
	rm -f *.o *.elf *.img

.PHONY: all clean