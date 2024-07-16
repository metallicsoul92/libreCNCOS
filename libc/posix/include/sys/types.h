#ifndef LCNC_LC_POSIX_SYS_TYPES_H
#define LCNC_LC_POSIX_SYS_TYPES_H


#include "../../../crt/include/stddef.h"
#include "../../../crt/include/stdint.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef int pid_t;
typedef unsigned int uid_t;
typedef unsigned int gid_t;
typedef unsigned int dev_t;
typedef unsigned long ino_t;
typedef unsigned int mode_t;
typedef unsigned long nlink_t;
typedef long off_t;
typedef int64_t blkcnt_t;
typedef int64_t blksize_t;
typedef int64_t fsblkcnt_t;
typedef int64_t fsfilcnt_t;
typedef int id_t;
typedef long key_t;
typedef unsigned long useconds_t;
typedef int64_t suseconds_t;
typedef int ssize_t;

#ifndef NULL
#define NULL ((void *)0)
#endif

#ifndef __HAS_MAP_FAILED
#define MAP_FAILED ((void*)-1)
#define __HAS_MAP_FAILED
#endif

#ifdef __cplusplus
}
#endif

#endif /* SYS_TYPES_H */
