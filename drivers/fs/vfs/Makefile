# Makefile for drivers/fs/vfs

# Toolchain
CC = gcc

# Directories
SRCDIR = .
BUILDDIR = ../../../bin
OBJDIR = $(BUILDDIR)/obj/drivers/fs/vfs
DRIVERDIR = $(BUILDDIR)/drivers

# Flags
CFLAGS = -ffreestanding -nostdlib -nostdinc -fno-builtin -fno-stack-protector -Wall -Wextra

# Sources
CSRCS = $(wildcard *.c)

# Objects
OBJS = $(CSRCS:%.c=$(OBJDIR)/%.o)

# Targets
all: $(DRIVERDIR)/drivers_fs_vfs.a

# Create static library
$(DRIVERDIR)/drivers_fs_vfs.a: $(OBJS)
	mkdir -p $(DRIVERDIR)
	ar rcs $@ $(OBJS)

# Compile C files
$(OBJDIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean
clean:
	rm -f $(OBJDIR)/*.o $(DRIVERDIR)/drivers_fs_vfs.a
