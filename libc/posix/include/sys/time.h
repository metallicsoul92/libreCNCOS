#ifndef LCNC_LC_POSIX_SYS_TIME_H
#define LCNC_LC_POSIX_SYS_TIME_H

#include "../../crt/time.h"
#include "types.h"


#ifdef __cplusplus
extern "C" {
#endif

struct timeval {
    time_t      tv_sec;     /* seconds */
    suseconds_t tv_usec;    /* microseconds */
};

struct timezone {
    int tz_minuteswest;     /* minutes west of Greenwich */
    int tz_dsttime;         /* type of DST correction */
};

int gettimeofday(struct timeval *tv, struct timezone *tz);
int settimeofday(const struct timeval *tv, const struct timezone *tz);

#ifdef __cplusplus
}
#endif

#endif /* SYS_TIME_H */
