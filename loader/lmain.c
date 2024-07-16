#include "../include/loader/pmodestructs.h"
#include "../include/multiboot.h"

/*GDT functions */
// Function to set up a GDT entry in 32-bit mode
void set_gdt_entry_32(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
    gdt_32[num].base_low = (base & 0xFFFF);
    gdt_32[num].base_middle = (base >> 16) & 0xFF;
    gdt_32[num].base_high = (base >> 24) & 0xFF;

    gdt_32[num].limit_low = (limit & 0xFFFF);
    gdt_32[num].granularity = (limit >> 16) & 0x0F;
    gdt_32[num].granularity |= (gran & 0xF0);
    gdt_32[num].access = access;
}

// Function to initialize and load the GDT in 32-bit mode
void init_gdt_32() {
    gdtp_32.limit = (sizeof(struct gdt_entry_32) * 3) - 1;
    gdtp_32.base = (uint32_t)&gdt_32;

    // Example entries: Null, Code, Data
    set_gdt_entry_32(0, 0, 0, 0, 0);                // Null segment
    set_gdt_entry_32(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
    set_gdt_entry_32(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment

    // Load the GDT with lgdt
    __asm__ __volatile__ ("lgdt (%0)" : : "r" (&gdtp_32));
}


/* This function gets called by the bootloader */
void lmain(const void* multiboot_struct) {
        // Set up GDT
        init_gdt_32();

        const multiboot_info_t* mb_info = multiboot_struct;            /* Make pointer to multiboot_info_t struct */
	multiboot_uint32_t mb_flags = mb_info->flags;                  /* Get flags from mb_info */

        void* kentry = NULL;                                           /* Pointer to the kernel entry point */

        if (mb_flags & MULTIBOOT_INFO_MODS) {                          /* Check if modules are available */
                multiboot_uint32_t mods_count = mb_info->mods_count;   /* Get the amount of modules available */
		multiboot_uint32_t mods_addr = mb_info->mods_addr;     /* And the starting address of the modules */

                for (uint32_t mod = 0; mod < mods_count; mod++) {
                        multiboot_module_t* module = (multiboot_module_t*)(mods_addr + (mod * sizeof(multiboot_module_t)));     /* Loop through all modules */
                }
        }
}
