#include "../include/string.h"

// String manipulation functions
char *strcpy(char *dest, const char *src) {
    char *d = dest;
    while ((*d++ = *src++));
    return dest;
}

char *strncpy(char *dest, const char *src, size_t n) {
    char *d = dest;
    while (n && (*d++ = *src++)) n--;
    if (n) while (--n) *d++ = '\0';
    return dest;
}

char *strcat(char *dest, const char *src) {
    char *d = dest;
    while (*d) d++;
    while ((*d++ = *src++));
    return dest;
}

char *strncat(char *dest, const char *src, size_t n) {
    char *d = dest;
    while (*d) d++;
    while (n-- && (*d++ = *src++));
    if (n) *d = '\0';
    return dest;
}

int strcmp(const char *str1, const char *str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

int strncmp(const char *str1, const char *str2, size_t n) {
    while (n && *str1 && (*str1 == *str2)) {
        str1++;
        str2++;
        n--;
    }
    if (!n) return 0;
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

size_t strlen(const char *str) {
    const char *s = str;
    while (*s) s++;
    return s - str;
}

char *strchr(const char *str, int c) {
    while (*str) {
        if (*str == (char)c) return (char *)str;
        str++;
    }
    return NULL;
}

char *strrchr(const char *str, int c) {
    const char *last = NULL;
    while (*str) {
        if (*str == (char)c) last = str;
        str++;
    }
    return (char *)last;
}

char *strstr(const char *haystack, const char *needle) {
    if (!*needle) return (char *)haystack;
    for (; *haystack; haystack++) {
        if ((*haystack == *needle) && !strncmp(haystack, needle, strlen(needle)))
            return (char *)haystack;
    }
    return NULL;
}

char *strtok(char *str, const char *delimiters) {
    static char *last;
    if (!str) str = last;
    if (!str) return NULL;

    str += strspn(str, delimiters);
    if (!*str) return NULL;

    char *token = str;
    str = strpbrk(token, delimiters);
    if (str) *str++ = '\0';
    last = str;
    return token;
}

size_t strspn(const char *str, const char *accept) {
    const char *s = str;
    const char *a;
    while (*s) {
        for (a = accept; *a; a++) {
            if (*s == *a) break;
        }
        if (!*a) break;
        s++;
    }
    return s - str;
}

size_t strcspn(const char *str, const char *reject) {
    const char *s = str;
    const char *r;
    while (*s) {
        for (r = reject; *r; r++) {
            if (*s == *r) return s - str;
        }
        s++;
    }
    return s - str;
}

char *strpbrk(const char *str, const char *accept) {
    const char *s;
    const char *a;
    for (s = str; *s; s++) {
        for (a = accept; *a; a++) {
            if (*s == *a) return (char *)s;
        }
    }
    return NULL;
}

void *memcpy(void *dest, const void *src, size_t n) {
    char *d = dest;
    const char *s = src;
    while (n--) {
        *d++ = *s++;
    }
    return dest;
}

void *memmove(void *dest, const void *src, size_t n) {
    char *d = dest;
    const char *s = src;
    if (d < s) {
        while (n--) {
            *d++ = *s++;
        }
    } else {
        d += n;
        s += n;
        while (n--) {
            *--d = *--s;
        }
    }
    return dest;
}

int memcmp(const void *ptr1, const void *ptr2, size_t n) {
    const unsigned char *a = ptr1;
    const unsigned char *b = ptr2;
    while (n--) {
        if (*a != *b) return *a - *b;
        a++;
        b++;
    }
    return 0;
}

void *memchr(const void *ptr, int value, size_t n) {
    const unsigned char *p = ptr;
    while (n--) {
        if (*p == (unsigned char)value) return (void *)p;
        p++;
    }
    return NULL;
}

void *memset(void *ptr, int value, size_t n) {
    unsigned char *p = ptr;
    while (n--) {
        *p++ = (unsigned char)value;
    }
    return ptr;
}
