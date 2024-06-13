#include "stdlib.h"
#include "string.h" // For memcpy, memset
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Numeric conversion functions
double atof(const char *str) {
    return strtod(str, NULL);
}

int atoi(const char *str) {
    return (int)strtol(str, NULL, 10);
}

long int atol(const char *str) {
    return strtol(str, NULL, 10);
}

long long int atoll(const char *str) {
    return strtoll(str, NULL, 10);
}

// Pseudo-random sequence generation functions
static unsigned long int next = 1;

int rand(void) {
    next = next * 1103515245 + 12345;
    return (unsigned int)(next / 65536) % (RAND_MAX + 1);
}

void srand(unsigned int seed) {
    next = seed;
}

// Memory management functions
void *malloc(size_t size) {
    return sbrk(size);
}

void *calloc(size_t num, size_t size) {
    size_t total_size = num * size;
    void *ptr = malloc(total_size);
    if (ptr) {
        memset(ptr, 0, total_size);
    }
    return ptr;
}

void *realloc(void *ptr, size_t size) {
    if (!ptr) {
        return malloc(size);
    }

    void *new_ptr = malloc(size);
    if (new_ptr) {
        memcpy(new_ptr, ptr, size);
        free(ptr);
    }
    return new_ptr;
}

void free(void *ptr) {
    // No-op in this simple implementation
}

// Environment functions
int system(const char *command) {
    int status;
    pid_t pid = fork();
    if (pid == -1) {
        return -1;
    } else if (pid == 0) {
        execl("/bin/sh", "sh", "-c", command, (char *)NULL);
        _exit(127);
    } else {
        while (waitpid(pid, &status, 0) == -1) {
            if (errno != EINTR) {
                return -1;
            }
        }
        return status;
    }
}

char *getenv(const char *name) {
    extern char **environ;
    size_t len = strlen(name);
    for (char **env = environ; *env != NULL; env++) {
        if (strncmp(name, *env, len) == 0 && (*env)[len] == '=') {
            return &(*env)[len + 1];
        }
    }
    return NULL;
}

// Process control functions
int abs(int n) {
    return n < 0 ? -n : n;
}

long labs(long n) {
    return n < 0 ? -n : n;
}

long long llabs(long long n) {
    return n < 0 ? -n : n;
}

// Sorting and searching functions
void qsort(void *base, size_t num, size_t size, int (*compar)(const void *, const void *)) {
    if (num < 2) return;

    char *pivot = base + (num - 1) * size;
    size_t i = 0, j = 0;
    char *temp = malloc(size);

    for (; j < num - 1; j++) {
        char *current = base + j * size;
        if (compar(current, pivot) < 0) {
            memcpy(temp, current, size);
            memcpy(current, base + i * size, size);
            memcpy(base + i * size, temp, size);
            i++;
        }
    }

    memcpy(temp, base + i * size, size);
    memcpy(base + i * size, pivot, size);
    memcpy(pivot, temp, size);
    free(temp);

    qsort(base, i, size, compar);
    qsort(base + (i + 1) * size, num - i - 1, size, compar);
}

void *bsearch(const void *key, const void *base, size_t num, size_t size,
              int (*compar)(const void *, const void *)) {
    size_t low = 0;
    size_t high = num;

    while (low < high) {
        size_t mid = (low + high) / 2;
        char *p = (char *)base + mid * size;
        int cmp = compar(key, p);
        if (cmp < 0) {
            high = mid;
        } else if (cmp > 0) {
            low = mid + 1;
        } else {
            return p;
        }
    }
    return NULL;
}

// Other functions
void exit(int status) {
    _exit(status);
}

void abort(void) {
    raise(SIGABRT);
}

static void (*atexit_funcs[32])(void);
static int atexit_count = 0;

int atexit(void (*func)(void)) {
    if (atexit_count >= 32) return -1;
    atexit_funcs[atexit_count++] = func;
    return 0;
}

void __atexit_handler(void) {
    for (int i = atexit_count - 1; i >= 0; i--) {
        atexit_funcs[i]();
    }
}

__attribute__((constructor))
static void __init_atexit(void) {
    atexit(__atexit_handler);
}
