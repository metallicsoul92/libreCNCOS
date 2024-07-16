GCC = gcc

CFLAGS = -ffreestanding -nostdlib -I../../../include
OBJDIR = ../../../bin/drivers/fs/vfs

SRCS = vfs.c
OBJS = $(addprefix $(OBJDIR)/,$(SRCS:.c=.o))

.PHONY: all clean

all: $(OBJS)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	$(GCC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJDIR)/*.o
