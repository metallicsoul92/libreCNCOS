#ifndef LCNC_LC_CRT_SIGNAL_H
#define LCNC_LC_CRT_SIGNAL_H

// Signal numbers
#define SIGABRT   1   // Abort signal
#define SIGFPE    2   // Floating point exception
#define SIGILL    3   // Illegal instruction
#define SIGINT    4   // Interrupt
#define SIGSEGV   5   // Segmentation fault
#define SIGTERM   6   // Termination signal

// Signal handling functions
typedef void (*sighandler_t)(int);

// Set a signal handler for a specific signal
sighandler_t signal(int signum, sighandler_t handler);

// Signal constants for use with signal function
#define SIG_DFL ((sighandler_t)0)   // Default signal handling
#define SIG_IGN ((sighandler_t)1)   // Ignore signal

#endif // SIGNAL_H
