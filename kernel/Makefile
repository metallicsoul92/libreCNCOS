# Makefile for 64-bit kernel

# Toolchain
CC = gcc

# Directories
SRCDIR = .
BUILDDIR = ../bin
OBJDIR = $(BUILDDIR)/obj/kernel
KERNELDIR = $(BUILDDIR)/kernel
TOOLSDIR = ../tools

# Flags
CFLAGS = -m64 -ffreestanding -nostdlib -nostdinc -fno-builtin -fno-stack-protector -Wall -Wextra

# Sources
CSRCS = $(wildcard *.c)

# Objects
OBJS = $(CSRCS:%.c=$(OBJDIR)/%.o)

# Targets
all: $(KERNELDIR)/kernel

# Create 64-bit kernel
$(KERNELDIR)/kernel: $(OBJS)
	mkdir -p $(KERNELDIR)
	ld -m elf_x86_64 -T $(TOOLSDIR)/kernellinker.ld -o $@ $(OBJS)

# Compile C files
$(OBJDIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean
clean:
	rm -f $(OBJDIR)/*.o $(KERNELDIR)/kernel
