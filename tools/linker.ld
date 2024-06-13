ENTRY(_start)
SECTIONS
{
  . = 0x00100000; /* Start at 1MB */

  .text :
  {
    *(.text)
  }

  .rodata :
  {
    *(.rodata)
  }

  .data :
  {
    *(.data)
  }

  .bss :
  {
    *(.bss)
    *(COMMON)
  }
}
