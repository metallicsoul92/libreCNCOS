#ifndef LCNC_LC_CRT_STDIO_H
#define LCNC_LC_CRT_STDIO_H

// Include necessary headers
#include <stddef.h>   // For size_t, NULL
#include <stdarg.h>   // For va_list, va_start, va_arg, va_end

// File structure
typedef struct FILE {
    // Implementation-specific details
} FILE;

// Standard I/O streams
extern FILE *stdin;    // Standard input stream
extern FILE *stdout;   // Standard output stream
extern FILE *stderr;   // Standard error stream

// File operations
FILE *fopen(const char *filename, const char *mode);
int fclose(FILE *stream);
int fflush(FILE *stream);

// Formatted output functions
int printf(const char *format, ...);
int fprintf(FILE *stream, const char *format, ...);
int sprintf(char *str, const char *format, ...);
int snprintf(char *str, size_t size, const char *format, ...);

// Formatted input functions
int scanf(const char *format, ...);
int fscanf(FILE *stream, const char *format, ...);
int sscanf(const char *str, const char *format, ...);

// Character input/output functions
int putchar(int c);
int getchar(void);

// File input/output functions
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);

// File positioning functions
int fseek(FILE *stream, long offset, int whence);
long ftell(FILE *stream);
void rewind(FILE *stream);

// Error handling
void perror(const char *s);

// End-of-file and error indicators
int feof(FILE *stream);
int ferror(FILE *stream);
void clearerr(FILE *stream);

#endif /* _STDIO_H */
