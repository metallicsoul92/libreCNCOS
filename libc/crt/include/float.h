#ifndef LCNC_LC_CRT_FLOAT_H
#define LCNC_LC_CRT_FLOAT_H

// Characteristics of floating-point types
#define FLT_RADIX       2           // Radix of exponent representation
#define FLT_ROUNDS      1           // Rounding mode for floating-point addition
#define FLT_DIG         6           // Decimal digits of precision for float
#define FLT_EPSILON     1.1920929e-07F // Smallest number x where 1.0 + x != 1.0 for float
#define FLT_MANT_DIG    24          // Number of base-FLT_RADIX digits in mantissa for float
#define FLT_MAX         3.402823466e+38F // Maximum finite float value
#define FLT_MAX_10_EXP  38          // Maximum int x such that FLT_RADIX^(x-1) <= FLT_MAX for float
#define FLT_MAX_EXP     128         // Maximum int x such that 10^x is representable for float
#define FLT_MIN         1.175494351e-38F // Minimum positive float value
#define FLT_MIN_10_EXP  (-37)       // Minimum int x such that FLT_RADIX^(x-1) >= FLT_MIN for float
#define FLT_MIN_EXP     (-125)      // Minimum int x such that 10^x is representable for float

#define DBL_DIG         15          // Decimal digits of precision for double
#define DBL_EPSILON     2.2204460492503131e-16 // Smallest number x where 1.0 + x != 1.0 for double
#define DBL_MANT_DIG    53          // Number of base-FLT_RADIX digits in mantissa for double
#define DBL_MAX         1.7976931348623157e+308 // Maximum finite double value
#define DBL_MAX_10_EXP  308         // Maximum int x such that FLT_RADIX^(x-1) <= DBL_MAX for double
#define DBL_MAX_EXP     1024        // Maximum int x such that 10^x is representable for double
#define DBL_MIN         2.2250738585072014e-308 // Minimum positive double value
#define DBL_MIN_10_EXP  (-307)      // Minimum int x such that FLT_RADIX^(x-1) >= DBL_MIN for double
#define DBL_MIN_EXP     (-1021)     // Minimum int x such that 10^x is representable for double

#define LDBL_DIG        DBL_DIG     // Decimal digits of precision for long double
#define LDBL_EPSILON    DBL_EPSILON // Smallest number x where 1.0 + x != 1.0 for long double
#define LDBL_MANT_DIG   DBL_MANT_DIG // Number of base-FLT_RADIX digits in mantissa for long double
#define LDBL_MAX        DBL_MAX     // Maximum finite long double value
#define LDBL_MAX_10_EXP DBL_MAX_10_EXP // Maximum int x such that FLT_RADIX^(x-1) <= LDBL_MAX for long double
#define LDBL_MAX_EXP    DBL_MAX_EXP // Maximum int x such that 10^x is representable for long double
#define LDBL_MIN        DBL_MIN     // Minimum positive long double value
#define LDBL_MIN_10_EXP DBL_MIN_10_EXP // Minimum int x such that FLT_RADIX^(x-1) >= LDBL_MIN for long double
#define LDBL_MIN_EXP    DBL_MIN_EXP // Minimum int x such that 10^x is representable for long double

#endif // FLOAT_H
