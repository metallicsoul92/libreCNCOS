#ifndef LCNC_LC_CRT_STDARG_H
#define LCNC_LC_CRT_STDARG_H

// Define va_list type
typedef char * va_list;

// Macros for va_start, va_arg, va_end
#define va_start(ap, param)  (ap = (va_list)&param + sizeof(param))
#define va_arg(ap, type)     (*(type *)((ap += sizeof(type)) - sizeof(type)))
#define va_end(ap)           (ap = (va_list)0)
#define va_copy(dest, src)   (dest = src)

#endif /* _STDARG_H */
