#include "../include/loader/pmodestructs.h"
#include "../include/multiboot.h"
#include "../include/kernel/pml4.h"
#include "../include/kernel/pml5.h"

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

// Function to initialize paging structures
void init_paging() {
    if (is_pml5_supported()) {
        setup_pml5();
    } else {
        setup_pml4();
    }
}

// Function to enable long mode and setup paging
void enable_long_mode() {
    // Enable PAE
    __asm__ __volatile__ (
        "mov %%cr4, %%eax\n\t"
        "or $0x20, %%eax\n\t"
        "mov %%eax, %%cr4"
        : : : "eax"
    );
    // Enable long mode by setting the EFER.LME bit
    __asm__ __volatile__ (
        "mov $0xC0000080, %%ecx\n\t"
        "rdmsr\n\t"
        "or $0x100, %%eax\n\t"
        "wrmsr"
        : : : "eax", "ecx", "edx"
    );
    // Load PML4 or PML5 table address into CR3
    uint64_t cr3_addr = get_paging_table();
    __asm__ __volatile__ (
        "mov %0, %%cr3" : : "r" (cr3_addr)
    );
    // Enable paging
    __asm__ __volatile__ (
        "mov %%cr0, %%eax\n\t"
        "or $0x80000000, %%eax\n\t"
        "mov %%eax, %%cr0"
        : : : "eax"
    );
}

/* This function gets called by the bootloader */
void lmain(const void* multiboot_struct) {
    // Set up GDT
    init_gdt_32();

    const multiboot_info_t* mb_info = multiboot_struct; // Make pointer to multiboot_info_t struct
    multiboot_uint32_t mb_flags = mb_info->flags;      // Get flags from mb_info

    void* kernel_entry = NULL;  // Pointer to the kernel entry point

    if (mb_flags & MULTIBOOT_INFO_MODS) { // Check if modules are available
        multiboot_uint32_t mods_count = mb_info->mods_count; // Get the amount of modules available
        multiboot_uint32_t mods_addr = mb_info->mods_addr;   // And the starting address of the modules

        if (mods_count > 0) {
            // Load the first module as the 64-bit kernel
            multiboot_module_t* module = (multiboot_module_t*)mods_addr;
            kernel_entry = (void*)module->mod_start;
        }
    }

    if (kernel_entry) {
      // Initialize paging structures
            init_paging();
            // Enable long mode and set up paging
            enable_long_mode();

        // Jump to the 64-bit kernel entry point
        __asm__ __volatile__ (
            "cli\n\t"                   // Clear interrupts
            "mov %0, %%eax\n\t"         // Load kernel entry address into eax
            "jmp *%%eax\n\t"            // Jump to the kernel entry point
            : : "r" (kernel_entry) : "eax"
        );
    } else {
        // Handle error: no kernel module found
        while (1) {
            __asm__ __volatile__ ("hlt");
        }
    }
}
