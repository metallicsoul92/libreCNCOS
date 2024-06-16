#ifndef LCNC_LC_CRT_SETJMP_H
#define LCNC_LC_CRT_SETJMP_H

// Define a type to hold the state information
typedef struct {
    long rbx;    // Callee-saved register
    long rbp;    // Base pointer
    long r12;    // Callee-saved register
    long r13;    // Callee-saved register
    long r14;    // Callee-saved register
    long r15;    // Callee-saved register
    long rsp;    // Stack pointer
    long rip;    // Instruction pointer
} jmp_buf[1];


// Save the current execution state
int setjmp(jmp_buf env);

// Restore the execution state saved by setjmp
void longjmp(jmp_buf env, int val);

#endif // SETJMP_H
