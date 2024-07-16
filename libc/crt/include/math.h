#ifndef LCNC_LC_CRT_MATH_H
#define LCNC_LC_CRT_MATH_H

// Constants
#define M_E         2.7182818284590452354   // e
#define M_LOG2E     1.4426950408889634074   // log2(e)
#define M_LOG10E    0.43429448190325182765  // log10(e)
#define M_LN2       0.69314718055994530942  // ln(2)
#define M_LN10      2.30258509299404568402  // ln(10)
#define M_PI        3.14159265358979323846  // pi
#define M_PI_2      1.57079632679489661923  // pi/2
#define M_PI_4      0.78539816339744830962  // pi/4
#define M_1_PI      0.31830988618379067154  // 1/pi
#define M_2_PI      0.63661977236758134308  // 2/pi
#define M_2_SQRTPI  1.12837916709551257390  // 2/sqrt(pi)
#define M_SQRT2     1.41421356237309504880  // sqrt(2)
#define M_SQRT1_2   0.70710678118654752440  // 1/sqrt(2)

// Function prototypes
//TODO IMPLEMENT THESE:
double acos(double x);
double asin(double x);
double atan(double x);
double atan2(double y, double x);
double cos(double x);
double sin(double x);
double tan(double x);
double cosh(double x);
double sinh(double x);
double tanh(double x);
double exp(double x);
double frexp(double value, int *exp);
double ldexp(double x, int exp);
double log(double x);
double log10(double x);
double modf(double value, double *iptr);
double pow(double x, double y);
double sqrt(double x);
double ceil(double x);
double floor(double x);
double fabs(double x);

#endif // MATH_H
