# Makefile to assemble .asm files in the current directory and place the output in bin/arch/x64

# Directories
SRC_DIR := .
BIN_DIR := ../../bin/arch/x64

# Assembler and flags
ASM := nasm
ASM_FLAGS := -f elf64

# Get list of .asm files
ASM_FILES := $(wildcard $(SRC_DIR)/*.asm)

# Generate list of object files
OBJ_FILES := $(patsubst $(SRC_DIR)/%.asm,$(BIN_DIR)/%.o,$(ASM_FILES))

# Default target
all: $(OBJ_FILES)

# Rule to assemble .asm files
$(BIN_DIR)/%.o: $(SRC_DIR)/%.asm
	@mkdir -p $(BIN_DIR)
	$(ASM) $(ASM_FLAGS) -o $@ $<

# Clean up
clean:
	rm -rf $(BIN_DIR)/*.o

.PHONY: all clean
