NASM = nasm
OBJDIR = ../../bin/arch/x86

SRCS = bootloader.asm
OBJS = $(addprefix $(OBJDIR)/,$(SRCS:.asm=.o))

.PHONY: all clean

all: $(OBJS)

$(OBJDIR)/%.o: %.asm
	@mkdir -p $(OBJDIR)
	$(NASM) -f elf64 $< -o $@

clean:
	rm -f $(OBJDIR)/*.o
