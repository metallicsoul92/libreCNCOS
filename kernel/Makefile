GCC = gcc

CFLAGS = -ffreestanding -nostdlib -Iinclude
OBJDIR = ../bin/kernel

SRCS =  gdt.c kernel.c idt.c isr.c task.c tty.c vga.c paging.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean

all: $(OBJS)

%.o: %.c
	$(GCC) $(CFLAGS) -c $< -o $(OBJDIR)/$@

clean:
	rm -f $(OBJDIR)/*.o
