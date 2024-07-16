#ifndef LCNC_LC_POSIX_FCNTL_H
#define LCNC_LC_POSIX_FCNTL_H

#include "sys/types.h" // For off_t and pid_t

#ifdef __cplusplus
extern "C" {
#endif

/* File descriptor flags for open() and fcntl() */
#define O_RDONLY    0       /* Open for reading only */
#define O_WRONLY    1       /* Open for writing only */
#define O_RDWR      2       /* Open for reading and writing */
#define O_CREAT     0100    /* Create file if it does not exist */
#define O_TRUNC     01000   /* Truncate file to length 0 */
#define O_APPEND    02000   /* Set append mode */
#define O_EXCL      0200    /* Exclusive use flag for O_CREAT */

/* File status flags for fcntl() */
#define O_NONBLOCK  04000   /* Non-blocking mode */
#define O_SYNC      04010000/* Synchronous writes */
#define O_FSYNC     O_SYNC  /* Synchronous writes for POSIX compatibility */

/* Advisory file segment locking */
struct flock {
    short l_type;    /* Type of lock: F_RDLCK, F_WRLCK, F_UNLCK */
    short l_whence;  /* How to interpret l_start: SEEK_SET, SEEK_CUR, SEEK_END */
    off_t l_start;   /* Starting offset for lock */
    off_t l_len;     /* Number of bytes to lock */
    pid_t l_pid;     /* PID of process blocking our lock (F_GETLK only) */
};

/* Commands for fcntl() */
#define F_DUPFD     0       /* Duplicate file descriptor */
#define F_GETFD     1       /* Get file descriptor flags */
#define F_SETFD     2       /* Set file descriptor flags */
#define F_GETFL     3       /* Get file status flags */
#define F_SETFL     4       /* Set file status flags */
#define F_GETLK     5       /* Get record locking information */
#define F_SETLK     6       /* Set record locking information */
#define F_SETLKW    7       /* Set record locking information; wait if blocked */

/* Lock types */
#define F_RDLCK     0       /* Read lock */
#define F_WRLCK     1       /* Write lock */
#define F_UNLCK     2       /* Remove lock */

/* Function prototype */
int fcntl(int fd, int cmd, ...);

#ifdef __cplusplus
}
#endif

#endif /* LCNC_LC_POSIX_FCNTL_H */
