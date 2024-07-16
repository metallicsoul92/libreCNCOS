#include "../include/fcntl.h"
#include "../../crt/include/stdarg.h"
#include "../../crt/include/errno.h"
#include "../include/unistd.h"


/* Internal function declarations */
static int __dupfd(int fd, int arg);
static int __getfd(int fd);
static int __setfd(int fd, int arg);
static int __getfl(int fd);
static int __setfl(int fd, int arg);
static int __flock(int fd, int cmd, struct flock *arg);

/* Implementation of fcntl */
int fcntl(int fd, int cmd, ...) {
    va_list args;
    va_start(args, cmd);
    int result = -1;

    switch (cmd) {
        case F_DUPFD: {
            int arg = va_arg(args, int);
            result = __dupfd(fd, arg);
            break;
        }
        case F_GETFD: {
            result = __getfd(fd);
            break;
        }
        case F_SETFD: {
            int arg = va_arg(args, int);
            result = __setfd(fd, arg);
            break;
        }
        case F_GETFL: {
            result = __getfl(fd);
            break;
        }
        case F_SETFL: {
            int arg = va_arg(args, int);
            result = __setfl(fd, arg);
            break;
        }
        case F_GETLK:
        case F_SETLK:
        case F_SETLKW: {
            struct flock *arg = va_arg(args, struct flock *);
            result = __flock(fd, cmd, arg);
            break;
        }
        default: {
            errno = EINVAL;
            result = -1;
        }
    }

    va_end(args);
    return result;
}

/* Internal function implementations */

static int __dupfd(int fd, int arg) {
    // Duplicate the file descriptor fd using the system call
    int newfd = dup2(fd, arg);
    if (newfd == -1) {
        errno = EINVAL;
    }
    return newfd;
}

static int __getfd(int fd) {
    // Get the file descriptor flags using the system call
    int flags = fcntl(fd, F_GETFD);
    if (flags == -1) {
        errno = EINVAL;
    }
    return flags;
}

static int __setfd(int fd, int arg) {
    // Set the file descriptor flags using the system call
    int result = fcntl(fd, F_SETFD, arg);
    if (result == -1) {
        errno = EINVAL;
    }
    return result;
}

static int __getfl(int fd) {
    // Get the file status flags using the system call
    int flags = fcntl(fd, F_GETFL);
    if (flags == -1) {
        errno = EINVAL;
    }
    return flags;
}

static int __setfl(int fd, int arg) {
    // Set the file status flags using the system call
    int result = fcntl(fd, F_SETFL, arg);
    if (result == -1) {
        errno = EINVAL;
    }
    return result;
}

static int __flock(int fd, int cmd, struct flock *arg) {
    // Perform the file locking operation using the system call
    int result = fcntl(fd, cmd, arg);
    if (result == -1) {
        errno = EINVAL;
    }
    return result;
}
