#ifndef LCNC_KERNEL_MM_PMM_H
#define LCNC_KERNEL_MM_PMM_H

#ifndef __HAS_STDINT
#include <stdint.h>
#define __HAS_STDINT
#endif

#ifndef __HAS_STDDEF
#include <stddef.h>
#define __HAS_STDDEF
#endif

#define PAGE_SIZE 4096

void init_pmm(size_t total_memory);
void* alloc_page();
void free_page(void* page);

#endif // LCNC_KERNEL_MM_PMM_H
