#ifndef LCNC_KERNEL_TTY_H_
#define LCNC_KERNEL_TTY_H_

//include for standard types
#include "../../libc/crt/include/stdint.h"

#include "vga.h"

// Define the structure for video information
extern videoInfo_t videoInfo;

// Define the structure for terminal color
struct __terminalColor {
    uint8_t foreground : 4; // Top 4 bits
    uint8_t background : 4; // Bottom 4 bits
};

typedef struct __terminalColor terminalColor_t;

// Function declarations for terminal color handling
terminalColor_t getColor(uint8_t color);
uint8_t colorTouint8(terminalColor_t color);

// Define the structure for terminal information
struct __terminalInfo {
    uint16_t x;
    uint16_t y;
    uint16_t row;
    terminalColor_t color;
    uint16_t position;
    uint16_t *buffer;
};

typedef struct __terminalInfo terminalInfo_t;

// Function declarations for accessing terminal and video information
terminalInfo_t *getTerminalInfo();
videoInfo_t *getVideoInfo();
extern terminalInfo_t terminalInfo;
extern videoInfo_t videoInfo;

// Function declarations for terminal operations
void initializeTerminal();
void terminalClear();
void terminalUpdateCursor();
void terminalPutEntryAt(unsigned char c, uint8_t color, size_t x, size_t y);
void terminalPutChar(char c);
void terminalWrite(const char* data, size_t size);
void terminalWriteString(const char* data);
void terminalWriteLine(const char* data);
void terminalChangeColor(terminalColor_t color);
void terminalChangeColorUint8(uint8_t color);
void terminalNewLine();
void terminalScroll();
int printk(const char *fmt, ...);

// Utility function for reversing a string
void reverse(char s[]);

// Function declarations for integer-to-string conversion
char *kitoa(int n, char s[]);
char *kitoab(int n, char s[], unsigned int base);
char *kuitoa(unsigned int n, char s[]);
char *kuitoab(unsigned int n, char s[], unsigned int base);

// Function declaration for formatted printing to a buffer
void sprintk(char *buffer, const char *fmt, ...);

#endif // TTY_H_
