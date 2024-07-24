# Makefile for 64-bit kernel

# Toolchain
CC = gcc
AS = nasm
LD = ld

# Directories
SRCDIR = .
BUILDDIR = ../../bin
OBJDIR = $(BUILDDIR)/obj/arch/x64
KERNELDIR = $(BUILDDIR)/kernel
KERNEL_OBJDIR = $(BUILDDIR)/obj/kernel
TOOLSDIR = ../../tools

# Flags
CFLAGS = -m64 -ffreestanding -nostdlib -nostdinc -fno-builtin -fno-stack-protector -Wall -Wextra
LDFLAGS = -m elf_x86_64 -T $(TOOLSDIR)/kernellinker.ld
ASFLAGS = -f elf64

# Sources
ASMSRCS = $(wildcard *.asm)
CSRCS = $(wildcard *.c) ../../kernel/isr.c

# Objects
ASMOBJS = $(ASMSRCS:%.asm=$(OBJDIR)/%.o)
COBJS = $(CSRCS:../../kernel/%.c=$(KERNEL_OBJDIR)/%.o) $(CSRCS:%.c=$(OBJDIR)/%.o)

# Targets
all: $(KERNELDIR)/kernel

# Build kernel
$(KERNELDIR)/kernel: $(ASMOBJS) $(COBJS)
	mkdir -p $(KERNELDIR)
	$(LD) $(LDFLAGS) -o $@ $(ASMOBJS) $(COBJS)

# Compile assembly files
$(OBJDIR)/%.o: $(SRCDIR)/%.asm
	mkdir -p $(OBJDIR)
	$(AS) $(ASFLAGS) -o $@ $<

# Compile C files from kernel
$(KERNEL_OBJDIR)/%.o: ../../kernel/%.c
	mkdir -p $(KERNEL_OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Compile C files from current directory
$(OBJDIR)/%.o: %.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean
clean:
	rm -f $(OBJDIR)/*.o $(KERNEL_OBJDIR)/*.o $(KERNELDIR)/kernel
