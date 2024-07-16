// cpuid.h

#ifndef LCNC_KERNEL_CPUID_H
#define LCNC_KERNEL_CPUID_H

#ifndef __HAS_STDINT
#define __HAS_STDINT
#include "../../libc/crt/include/stdint.h"
#endif

void cpuid(uint32_t leaf, uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx);
void cpuid_count(uint32_t leaf, uint32_t subleaf, uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx);

#endif // CPUID_H
