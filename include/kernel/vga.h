#ifndef LCNC_KERNEL_VGA_H
#define LCNC_KERNEL_VGA_H

#ifndef __HAS_STDDEF
#include "../../libc/crt/include/stddef.h"
#define __HAS_STDDEF
#endif


#ifndef __HAS_STDINT
#include "../../libc/crt/include/stdint.h"
#define __HAS_STDINT
#endif

typedef struct __videoInfo videoInfo_t;

enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};


uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg);
uint16_t vga_entry(unsigned char uc, uint8_t color);

size_t vga_getVGAWidth();
size_t vga_getVGAHeight();
uint16_t * vga_getVGAMem();

void initialize_vga_default();
void initialize_vga(size_t _width, size_t _height);

#endif
