# Makefile for libc posix

# Toolchain
CC = gcc

# Directories
SRCDIR = .
BUILDDIR = ../../../bin
OBJDIR = $(BUILDDIR)/obj/libc/posix
LIBCDIR = $(BUILDDIR)/libc

# Flags
CFLAGS = -ffreestanding -nostdlib -nostdinc -fno-builtin -fno-stack-protector -Wall -Wextra

# Sources
CSRCS = $(wildcard *.c)

# Objects
OBJS = $(CSRCS:%.c=$(OBJDIR)/%.o)

# Targets
all: $(LIBCDIR)/libc_posix.a

# Create static library
$(LIBCDIR)/libc_posix.a: $(OBJS)
	mkdir -p $(LIBCDIR)
	ar rcs $@ $(OBJS)

# Compile C files
$(OBJDIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean
clean:
	rm -f $(OBJDIR)/*.o $(LIBCDIR)/libc_posix.a
