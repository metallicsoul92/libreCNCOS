ENTRY(_start)

SECTIONS
{
  . = 0x100000; /* Start at 1MB */

  .text :
  {
    *(.multiboot)
    *(.text)
    *(.rodata)
  }

  .data :
  {
    *(.data)
  }

  .bss :
  {
    _bss_end = .;
    *(.bss)
    *(COMMON)
  }

  . = ALIGN(4096);  /* Align to page boundary */

  /* Define the start of the heap */
  HEAP_START = .;    /* Start of the heap */
  . = . + 0x10000;   /* Allocate 64KB for the heap, adjust size as needed */

  end = .;          /* Define end symbol */
}
