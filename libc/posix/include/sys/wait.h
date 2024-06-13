#ifndef SYS_WAIT_H
#define SYS_WAIT_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Macros for WIFEXITED, WEXITSTATUS, WIFSIGNALED, WTERMSIG, WIFSTOPPED, WSTOPSIG */
#define WIFEXITED(status)   (((status) & 0xff) == 0)
#define WEXITSTATUS(status) ((status) >> 8)
#define WIFSIGNALED(status) (((status) & 0xff) > 0 && ((status) & 0x7f) != 0x7f)
#define WTERMSIG(status)    ((status) & 0x7f)
#define WIFSTOPPED(status)  (((status) & 0xff) == 0x7f)
#define WSTOPSIG(status)    WEXITSTATUS(status)

/* Constants for waitpid */
#define WNOHANG     1
#define WUNTRACED   2

/* Types */
typedef int idtype_t;

/* Functions */
pid_t wait(int *status);
pid_t waitpid(pid_t pid, int *status, int options);
int waitid(idtype_t idtype, id_t id, siginfo_t *infop, int options);

#ifdef __cplusplus
}
#endif

#endif /* SYS_WAIT_H */
