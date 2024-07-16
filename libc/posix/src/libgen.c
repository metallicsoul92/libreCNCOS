#include "../include/libgen.h"
#include "../../crt/include/string.h"

#ifndef LIBC_DQPTH
  #ifndef LIBC_SQPTH
    #define LIBC_SQPTH 1
    #undef LIBC_DQPTH
  #endif
#endif

#ifdef LIBC_SQPTH
  #define PTOKEN '/'
#endif

#ifdef LIBC_DQPTH
  #define PTOKEN "//"
#endif



char *basename(char *path) {
    if (path == NULL || *path == '\0') {
        return ".";
    }

    char *p = strrchr(path, PTOKEN);
    return p ? p + 1 : path;
}

char *dirname(char *path) {
    static char dot[] = ".";
    char *prevSlash;

    if (path == NULL || *path == '\0') {
        return dot;
    }

    prevSlash = strrchr(path, PTOKEN);

    if (prevSlash == path) {
        ++prevSlash;
    } else if (prevSlash != NULL && prevSlash[1] == '\0') {
        prevSlash = memchr(path, prevSlash - path, PTOKEN);
    }

    if (prevSlash != NULL) {
        prevSlash[0] = '\0';
    } else {
        path = dot;
    }

    return path;
}
