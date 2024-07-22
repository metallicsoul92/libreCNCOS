# Makefile for osutils

# Toolchain
CC = gcc

# Directories
SRCDIR = .
BUILDDIR = ../bin
OBJDIR = $(BUILDDIR)/obj/osutils
LIBDIR = $(BUILDDIR)/osutils

# Flags
CFLAGS = -ffreestanding -nostdlib -nostdinc -fno-builtin -fno-stack-protector -Wall -Wextra

# Sources
CSRCS = $(wildcard *.c)

# Objects
OBJS = $(CSRCS:%.c=$(OBJDIR)/%.o)

# Targets
all: $(LIBDIR)/osutils.a

# Create static library
$(LIBDIR)/osutils.a: $(OBJS)
	mkdir -p $(LIBDIR)
	ar rcs $@ $(OBJS)

# Compile C files
$(OBJDIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean
clean:
	rm -f $(OBJDIR)/*.o $(LIBDIR)/osutils.a
