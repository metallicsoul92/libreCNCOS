#ifndef LCNC_LC_CRT_SETJMP_H
#define LCNC_LC_CRT_SETJMP_H

// Define a type to hold the state information
typedef struct {
    unsigned long long rbp;   // Base pointer
    unsigned long long rsp;   // Stack pointer
    unsigned long long rip;   // Instruction pointer
    unsigned long long rdi;   // General purpose register
    unsigned long long rsi;   // General purpose register
    unsigned long long rdx;   // General purpose register
    unsigned long long rcx;   // General purpose register
} jmp_buf[1];

// Save the current execution state
int setjmp(jmp_buf env);

// Restore the execution state saved by setjmp
void longjmp(jmp_buf env, int val);

#endif // SETJMP_H
