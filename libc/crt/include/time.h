#ifndef LCNC_LC_CRT_TIME_H
#define LCNC_LC_CRT_TIME_H

// Types
typedef long time_t;
typedef long clock_t;
struct tm {
    int tm_sec;   // seconds after the minute - [0, 60] including leap second
    int tm_min;   // minutes after the hour - [0, 59]
    int tm_hour;  // hours since midnight - [0, 23]
    int tm_mday;  // day of the month - [1, 31]
    int tm_mon;   // months since January - [0, 11]
    int tm_year;  // years since 1900
    int tm_wday;  // days since Sunday - [0, 6]
    int tm_yday;  // days since January 1 - [0, 365]
    int tm_isdst; // daylight saving time flag
};

// Constants
#define CLOCKS_PER_SEC 1000

// Time manipulation functions
time_t time(time_t *tloc);
double difftime(time_t time1, time_t time0);
time_t mktime(struct tm *timeptr);

// Formatting functions
char *asctime(const struct tm *timeptr);
char *ctime(const time_t *timer);
struct tm *gmtime(const time_t *timer);
struct tm *localtime(const time_t *timer);

// Clock functions
clock_t clock(void);

#endif /* _TIME_H */
