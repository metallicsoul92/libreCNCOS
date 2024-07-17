#ifndef LCNC_KERNEL_SYSCALLS_H
#define LCNC_KERNEL_SYSCALLS_H

#include "../../libc/posix/include/sys/types.h"

void * sbrk(ptrdiff_t increment);
void* mmap(void* addr, size_t length, int prot, int flags, int fd, off_t offset);

#endif
