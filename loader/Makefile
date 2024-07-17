# Makefile for 32-bit loader

# Toolchain
CC = gcc
AS = nasm
LD = ld

# Directories
SRCDIR = .
BUILDDIR = ../../bin
OBJDIR = $(BUILDDIR)/obj
LOADERDIR = $(BUILDDIR)/loader

# Flags
CFLAGS = -m32 -ffreestanding -nostdlib -nostdinc -fno-builtin -fno-stack-protector -Wall -Wextra
LDFLAGS = -m elf_i386 -T linker.ld
ASFLAGS = -f elf32

# Sources
ASMSRCS = bootloader.asm
CSRCS = lmain.c

# Objects
OBJS = $(ASMSRCS:.asm=.o) $(CSRCS:.c=.o)

# Targets
all: $(LOADERDIR)/loader

# Build loader
$(LOADERDIR)/loader: $(OBJS)
	mkdir -p $(LOADERDIR)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

# Compile assembly files
%.o: %.asm
	$(AS) $(ASFLAGS) -o $(OBJDIR)/$@ $<

# Compile C files
%.o: %.c
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$@ $<

# Clean
clean:
	rm -f $(OBJDIR)/*.o $(LOADERDIR)/loader
