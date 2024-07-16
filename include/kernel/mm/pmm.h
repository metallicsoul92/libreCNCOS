#ifndef LCNC_KERNEL_MM_PMM_H
#define LCNC_KERNEL_MM_PMM_H

#ifndef __HAS_STDINT
#define __HAS_STDINT
#include "../../../libc/crt/include/stdint.h"
#endif


#ifndef __HAS_STDDEF
#define __HAS_STDDEF
#include "../../../libc/crt/include/stddef.h"
#endif


#define PAGE_SIZE 4096

void init_pmm(size_t total_memory);
void* alloc_page();
void free_page(void* page);

#endif // LCNC_KERNEL_MM_PMM_H
