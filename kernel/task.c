#include "../include/kernel/task.h"
#include "../include/kernel/mm/memory.h"
#include "../include/kernel/mm/kmalloc.h" // for kmalloc
#include "../libc/crt/include/string.h"

// Initialize a global memory manager
MemoryManager memory_manager;

task_t* create_task(uint32_t pid, uint8_t priority, size_t mem_size, task_t* parent) {
    task_t* task = (task_t*)kmalloc(sizeof(task_t));
    if (task == NULL) {
        // Handle allocation failure
        return NULL;
    }

    memset(task, 0, sizeof(task_t));
    task->priority = priority;
    task->state = TASK_STATE_READY;
    task->type = (parent == NULL) ? TASK_TYPE_SYSTEM : TASK_TYPE_USER; // Default to user type if parent is provided
    task->parent = parent;
    task->numChild = 0;
    task->numChildren = 0;
    task->maxChildren = 4;
    task->children = (task_t**)kmalloc(task->maxChildren * sizeof(task_t*));
    if (task->children == NULL) {
        // Handle allocation failure
        kfree(task);
        return NULL;
    }
    task->base_addr = kmalloc(mem_size);
    if (task->base_addr == NULL) {
        // Handle allocation failure
        kfree(task->children);
        kfree(task);
        return NULL;
    }
    task->mem_size = mem_size;

    // Add the task's memory to the memory manager
    add_memory_region(&memory_manager, task->base_addr, mem_size, task->type == TASK_TYPE_SYSTEM ? MEMORY_REGION_SYSTEM : MEMORY_REGION_USER);

    if (parent != NULL) {
        add_child_task(parent, task);
    }

    return task;
}

void terminate_task(task_t* task) {
    if (task == NULL) {
        return;
    }

    // Remove the task's memory from the memory manager
    remove_memory_region(&memory_manager, task->base_addr);

    // Free the task's memory
    kfree(task->base_addr);

    // Remove the task from its parent's children list
    if (task->parent != NULL) {
        remove_child_task(task->parent, task);
    }

    // Free the task's children array
    kfree(task->children);

    // Finally, free the task itself
    kfree(task);
}

void add_child_task(task_t* parent, task_t* child) {
    if (parent->numChildren >= parent->maxChildren) {
        // Reallocate to accommodate more children
        parent->maxChildren *= 2;
        task_t** new_children = (task_t**)krealloc(parent->children, parent->maxChildren * sizeof(task_t*));
        if (new_children == NULL) {
            // Handle allocation failure
            return;
        }
        parent->children = new_children;
    }

    parent->children[parent->numChildren] = child;
    child->numChild = parent->numChildren;
    parent->numChildren++;
}

void remove_child_task(task_t* parent, task_t* child) {
    if (parent == NULL || child == NULL || parent->numChildren == 0) {
        return;
    }

    // Find the child in the parent's children array
    for (uint32_t i = 0; i < parent->numChildren; i++) {
        if (parent->children[i] == child) {
            // Shift remaining children left to fill the gap
            for (uint32_t j = i; j < parent->numChildren - 1; j++) {
                parent->children[j] = parent->children[j + 1];
                parent->children[j]->numChild = j;
            }
            parent->numChildren--;
            return;
        }
    }
}
