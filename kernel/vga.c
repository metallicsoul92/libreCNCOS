#include "../include/kernel/vga.h"


#define VMEM 0xB8000


const size_t DEFAULT_VIDEO_WIDTH = 80;
const size_t DEFAULT_VIDEO_HEIGHT = 25;

uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
	return fg | bg << 4;
}
uint16_t vga_entry(unsigned char uc, uint8_t color) {
	return (uint16_t) uc | (uint16_t) color << 8;
}

struct __videoInfo{
	uint16_t* videoMemory; //(uint16_t*) 0xB8000;
	 size_t videoWidth;  //80
   size_t videoHeight; //25
};




////////////
//Private API
videoInfo_t _intVGA;  //internal VGA
////

void initialize_vga_default(){
  _intVGA.videoMemory = (uint16_t*) VMEM;
  _intVGA.videoWidth = DEFAULT_VIDEO_WIDTH;
  _intVGA.videoHeight = DEFAULT_VIDEO_HEIGHT;
}
void initialize_vga(size_t _width, size_t _height){
  _intVGA.videoMemory = (uint16_t*) VMEM;
  _intVGA.videoWidth = _width;
  _intVGA.videoHeight = _height;
}


size_t vga_getVGAWidth(){
  return _intVGA.videoWidth;
}
size_t vga_getVGAHeight(){
  return _intVGA.videoHeight;
}
uint16_t * vga_getVGAMem(){
  return _intVGA.videoMemory;
}
