# Makefile for 32-bit loader

# Toolchain
CC = gcc

# Directories
SRCDIR = .
BUILDDIR = ../bin
OBJDIR = $(BUILDDIR)/obj/loader
LOADERDIR = $(BUILDDIR)/loader
TOOLSDIR = ../tools
# Flags
CFLAGS = -m32 -ffreestanding -nostdlib -nostdinc -fno-builtin -fno-stack-protector -Wall -Wextra

# Sources
CSRCS = $(wildcard *.c)

# Objects
OBJS = $(CSRCS:%.c=$(OBJDIR)/%.o)

# Targets
all: $(LOADERDIR)/loader

# Create 32-bit loader
$(LOADERDIR)/loader: $(OBJS)
	mkdir -p $(LOADERDIR)
	ld -m elf_i386 -T $(TOOLSDIR)/loaderlinker.ld -o $@ $(OBJS)

# Compile C files
$(OBJDIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean
clean:
	rm -f $(OBJDIR)/*.o $(LOADERDIR)/loader
