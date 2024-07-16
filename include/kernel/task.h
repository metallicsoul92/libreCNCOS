#ifndef LCNC_KERNEL_TASK_H
#define LCNC_KERNEL_TASK_H

#ifndef __HAS_STDINT
#define __HAS_STDINT
#include "../../libc/crt/include/stdint.h"
#endif

#ifndef __HAS_STDDEF
#define __HAS_STDDEF
#include "../../libc/crt/include/stddef.h"
#endif
#include "registers.h"

// Task states
typedef enum {
    TASK_STATE_RUNNING = 0,
    TASK_STATE_READY = 1,
    TASK_STATE_BLOCKED = 2,
    TASK_STATE_TERMINATED = 4
} TaskState;

typedef enum {
  TASK_TYPE_SYSTEM = 1,
  TASK_TYPE_USER = 2
} TaskType;

// Task structure
typedef struct Task {
    reg_t regs;                // Registers of the task
    uint8_t priority;          // Task priority
    TaskState state;           // Current state of the task
    TaskType type;              // Type of the task (e.g., user or system)
    struct Task *prev;         // Previous task in the doubly linked list
    struct Task *next;         // Next task in the doubly linked list
    struct Task *parent;       // Parent task
    struct Task **children;    // Array of pointers to child tasks
    uint32_t numChild;         // Index into parent's children array
    uint32_t numChildren;      // Number of children
    uint32_t maxChildren;      // Maximum number of children
    void* base_addr;           // Base address of the task's virtual memory
    size_t mem_size;           // Size of the task's memory
} task_t;

// Functions to manage tasks
task_t* create_task(uint32_t pid, uint8_t priority, size_t mem_size, task_t* parent);
void terminate_task(task_t* task);
void add_child_task(task_t* parent, task_t* child);
void remove_child_task(task_t* parent, task_t* child);

#endif // TASK_H
