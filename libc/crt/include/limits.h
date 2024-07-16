#ifndef LCNC_LC_CRT_LIMITS_H
#define LCNC_LC_CRT_LIMITS_H 1

#define CHAR_BIT   8                // number of bits in a char
#define SCHAR_MIN  (-128)           // minimum value for a signed char
#define SCHAR_MAX  127              // maximum value for a signed char
#define UCHAR_MAX  255              // maximum value for an unsigned char
#define CHAR_MIN   SCHAR_MIN        // minimum value for a char
#define CHAR_MAX   SCHAR_MAX        // maximum value for a char
#define MB_LEN_MAX 1                // maximum number of bytes in a multibyte character

#define SHRT_MIN   (-32768)         // minimum value for a short
#define SHRT_MAX   32767            // maximum value for a short
#define USHRT_MAX  65535            // maximum value for an unsigned short

#define INT_MIN    (-2147483647 - 1) // minimum value for an int
#define INT_MAX    2147483647       // maximum value for an int
#define UINT_MAX   4294967295U      // maximum value for an unsigned int

#define LONG_MIN   (-9223372036854775807L - 1) // minimum value for a long
#define LONG_MAX   9223372036854775807L        // maximum value for a long
#define ULONG_MAX  18446744073709551615UL       // maximum value for an unsigned long

#define LLONG_MIN  (-9223372036854775807LL - 1) // minimum value for a long long
#define LLONG_MAX  9223372036854775807LL        // maximum value for a long long
#define ULLONG_MAX 18446744073709551615ULL       // maximum value for an unsigned long long

// Other constants may be defined based on the specific implementation and target environment

#endif // LCNC_LC_CRT_LIMITS_H
