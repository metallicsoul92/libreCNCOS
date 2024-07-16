#include "../../../include/drivers/fs/vfs/vfs.h"

// Internal storage of the mounted file system
static FileSystem* mounted_fs = NULL;

int vfs_mount(FileSystem* fs) {
    if (mounted_fs != NULL) {
        // Unmount current file system if one is already mounted
        vfs_unmount();
    }

    if (fs->mount(fs->fs_data) == 0) {
        mounted_fs = fs;
        return 0;
    }
    return -1; // Mounting failed
}

int vfs_unmount() {
    if (mounted_fs == NULL) {
        return -1; // No file system mounted
    }
    if (mounted_fs->unmount() == 0) {
        mounted_fs = NULL;
        return 0;
    }
    return -1; // Unmounting failed
}

File* vfs_open(const char* path, const char* mode) {
    if (mounted_fs == NULL) {
        return NULL; // No file system mounted
    }
    return mounted_fs->open(path, mode);
}

int vfs_close(File* file) {
    if (mounted_fs == NULL) {
        return -1; // No file system mounted
    }
    return mounted_fs->close(file);
}

size_t vfs_read(File* file, void* buffer, size_t size) {
    if (mounted_fs == NULL) {
        return 0; // No file system mounted
    }
    return mounted_fs->read(file, buffer, size);
}

size_t vfs_write(File* file, const void* buffer, size_t size) {
    if (mounted_fs == NULL) {
        return 0; // No file system mounted
    }
    return mounted_fs->write(file, buffer, size);
}
