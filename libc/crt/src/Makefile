# Makefile for libc crt

# Toolchain
CC = gcc

# Directories
SRCDIR = .
BUILDDIR = ../../../bin
OBJDIR = $(BUILDDIR)/obj/libc/crt
LIBCDIR = $(BUILDDIR)/libc

# Flags
CFLAGS = -ffreestanding -nostdlib -nostdinc -fno-builtin -fno-stack-protector -Wall -Wextra

# Sources
CSRCS = $(wildcard *.c)

# Objects
OBJS = $(CSRCS:%.c=$(OBJDIR)/%.o)

# Targets
all: $(LIBCDIR)/libc_crt.a

# Create static library
$(LIBCDIR)/libc_crt.a: $(OBJS)
	mkdir -p $(LIBCDIR)
	ar rcs $@ $(OBJS)

# Compile C files
$(OBJDIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean
clean:
	rm -f $(OBJDIR)/*.o $(LIBCDIR)/libc_crt.a
