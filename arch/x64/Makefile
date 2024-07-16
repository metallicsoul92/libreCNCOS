NASM = nasm
OBJDIR = ../../bin/arch/x64

SRCS = kernel_entry.asm idt.asm io.asm modes.asm crti.asm crtn.asm gdt.asm isr_stub.asm paging.asm
OBJS = $(addprefix $(OBJDIR)/,$(SRCS:.asm=.o))

.PHONY: all clean

all: $(OBJS)

$(OBJDIR)/%.o: %.asm
	@mkdir -p $(OBJDIR)
	$(NASM) -f elf64 $< -o $@

clean:
	rm -f $(OBJDIR)/*.o
