#include "../include/tty.h"
#include "../include/inlineAssembly.h"
#include "../libc/crt/include/string.h"
#include "../libc/crt/include/stdarg.h"
#include "../libc/crt/include/stdio.h"
#include "../libc/crt/include/stdbool.h"
#include "../libc/crt/include/limits.h"

/* The I/O ports */
#define TTY_COMMAND_PORT         0x3D4
#define TTY_DATA_PORT            0x3D5

/* The I/O port commands */
#define TTY_HIGH_BYTE_COMMAND    14
#define TTY_LOW_BYTE_COMMAND     15

terminalInfo_t terminalInfo;

terminalInfo_t* getTerminalInfo() {
    return &terminalInfo;
}

static uint16_t s_buffer[80 * 1024];

terminalColor_t getColor(uint8_t color) {
    _terminalColor out;
    out.foreground = color & 0xF;
    out.background = (color >> 4) & 0xF;
    return out;
}

void reverse(char s[]) {
    int i, j;
    char c;

    for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

char* kitoa(int n, char s[]) {
    int i, sign;

    if ((sign = n) < 0)  /* record sign */
        n = -n;          /* make n positive */
    i = 0;
    do {       /* generate digits in reverse order */
        s[i++] = n % 10 + '0';   /* get next digit */
    } while ((n /= 10) > 0);     /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
    return s;
}

char* klltoa(long long n, char s[]) {
    long long i, sign;

    if ((sign = n) < 0)  /* record sign */
        n = -n;          /* make n positive */
    i = 0;
    do {       /* generate digits in reverse order */
        s[i++] = n % 10 + '0';   /* get next digit */
    } while ((n /= 10) > 0);     /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
    return s;
}

char* kulltoa(unsigned long long n, char s[]) {
    long long i = 0;
    do {       /* generate digits in reverse order */
        s[i++] = n % 10 + '0';   /* get next digit */
    } while ((n /= 10) > 0);     /* delete it */
    s[i] = '\0';
    reverse(s);
    return s;
}

char* kulltoab(unsigned long long n, char s[], unsigned int base) {
    long long i = 0;
    do {       /* generate digits in reverse order */
        s[i++] = "0123456789ABCDEF"[n % base];   /* get next digit */
    } while ((n /= base) > 0);     /* delete it */
    s[i] = '\0';
    reverse(s);
    return s;
}

char* kitoab(int n, char s[], unsigned int base) {
    int i, sign;

    if ((sign = n) < 0)  /* record sign */
        n = -n;          /* make n positive */
    i = 0;
    do {       /* generate digits in reverse order */
        s[i++] = "0123456789ABCDEF"[n % base];   /* get next digit */
    } while ((n /= base) > 0);     /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
    return s;
}

char* kuitoa(unsigned int n, char s[]) {
    int i = 0;
    do {       /* generate digits in reverse order */
        s[i++] = n % 10 + '0';   /* get next digit */
    } while ((n /= 10) > 0);     /* delete it */
    s[i] = '\0';
    reverse(s);
    return s;
}

char* kuitoab(unsigned int n, char s[], unsigned int base) {
    int i = 0;
    do {       /* generate digits in reverse order */
        s[i++] = "0123456789ABCDEF"[n % base];   /* get next digit */
    } while ((n /= base) > 0);     /* delete it */
    s[i] = '\0';
    reverse(s);
    return s;
}

uint8_t colorTouint8(_terminalColor color) {
    return vga_entry_color(color.foreground, color.background);
}

void initializeTerminal() {
    initialize_vga_default();

    terminalInfo.x = 0;
    terminalInfo.y = 0;
    terminalInfo.row = 0;
    terminalInfo.position = 0;
    terminalInfo.color = getColor(vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
    terminalInfo.buffer = vga_getVGAMem();
    terminalClear();
    terminalUpdateCursor();
}

void terminalClear() {
    for (size_t y = 0; y < vga_getVGAHeight(); y++) {
        for (size_t x = 0; x < vga_getVGAWidth(); x++) {
            const size_t index = y * vga_getVGAWidth() + x;
            terminalInfo.buffer[index] = vga_entry(' ', colorTouint8(terminalInfo.color));
        }
    }
}

void terminalUpdateCursor() {
    terminalInfo.position = terminalInfo.y * vga_getVGAWidth() + terminalInfo.x;
    outb(TTY_COMMAND_PORT, TTY_HIGH_BYTE_COMMAND);
    outb(TTY_DATA_PORT, ((terminalInfo.position >> 8) & 0x00FF));
    outb(TTY_COMMAND_PORT, TTY_LOW_BYTE_COMMAND);
    outb(TTY_DATA_PORT, terminalInfo.position & 0x00FF);
}

void terminalPutEntryAt(unsigned char c, uint8_t color, size_t x, size_t y) {
    const size_t index = y * vga_getVGAWidth() + x;
    terminalInfo.buffer[index] = vga_entry(c, color);
    s_buffer[index] = vga_entry(c, color);
}

void terminalPutChar(char c) {
    unsigned char uc = c;

    if (c == '\n') {
        terminalNewLine();
        return;
    }

    terminalPutEntryAt(uc, colorTouint8(terminalInfo.color), terminalInfo.x, terminalInfo.y);

    if (++terminalInfo.x == vga_getVGAWidth()) {
        terminalInfo.x = 0;
        if (++terminalInfo.y == vga_getVGAHeight()) {
            terminalScroll();
        }
    }

    terminalUpdateCursor();
}

void terminalWrite(const char* data, size_t size) {
    for (size_t i = 0; i < size; i++)
        terminalPutChar(data[i]);
}

void terminalWriteString(const char* data) {
    terminalWrite(data, strlen(data));
}

void terminalWriteLine(const char* data) {
    terminalWriteString(data);
    terminalNewLine();
}

void terminalChangeColor(_terminalColor color) {
    terminalInfo.color = color;
}

void terminalChangeColorUint8(uint8_t color) {
    terminalInfo.color = getColor(color);
}

void terminalNewLine() {
    terminalInfo.x = 0;
    if (++terminalInfo.y == vga_getVGAHeight()) {
        terminalScroll();
    }
    terminalUpdateCursor();
}

void terminalScroll() {
    for (unsigned int i = 0; i < vga_getVGAHeight() - 1; i++) {
        for (unsigned int j = 0; j < vga_getVGAWidth(); j++) {
            terminalInfo.buffer[i * vga_getVGAWidth() + j] =
                terminalInfo.buffer[(i + 1) * vga_getVGAWidth() + j];
        }
    }
    // Clear the last row
    for (unsigned int j = 0; j < vga_getVGAWidth(); j++) {
        terminalInfo.buffer[(vga_getVGAHeight() - 1) * vga_getVGAWidth() + j] =
            vga_entry(' ', colorTouint8(terminalInfo.color));
    }
}

static bool print(const char* data, size_t length) {
    const unsigned char* bytes = (const unsigned char*) data;
    for (size_t i = 0; i < length; i++)
        if (putchar(bytes[i]) == EOF)
            return false;
    return true;
}

int printk(const char* fmt, ...) {
    va_list parameters;
    va_start(parameters, fmt);

    int written = 0;
    while (*fmt != '\0') {
        size_t maxrem = INT_MAX - written;

        if (fmt[0] != '%' || fmt[1] == '%') {
            if (fmt[0] == '%')
                fmt++;
            size_t amount = 1;
            while (fmt[amount] && fmt[amount] != '%')
                amount++;
            if (maxrem < amount) {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print(fmt, amount))
                return -1;
            fmt += amount;
            written += amount;
            continue;
        }

        const char* format_begun_at = fmt++;

        static char buffer[64];
        memset(&buffer, 0, sizeof(buffer));

        switch (*fmt) {
        case 'c':
            fmt++;
            {
                char c = (char) va_arg(parameters, int /* char promotes to int */);
                if (!maxrem) {
                    // TODO: Set errno to EOVERFLOW.
                    return -1;
                }
                if (!print(&c, sizeof(c)))
                    return -1;
                written++;
            }
            break;
        case 's':
            fmt++;
            {
                const char* str = va_arg(parameters, const char*);
                size_t len = strlen(str);
                if (maxrem < len) {
                    // TODO: Set errno to EOVERFLOW.
                    return -1;
                }
                if (!print(str, len))
                    return -1;
                written += len;
            }
            break;
        case 'd':
            fmt++;
            {
                int i = (int) va_arg(parameters, int);
                char* c = kitoa(i, buffer);
                size_t len = strlen(c);
                if (!maxrem) {
                    // TODO: Set errno to EOVERFLOW.
                    return -1;
                }
                if (!print(c, len))
                    return -1;
                written += len;
            }
            break;
        case 'u':
            fmt++;
            {
                unsigned int i = (unsigned int) va_arg(parameters, unsigned int);
                char* c = kuitoa(i, buffer);
                size_t len = strlen(c);
                if (!maxrem) {
                    // TODO: Set errno to EOVERFLOW.
                    return -1;
                }
                if (!print(c, len))
                    return -1;
                written += len;
            }
            break;
        case 'U':
            fmt++;
            {
                unsigned long long i = (unsigned long long) va_arg(parameters, unsigned long long);
                char* c = kulltoa(i, buffer);
                size_t len = strlen(c);
                if (!maxrem) {
                    // TODO: Set errno to EOVERFLOW.
                    return -1;
                }
                if (!print(c, len))
                    return -1;
                written += len;
            }
            break;
        case 'l':
            fmt++;
            {
                long long i = (long long) va_arg(parameters, long long);
                char* c = klltoa(i, buffer);
                size_t len = strlen(c);
                if (!maxrem) {
                    // TODO: Set errno to EOVERFLOW.
                    return -1;
                }
                if (!print(c, len))
                    return -1;
                written += len;
            }
            break;
        case 'x':
            fmt++;
            {
                unsigned int i = (unsigned int) va_arg(parameters, unsigned int);
                char* c = kuitoab(i, buffer, 16);
                size_t len = strlen(c);
                if (!maxrem) {
                    // TODO: Set errno to EOVERFLOW.
                    return -1;
                }
                if (!print(c, len))
                    return -1;
                written += len;
            }
            break;
        case 'X':
            fmt++;
            {
                unsigned long long i = (unsigned long long) va_arg(parameters, unsigned long long);
                char* c = kulltoab(i, buffer, 16);
                size_t len = strlen(c);
                if (!maxrem) {
                    // TODO: Set errno to EOVERFLOW.
                    return -1;
                }
                if (!print(c, len))
                    return -1;
                written += len;
            }
            break;
        default:
            fmt = format_begun_at;
            size_t len = strlen(fmt);
            if (maxrem < len) {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print(fmt, len))
                return -1;
            written += len;
            fmt += len;
            break;
        }
    }

    va_end(parameters);
    return written;
}

void sprintk(char* buffer, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vsprintf(buffer, fmt, args);
    va_end(args);
}
