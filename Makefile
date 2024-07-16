NASM = nasm
GCC32 = x86_64-gcc -m32
GCC64 = gcc -m64
LD = ld

CFLAGS32 = -ffreestanding -nostdlib -m32 -Iinclude -Ilibc/crt/include -Ilibc/posix/include
CFLAGS64 = -ffreestanding -nostdlib -m64 -Iinclude -Ilibc/crt/include -Ilibc/posix/include
LDFLAGS = -T tools/linker.ld

BINDIR = bin

SUBDIRS = arch/x86 arch/x64 drivers/fs/vfs kernel kernel/mm kernel/sc libc/crt/src libc/posix/src osutils

OBJS32 = $(BINDIR)/arch/x86/bootloader.o
OBJS64 = $(BINDIR)/arch/x64/kernel_entry.o $(BINDIR)/arch/x64/gdt.o $(BINDIR)/arch/x64/paging.o $(BINDIR)/kernel/kernel.o $(BINDIR)/kernel/idt.o $(BINDIR)/kernel/isr.o $(BINDIR)/kernel/mm/kmalloc.o $(BINDIR)/kernel/mm/memory.o $(BINDIR)/kernel/mm/pmm.o $(BINDIR)/kernel/sc/mmap.o $(BINDIR)/kernel/sc/sbrk.o $(BINDIR)/kernel/task.o $(BINDIR)/kernel/tty.o $(BINDIR)/kernel/vga.o $(BINDIR)/drivers/fs/vfs/vfs.o $(BINDIR)/libc/crt/locale.o $(BINDIR)/libc/crt/math.o $(BINDIR)/libc/crt/setjmp.o $(BINDIR)/libc/crt/signal.o $(BINDIR)/libc/crt/stdio.o $(BINDIR)/libc/crt/stdlib.o $(BINDIR)/libc/crt/string.o $(BINDIR)/libc/crt/time.o $(BINDIR)/libc/crt/wchar.o $(BINDIR)/libc/posix/fcntl.o $(BINDIR)/libc/posix/libgen.o $(BINDIR)/libc/posix/sys/stat.o $(BINDIR)/libc/crt/errno.o $(BINDIR)/osutils/io_utils.o

.PHONY: all clean $(SUBDIRS)

all: $(BINDIR)/kernel.bin

$(BINDIR)/kernel.bin: $(SUBDIRS) $(OBJS32) $(OBJS64)
	$(LD) $(LDFLAGS) -o $@ $(OBJS32) $(OBJS64)

$(BINDIR)/arch/x86/loader.o: arch/x86/loader.asm
	$(NASM) -f elf32 arch/x86/loader.asm -o $(BINDIR)/arch/x86/loader.o

$(BINDIR)/arch/x64/kernel_entry.o: arch/x64/kernel_entry.asm
	$(NASM) -f elf64 arch/x64/kernel_entry.asm -o $(BINDIR)/arch/x64/kernel_entry.o

$(SUBDIRS):
	$(MAKE) -C $@

clean:
	rm -f $(BINDIR)/kernel.bin $(OBJS32) $(OBJS64)
	$(MAKE) -C arch/x86 clean
	$(MAKE) -C arch/x64 clean
	$(MAKE) -C drivers/fs/vfs clean
	$(MAKE) -C kernel clean
	$(MAKE) -C kernel/mm clean
	$(MAKE) -C libc/crt/src clean
	$(MAKE) -C libc/posix/src clean
	$(MAKE) -C osutils clean
