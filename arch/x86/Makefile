# Makefile for 32-bit loader

# Toolchain
CC = gcc
AS = nasm
LD = ld

# Directories
SRCDIR = .
CSRCDIR = ../../loader
TOOLSDIR = ../../tools
BUILDDIR = ../../bin
OBJDIR = $(BUILDDIR)/obj/arch/x86
LOADERDIR = $(BUILDDIR)/loader

# Flags
CFLAGS = -m32 -ffreestanding -nostdlib -nostdinc -fno-builtin -fno-stack-protector -Wall -Wextra
LDFLAGS = -m elf_i386 -T $(TOOLSDIR)/loaderlinker.ld
ASFLAGS = -f elf32

# Sources
ASMSRCS = bootloader.asm
CSRCS = $(wildcard $(CSRCDIR)/*.c)

# Objects
ASMOBJS = $(ASMSRCS:%.asm=$(OBJDIR)/%.o)
COBJS = $(CSRCS:$(CSRCDIR)/%.c=$(OBJDIR)/%.o)

# Targets
all: $(LOADERDIR)/loader

# Build loader
$(LOADERDIR)/loader: $(ASMOBJS) $(COBJS)
	mkdir -p $(LOADERDIR)
	$(LD) $(LDFLAGS) -o $@ $(ASMOBJS) $(COBJS)

# Compile assembly files
$(OBJDIR)/%.o: $(SRCDIR)/%.asm
	mkdir -p $(OBJDIR)
	$(AS) $(ASFLAGS) -o $@ $<

# Compile C files from loader
$(OBJDIR)/%.o: $(CSRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean
clean:
	rm -f $(OBJDIR)/*.o $(LOADERDIR)/loader
