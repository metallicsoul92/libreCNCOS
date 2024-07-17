# Makefile for 32-bit loader

# Toolchain
CC = gcc
AS = nasm
LD = ld

# Directories
SRCDIR = .
BUILDDIR = ../../bin
OBJDIR = $(BUILDDIR)/obj/arch/x86
LOADERDIR = $(BUILDDIR)/loader

# Flags
CFLAGS = -m32 -ffreestanding -nostdlib -nostdinc -fno-builtin -fno-stack-protector -Wall -Wextra
LDFLAGS = -m elf_i386 -T $(SRCDIR)/linker.ld
ASFLAGS = -f elf32

# Sources
ASMSRCS = bootloader.asm
CSRCS = ../../loader/lmain.c

# Objects
OBJS = $(ASMSRCS:%.asm=$(OBJDIR)/%.o) $(CSRCS:%.c=$(OBJDIR)/%.o)

# Targets
all: $(LOADERDIR)/loader

# Build loader
$(LOADERDIR)/loader: $(OBJS)
	mkdir -p $(LOADERDIR)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

# Compile assembly files
$(OBJDIR)/%.o: $(SRCDIR)/%.asm
	mkdir -p $(OBJDIR)
	$(AS) $(ASFLAGS) -o $@ $<

# Compile C files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean
clean:
	rm -f $(OBJDIR)/*.o $(LOADERDIR)/loader
