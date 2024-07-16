GCC = gcc

CFLAGS = -ffreestanding -nostdlib -Iinclude
OBJDIR = ../bin/osutils

SRCS = io_utils.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean

all: $(OBJS)

%.o: %.c
	$(GCC) $(CFLAGS) -c $< -o $(OBJDIR)/$@

clean:
	rm -f $(OBJDIR)/*.o
