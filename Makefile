NASM = nasm
GCC = x86_64-pc-msys-gcc
LD = ld

CFLAGS = -ffreestanding -nostdlib
LDFLAGS = -T tools/linker.ld

BIN = bin
BBOOT = $(BIN)/boot
BKERNEL = $(BIN)/kernel
BBIN = $(BIN)/bin


all: kernel.bin

kernel.bin: bin/boot/boot.o bin/boot/modes.o bin/kernel/kernel.o
	$(LD) $(LDFLAGS) -o $(BBIN)/$@ $^

arch/x64/boot.o: arch/x64/boot.asm
	$(NASM) -f elf64 $< -o $(BBOOT)/boot.o

arch/x64/modes.o: arch/x64/modes.asm
	$(NASM) -f elf64 $< -o $(BBOOT)/modes.o

kernel/kernel.o: kernel/kernel.c
	$(GCC) $(CFLAGS) -c $< -o $(BKERNEL)/kernel.o

clean:
	rm -f $(BBOOT)/boot.o $(BBOOT)/modes.o $(BKERNEL)/kernel.o $(BBIN)/kernel.bin
