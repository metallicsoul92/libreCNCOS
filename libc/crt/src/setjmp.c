#include "../include/setjmp.h"

int setjmp(jmp_buf env) {
    __asm__ __volatile__ (
        "movq %%rbx, 0(%0)\n"    // Save rbx
        "movq %%rbp, 8(%0)\n"    // Save rbp
        "movq %%r12, 16(%0)\n"   // Save r12
        "movq %%r13, 24(%0)\n"   // Save r13
        "movq %%r14, 32(%0)\n"   // Save r14
        "movq %%r15, 40(%0)\n"   // Save r15
        "movq %%rsp, 48(%0)\n"   // Save rsp
        "leaq 1f(%%rip), %%rax\n" // Save rip
        "movq %%rax, 56(%0)\n"
        "1:\n"
        : /* No output */
        : "r" (env)
        : "memory", "rax"
    );
    return 0;
}


void longjmp(jmp_buf env, int val) {
    __asm__ __volatile__ (
        "movq 0(%0), %%rbx\n"    // Restore rbx
        "movq 8(%0), %%rbp\n"    // Restore rbp
        "movq 16(%0), %%r12\n"   // Restore r12
        "movq 24(%0), %%r13\n"   // Restore r13
        "movq 32(%0), %%r14\n"   // Restore r14
        "movq 40(%0), %%r15\n"   // Restore r15
        "movq 48(%0), %%rsp\n"   // Restore rsp
        "movq 56(%0), %%rax\n"   // Restore rip
        "movl %1, %%edx\n"       // Set return value
        "testq %%rax, %%rax\n"   // Check if rip is 0
        "jz 2f\n"
        "jmp *%%rax\n"           // Jump to saved rip
        "2:\n"
        : /* No output */
        : "r" (env), "r" (val)
        : "memory", "rax", "rdx"
    );
}
