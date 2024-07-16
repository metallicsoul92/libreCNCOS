#ifndef LCNC_LC_CRT_STRING_H
#define LCNC_LC_CRT_STRING_H

// Define NULL pointer
#ifndef NULL
#define NULL ((void *)0)
#endif

// Define size_t
#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned long size_t;
#endif


// String manipulation functions
char *strcpy(char *dest, const char *src);
char *strncpy(char *dest, const char *src, size_t n);
char *strcat(char *dest, const char *src);
char *strncat(char *dest, const char *src, size_t n);
int strcmp(const char *str1, const char *str2);
int strncmp(const char *str1, const char *str2, size_t n);
size_t strlen(const char *str);
char *strchr(const char *str, int c);
char *strrchr(const char *str, int c);
char *strstr(const char *haystack, const char *needle);
char *strtok(char *str, const char *delimiters);
size_t strspn(const char *str, const char *accept);
size_t strcspn(const char *str, const char *reject);
char *strpbrk(const char *str, const char *accept);
void *memcpy(void *dest, const void *src, size_t n);
void *memmove(void *dest, const void *src, size_t n);
int memcmp(const void *ptr1, const void *ptr2, size_t n);
void *memchr(const void *ptr, int value, size_t n);
void *memset(void *ptr, int value, size_t n);

#endif /* _STRING_H */
