#ifndef LCNC_LC_CRT_STDLIB_H
#define LCNC_LC_CRT_STDLIB_H


#ifndef __HAS_STDDEF
#include "stddef.h"
#define __HAS_STDDEF
#endif

// Constants
#define NULL ((void *)0)
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define RAND_MAX 32767

// Numeric conversion functions
double atof(const char *str);
int atoi(const char *str);
long int atol(const char *str);
long long int atoll(const char *str);

// Pseudo-random sequence generation functions
int rand(void);
void srand(unsigned int seed);

// Memory management functions
void *malloc(size_t size);
void *calloc(size_t num, size_t size);
void *realloc(void *ptr, size_t size);
void free(void *ptr);

// Environment functions
int system(const char *command);
char *getenv(const char *name);

// Mathematical functions to compute the absolute value of integers
int abs(int n);
long labs(long n);
long long llabs(long long n);

// Sorting and searching functions
void qsort(void *base, size_t num, size_t size,
           int (*compar)(const void *, const void *));
void *bsearch(const void *key, const void *base, size_t num, size_t size,
              int (*compar)(const void *, const void *));

// Other functions
void exit(int status);
void abort(void);
int atexit(void (*func)(void));

#endif /* _STDLIB_H */
