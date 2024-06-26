#ifndef VFS_H
#define VFS_H

#ifndef __HAS_STDINT
#define __HAS_STDINT
#include <stdint.h>
#endif

#ifndef __HAS_STDDEF
#define __HAS_STDDEF
#include <stddef.h>
#endif

// Enum to differentiate between file and directory entries
typedef enum {
    FILE_ENTRY,
    DIRECTORY_ENTRY
} EntryType;

// File structure
typedef struct {
    const char* name;  // Name of the file
    size_t size;       // Size of the file in bytes
    void* data;        // Placeholder for actual data in a real implementation
} File;

// Forward declaration of Directory structure
struct Directory;

// Directory entry structure
typedef struct VfsDirEntry {
    EntryType type;  // Type of the entry (file or directory)
    union {
        File* file;        // Pointer to a file structure
        struct Directory* directory;  // Pointer to a directory structure
    } entry;
} VfsDirEntry;

// Directory structure
typedef struct Directory {
    const char* name;        // Name of the directory
    VfsDirEntry* entries;    // Array of directory entries
    size_t num_entries;      // Number of entries in the directory
} Directory;

// Structure representing a file system
typedef struct {
    const char* fs_name;    // Name of the file system
    void* fs_data;          // File system specific data
    int (*mount)(void* fs_data);      // Function to mount the file system
    int (*unmount)();                 // Function to unmount the file system
    File* (*open)(const char* path, const char* mode); // Function to open a file
    int (*close)(File* file);                          // Function to close a file
    size_t (*read)(File* file, void* buffer, size_t size); // Function to read from a file
    size_t (*write)(File* file, const void* buffer, size_t size); // Function to write to a file
} FileSystem;

// Functions to interact with the VFS
int vfs_mount(FileSystem* fs);  // Mount a file system
int vfs_unmount();              // Unmount the current file system
File* vfs_open(const char* path, const char* mode);  // Open a file
int vfs_close(File* file);      // Close a file
size_t vfs_read(File* file, void* buffer, size_t size);  // Read from a file
size_t vfs_write(File* file, const void* buffer, size_t size);  // Write to a file

#endif // VFS_H
