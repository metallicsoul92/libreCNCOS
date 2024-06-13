#ifndef UNISTD_H
#define UNISTD_H

#include "sys/types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Constants */
#define SEEK_SET    0   /* Set file offset to `offset` */
#define SEEK_CUR    1   /* Set file offset to current plus `offset` */
#define SEEK_END    2   /* Set file offset to EOF plus `offset` */

/* Function Prototypes */
int access(const char *pathname, int mode);
unsigned int alarm(unsigned int seconds);
int chdir(const char *path);
int close(int fd);
size_t read(int fd, void *buf, size_t count);
size_t write(int fd, const void *buf, size_t count);
int dup(int oldfd);
int dup2(int oldfd, int newfd);
int execl(const char *path, const char *arg, ...);
int execv(const char *path, char *const argv[]);
pid_t fork(void);
pid_t getpid(void);
pid_t getppid(void);
int pipe(int pipefd[2]);
ssize_t readlink(const char *path, char *buf, size_t bufsiz);
int rmdir(const char *path);
int setpgid(pid_t pid, pid_t pgid);
unsigned int sleep(unsigned int seconds);
int unlink(const char *pathname);
int usleep(useconds_t usec);

#ifdef __cplusplus
}
#endif

#endif /* UNISTD_H */
