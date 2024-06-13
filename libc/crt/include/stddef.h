#ifndef LCNC_LC_CRT_STDDEF_H
#define LCNC_LC_CRT_STDDEF_H

// Define NULL pointer
#define NULL ((void *)0)

// Define size_t
typedef unsigned long size_t;

// Define ptrdiff_t
typedef long ptrdiff_t;

// Define offsetof macro
#define offsetof(type, member) ((size_t)(&((type *)0)->member))

// Define wchar_t
typedef int wchar_t;

#endif /* _STDDEF_H */
