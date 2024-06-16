#ifndef LCNC_LC_CRT_STDARG_H
#define LCNC_LC_CRT_STDARG_H


//define the va_list type.
#ifndef HAS_VARG
typedef char * va_list;
#define HAS_VARG 1
#endif

#define va_start(marker, last)  { marker = (va_list)&last + sizeof(last); }
#define va_arg(marker, type)    (*((type *)((marker += sizeof(type)) - sizeof(type))))

#define va_copy(dest, src)      ((dest) = (src))
#define va_end(marker)          ((marker) = (va_list) 0)

#endif /* _STDARG_H */
