GCC = gcc

CFLAGS = -ffreestanding -nostdlib -nostdinc -I../../include
OBJDIR = ../../../bin/libc/posix

SRCS = fcntl.c libgen.c sys/stat.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean

all: $(OBJS)

%.o: %.c
	$(GCC) $(CFLAGS) -c $< -o $(OBJDIR)/$@

clean:
	rm -f $(OBJDIR)/*.o
