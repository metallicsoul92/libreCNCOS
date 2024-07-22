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
TOOLSDIR = ../../tools
# Flags
CFLAGS = -m64 -ffreestanding -nostdlib -nostdinc -fno-builtin -fno-stack-protector -Wall -Wextra
LDFLAGS = -m elf_x86_64 -T $(TOOLSDIR)/kernellinker.ld
ASFLAGS = -f elf64

# Sources
ASMSRCS = $(wildcard *.asm)

# Objects
OBJS = $(ASMSRCS:%.asm=$(OBJDIR)/%.o)

# Targets
all: $(KERNELDIR)/kernel

# Build kernel
$(KERNELDIR)/kernel: $(OBJS)
	mkdir -p $(KERNELDIR)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

# Compile assembly files
$(OBJDIR)/%.o: $(SRCDIR)/%.asm
	mkdir -p $(OBJDIR)
	$(AS) $(ASFLAGS) -o $@ $<

# Clean
clean:
	rm -f $(OBJDIR)/*.o $(KERNELDIR)/kernel
