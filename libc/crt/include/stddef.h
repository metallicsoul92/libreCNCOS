#ifndef LCNC_LC_CRT_STDDEF_H
#define LCNC_LC_CRT_STDDEF_H

// Define NULL pointer
#ifndef NULL
#define NULL ((void *)0)
#endif

// Define size_t
#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned long size_t;
#endif

// Define ptrdiff_t
#ifndef _PTRDIFF_T
#define _PTRDIFF_T
typedef long ptrdiff_t;
#endif

// Define offsetof macro
#ifndef offsetof
#define offsetof(type, member) ((size_t) &(((type *)0)->member))
#endif

// Define wchar_t
#ifndef _WCHAR_T
#define _WCHAR_T
typedef int wchar_t;
#endif

#endif /* LCNC_LC_CRT_STDDEF_H */
