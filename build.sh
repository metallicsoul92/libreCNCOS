nasm -f elf arch/x64/boot.asm -o bin/boot/boot.o
gcc -m32 -ffreestanding -c kernel/kernel.c -o bin/kernel/kernel.o
nasm -f elf arch/x64/modes.asm -o bin/boot/modes.o
ld -m elf_i386 -T tools/linker.ld -o bin/bin/kernel.bin bin/boot/boot.o bin/kernel/kernel.o bin/boot/modes.o
