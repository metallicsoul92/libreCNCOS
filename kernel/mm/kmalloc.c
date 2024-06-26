#include "../../include/kernel/mm/kmalloc.h"
#include "../../include/kernel/mm/pmm.h"
#include "../../include/kernel/mm/vmm.h"

#define INITIAL_HEAP_SIZE (1024 * 1024) // 1MB initial heap
#define EXPANSION_SIZE (1024 * 1024)    // 1MB expansion size

typedef struct Block {
    size_t size;
    struct Block* next;
    int free;
} Block;

#define BLOCK_SIZE sizeof(Block)

static uint8_t initial_heap[INITIAL_HEAP_SIZE];
static Block* free_list = (Block*)initial_heap;

void init_heap() {
    free_list->size = INITIAL_HEAP_SIZE - BLOCK_SIZE;
    free_list->next = NULL;
    free_list->free = 1;
}

void split_block(Block* block, size_t size) {
    Block* new_block = (Block*)((uint8_t*)block + size + BLOCK_SIZE);
    new_block->size = block->size - size - BLOCK_SIZE;
    new_block->next = block->next;
    new_block->free = 1;

    block->size = size;
    block->next = new_block;
}

void* basic_kmalloc(size_t size) {
    Block* current = free_list;
    while (current != NULL) {
        if (current->free && current->size >= size) {
            if (current->size > size + BLOCK_SIZE) {
                split_block(current, size);
            }
            current->free = 0;
            return (void*)((uint8_t*)current + BLOCK_SIZE);
        }
        current = current->next;
    }
    return NULL; // No suitable block found
}

void merge_blocks() {
    Block* current = free_list;
    while (current != NULL && current->next != NULL) {
        if (current->free && current->next->free) {
            current->size += current->next->size + BLOCK_SIZE;
            current->next = current->next->next;
        } else {
            current = current->next;
        }
    }
}

void basic_kfree(void* ptr) {
    if (ptr == NULL) return;

    Block* block = (Block*)((uint8_t*)ptr - BLOCK_SIZE);
    block->free = 1;
    merge_blocks();
}

void expand_heap(size_t size) {
    // Allocate a new block of memory for expansion
    uint8_t* new_block = (uint8_t*)alloc_page();
    memset(new_block, 0, PAGE_SIZE);

    // Add the new block to the free list
    Block* new_free_block = (Block*)new_block;
    new_free_block->size = PAGE_SIZE - BLOCK_SIZE;
    new_free_block->next = NULL;
    new_free_block->free = 1;

    // Find the end of the free list
    Block* current = free_list;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_free_block;
}

void* kmalloc(size_t size) {
    Block* current = free_list;
    while (current != NULL) {
        if (current->free && current->size >= size) {
            if (current->size > size + BLOCK_SIZE) {
                split_block(current, size);
            }
            current->free = 0;

            void* virtual_address = (void*)((uint8_t*)current + BLOCK_SIZE);
            void* physical_address = alloc_page();
            map_page(virtual_address, physical_address);

            return virtual_address;
        }
        current = current->next;
    }

    // Expand the heap if no suitable block is found
    expand_heap(EXPANSION_SIZE);
    return kmalloc(size); // Retry allocation after expansion
}

void kfree(void* ptr) {
    if (ptr == NULL) return;

    // Translate the virtual address to a physical address and free it
    void* physical_address = translate(ptr);
    if (physical_address != NULL) {
        free_page(physical_address);
    }

    // Free the block in the heap
    Block* block = (Block*)((uint8_t*)ptr - BLOCK_SIZE);
    block->free = 1;
    merge_blocks();
}
