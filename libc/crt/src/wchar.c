#include "../include/wchar.h"

// String Copy Functions
wchar_t *wcscpy(wchar_t *dest, const wchar_t *src) {
    wchar_t *ptr = dest;
    while ((*dest++ = *src++) != L'\0');
    return ptr;
}

wchar_t *wcsncpy(wchar_t *dest, const wchar_t *src, size_t n) {
    wchar_t *ptr = dest;
    while (n-- && (*dest++ = *src++) != L'\0');
    if (n >= 0)
        *dest = L'\0';
    return ptr;
}

// String Concatenation Functions
wchar_t *wcscat(wchar_t *dest, const wchar_t *src) {
    wcscpy(dest + wcslen(dest), src);
    return dest;
}

wchar_t *wcsncat(wchar_t *dest, const wchar_t *src, size_t n) {
    size_t dest_len = wcslen(dest);
    size_t i;
    for (i = 0; i < n && src[i] != L'\0'; ++i)
        dest[dest_len + i] = src[i];
    dest[dest_len + i] = L'\0';
    return dest;
}

// String Comparison Functions
int wcscmp(const wchar_t *str1, const wchar_t *str2) {
    while (*str1 && (*str1 == *str2)) {
        ++str1;
        ++str2;
    }
    return *(const unsigned int *)str1 - *(const unsigned int *)str2;
}

int wcsncmp(const wchar_t *str1, const wchar_t *str2, size_t n) {
    while (n-- && *str1 && (*str1 == *str2)) {
        ++str1;
        ++str2;
    }
    return n < 0 ? 0 : *(const unsigned int *)str1 - *(const unsigned int *)str2;
}

// String Length Function
size_t wcslen(const wchar_t *str) {
    const wchar_t *ptr = str;
    while (*ptr++)
        ;
    return ptr - str - 1;
}

// String Search Functions
wchar_t *wcschr(const wchar_t *str, wchar_t wc) {
    while (*str && *str != wc)
        ++str;
    return (*str == wc) ? (wchar_t *)str : NULL;
}

wchar_t *wcsrchr(const wchar_t *str, wchar_t wc) {
    const wchar_t *ptr = NULL;
    while (*str) {
        if (*str == wc)
            ptr = str;
        ++str;
    }
    return (wchar_t *)ptr;
}

wchar_t *wcsstr(const wchar_t *haystack, const wchar_t *needle) {
    size_t needle_len = wcslen(needle);
    while (*haystack) {
        if (!wcscmp(haystack, needle))
            return (wchar_t *)haystack;
        ++haystack;
    }
    return NULL;
}

// Tokenization Function
wchar_t *wcstok(wchar_t *str, const wchar_t *delimiters) {
    static wchar_t *last_token = NULL;
    if (str)
        last_token = str;
    else if (!last_token)
        return NULL;

    str = last_token + wcsspn(last_token, delimiters);
    last_token = str + wcscspn(str, delimiters);
    if (*last_token)
        *last_token++ = L'\0';
    else
        last_token = NULL;

    return str;
}

// String Spanning and Scanning Functions
size_t wcsspn(const wchar_t *str, const wchar_t *accept) {
    const wchar_t *ptr = str;
    while (*ptr && wcschr(accept, *ptr))
        ++ptr;
    return ptr - str;
}

size_t wcscspn(const wchar_t *str, const wchar_t *reject) {
    const wchar_t *ptr = str;
    while (*ptr && !wcschr(reject, *ptr))
        ++ptr;
    return ptr - str;
}

wchar_t *wcspbrk(const wchar_t *str, const wchar_t *accept) {
    while (*str) {
        if (wcschr(accept, *str))
            return (wchar_t *)str;
        ++str;
    }
    return NULL;
}

// Memory Copy Functions
wchar_t *wmemcpy(wchar_t *dest, const wchar_t *src, size_t n) {
    wchar_t *ptr = dest;
    while (n--)
        *dest++ = *src++;
    return ptr;
}

wchar_t *wmemmove(wchar_t *dest, const wchar_t *src, size_t n) {
    wchar_t *tmp = dest;
    if (src < dest) {
        src += n;
        dest += n;
        while (n--)
            *--dest = *--src;
    } else {
        while (n--)
            *dest++ = *src++;
    }
    return tmp;
}

// Memory Comparison Function
int wmemcmp(const wchar_t *ptr1, const wchar_t *ptr2, size_t n) {
    while (n-- && *ptr1 == *ptr2) {
        ++ptr1;
        ++ptr2;
    }
    return n < 0 ? 0 : *(const unsigned int *)ptr1 - *(const unsigned int *)ptr2;
}

// Memory Search Function
wchar_t *wmemchr(const wchar_t *ptr, wchar_t value, size_t n) {
    while (n-- && *ptr != value)
        ++ptr;
    return (*ptr == value) ? (wchar_t *)ptr : NULL;
}

// Memory Set Function
wchar_t *wmemset(wchar_t *ptr, wchar_t value, size_t n) {
    wchar_t *tmp = ptr;
    while (n--)
        *ptr++ = value;
    return tmp;
}
