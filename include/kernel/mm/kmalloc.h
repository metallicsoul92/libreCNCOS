#ifndef LCNC_KERNEL_MM_MALLOC_H
#define LCNC_KERNEL_MM_MALLOC_H


#ifndef __HAS_STDDEF
#define __HAS_STDDEF
#include "../../../libc/crt/include/stddef.h"
#endif


void init_heap();
void* basic_kmalloc(size_t size);
void basic_kfree(void* ptr);
void* kmalloc(size_t size);
void* krealloc(void* ptr, size_t size);
void kfree(void* ptr);

#endif // LCNC_KERNEL_MM_MALLOC_H
