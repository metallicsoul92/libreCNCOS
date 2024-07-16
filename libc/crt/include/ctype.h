#ifndef LCNC_LC_CRT_CTYPE_H
#define LCNC_LC_CRT_CTYPE_H

// Character classification macros
#define isdigit(c)    ((c >= '0' && c <= '9'))
#define isalpha(c)    ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
#define isalnum(c)    (isdigit(c) || isalpha(c))
#define isupper(c)    (c >= 'A' && c <= 'Z')
#define islower(c)    (c >= 'a' && c <= 'z')
#define isspace(c)    (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v')
#define isprint(c)    (c >= ' ' && c <= '~')

// Character conversion macros
#define toupper(c)    (islower(c) ? (c - 'a' + 'A') : (c))
#define tolower(c)    (isupper(c) ? (c - 'A' + 'a') : (c))

#endif // CTYPE_H
