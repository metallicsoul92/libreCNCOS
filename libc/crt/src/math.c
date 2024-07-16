#include "../include/math.h"

//private function
double fact(int n) {
    if (n == 0) return 1;
    double res = 1;
    for (int i = 1; i <= n; ++i) res *= i;
    return res;
}

//

// Arc cosine
double acos(double x) {
    if (x > 1.0 || x < -1.0) return 0.0 / 0.0; // NaN for invalid input

    double s = 0.0;
    double term = 1.0;
    double xsquared = x * x;
    int n = 0;

    while (fabs(term) > 1e-15) { // Accuracy threshold
        term = (fact(2 * n) / (pow(4, n) * pow(fact(n), 2) * (2 * n + 1))) * pow(x, 2 * n + 1);
        s += term;
        n++;
    }
    return M_PI_2 - s;
}

// Arc sine
double asin(double x) {
    if (x > 1.0 || x < -1.0) return 0.0 / 0.0; // NaN for invalid input

    double s = 0.0;
    double term = x;
    double xsquared = x * x;
    int n = 0;

    while (fabs(term) > 1e-15) { // Accuracy threshold
        term = (fact(2 * n) / (pow(4, n) * pow(fact(n), 2) * (2 * n + 1))) * pow(x, 2 * n + 1);
        s += term;
        n++;
    }
    return s;
}

// Arc tangent
double atan(double x) {
    if (x == 0.0) return 0.0;

    double s = 0.0;
    double term = x;
    int n = 0;
    double xsquared = x * x;

    while (fabs(term) > 1e-15) { // Accuracy threshold
        term = pow(-1, n) * pow(x, 2 * n + 1) / (2 * n + 1);
        s += term;
        n++;
    }
    return s;
}

// Arc tangent of y/x
double atan2(double y, double x) {
    if (x > 0) return atan(y / x);
    if (x < 0 && y >= 0) return atan(y / x) + M_PI;
    if (x < 0 && y < 0) return atan(y / x) - M_PI;
    if (x == 0 && y > 0) return M_PI / 2;
    if (x == 0 && y < 0) return -M_PI / 2;
    return 0; // Undefined
}

// Cosine
double cos(double x) {
    double s = 1.0;
    double term = 1.0;
    double xsquared = x * x;
    int n = 1;

    while (fabs(term) > 1e-15) { // Accuracy threshold
        term *= -xsquared / (2 * n * (2 * n - 1));
        s += term;
        n++;
    }
    return s;
}

// Sine
double sin(double x) {
    double s = x;
    double term = x;
    double xsquared = x * x;
    int n = 1;

    while (fabs(term) > 1e-15) { // Accuracy threshold
        term *= -xsquared / (2 * n * (2 * n + 1));
        s += term;
        n++;
    }
    return s;
}
// Tangent
double tan(double x) {
    return sin(x) / cos(x);
}

// Hyperbolic cosine
double cosh(double x) {
    double s = 1.0;
    double term = 1.0;
    double xsquared = x * x;
    int n = 1;

    while (fabs(term) > 1e-15) { // Accuracy threshold
        term *= xsquared / (2 * n * (2 * n - 1));
        s += term;
        n++;
    }
    return s;
}

// Hyperbolic sine
double sinh(double x) {
    double s = x;
    double term = x;
    double xsquared = x * x;
    int n = 1;

    while (fabs(term) > 1e-15) { // Accuracy threshold
        term *= xsquared / (2 * n * (2 * n + 1));
        s += term;
        n++;
    }
    return s;
}

// Hyperbolic tangent
double tanh(double x) {
    double ex = exp(x);
    double ex_inv = exp(-x);
    return (ex - ex_inv) / (ex + ex_inv);
}

// Exponential
double exp(double x) {
    double s = 1.0;
    double term = 1.0;
    int n = 1;

    while (fabs(term) > 1e-15) { // Accuracy threshold
        term *= x / n;
        s += term;
        n++;
    }
    return s;
}
// Frexp
double frexp(double value, int *exp) {
    *exp = 0;

    if (value == 0.0) return 0.0;

    while (fabs(value) >= 1.0) {
        value /= 2.0;
        (*exp)++;
    }

    while (fabs(value) < 0.5) {
        value *= 2.0;
        (*exp)--;
    }

    return value;
}

// Ldexp
double ldexp(double x, int exp) {
    return x * pow(2, exp);
}

// Logarithm (base e)
double log(double x) {
    if (x <= 0.0) return 0.0 / 0.0; // NaN for non-positive input

    double s = 0.0;
    double term = (x - 1) / (x + 1);
    double xsquared = term * term;
    int n = 1;

    while (fabs(term) > 1e-15) { // Accuracy threshold
        term = pow(xsquared, n) / (2 * n - 1);
        s += term;
        n++;
    }
    return 2 * s;
}


// Logarithm (base 10)
double log10(double x) {
    return log(x) / log(10);
}
// Modf
double modf(double value, double *iptr) {
    *iptr = (double)((long)value);
    return value - *iptr;
}
// Power
double pow(double x, double y) {
    return exp(y * log(x));
}
// Square root
double sqrt(double x) {
    if (x < 0.0) return 0.0 / 0.0; // NaN for negative input

    double guess = x / 2.0;
    double epsilon = 1e-15;

    while (fabs(guess * guess - x) > epsilon) {
        guess = (guess + x / guess) / 2.0;
    }
    return guess;
}

// Ceil
double ceil(double x) {
    if (x == (double)((long)x)) return x;
    return (x > 0) ? (double)((long)x + 1) : (double)((long)x);
}

// Floor
double floor(double x) {
    if (x == (double)((long)x)) return x;
    return (x > 0) ? (double)((long)x) : (double)((long)x - 1);
}

// Absolute value
double fabs(double x) {
    return (x < 0) ? -x : x;
}
