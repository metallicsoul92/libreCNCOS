GCC = gcc

CFLAGS = -ffreestanding -nostdlib -Iinclude
OBJDIR = ../../bin/kernel/sc

SRCS = sbrk.c mmap.c
OBJS = $(addprefix $(OBJDIR)/,$(SRCS:.c=.o))

.PHONY: all clean

all: $(OBJS)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	$(GCC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJDIR)/*.o
