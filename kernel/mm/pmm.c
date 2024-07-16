#include "../../include/kernel/mm/pmm.h"
#include "../../libc/crt/include/string.h"
#include "../../include/kernel/mm/kmalloc.h"

static uint8_t* bitmap;
static size_t total_pages;

void init_pmm(size_t total_memory) {
    total_pages = total_memory / PAGE_SIZE;
    size_t bitmap_size = total_pages / 8 + 1; // One bit per page
    bitmap = (uint8_t*)basic_kmalloc(bitmap_size);
    memset(bitmap, 0, bitmap_size); // Mark all pages as free
}

static void bitmap_set(int bit) {
    bitmap[bit / 8] |= (1 << (bit % 8));
}

static void bitmap_clear(int bit) {
    bitmap[bit / 8] &= ~(1 << (bit % 8));
}

static int bitmap_test(int bit) {
    return bitmap[bit / 8] & (1 << (bit % 8));
}

void* alloc_page() {
    for (size_t i = 0; i < total_pages; i++) {
        if (!bitmap_test(i)) {
            bitmap_set(i);
            return (void*)(i * PAGE_SIZE);
        }
    }
    return NULL; // No free pages available
}

void free_page(void* page) {
    size_t page_index = (size_t)page / PAGE_SIZE;
    if (page_index < total_pages) {
        bitmap_clear(page_index);
    }
}
