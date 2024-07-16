GCC = gcc

CFLAGS = -ffreestanding -nostdlib -I../../include
OBJDIR = ../../../bin/libc/crt

SRCS = errno.c locale.c math.c setjmp.c signal.c stdio.c stdlib.c string.c time.c wchar.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean

all: $(OBJS)

%.o: %.c
	$(GCC) $(CFLAGS) -c $< -o $(OBJDIR)/$@

clean:
	rm -f $(OBJDIR)/*.o
