#!/bin/sh

# Create ISO directory structure
ISO_DIR=isodir

mkdir -p $ISO_DIR/boot/grub
mkdir -p $ISO_DIR/bin
mkdir -p $ISO_DIR/dev
mkdir -p $ISO_DIR/etc
mkdir -p $ISO_DIR/home
mkdir -p $ISO_DIR/lib
mkdir -p $ISO_DIR/mnt
mkdir -p $ISO_DIR/proc
mkdir -p $ISO_DIR/root
mkdir -p $ISO_DIR/sbin
mkdir -p $ISO_DIR/sys
mkdir -p $ISO_DIR/tmp
mkdir -p $ISO_DIR/usr
mkdir -p $ISO_DIR/var

# Additional directories for the libraries and drivers
mkdir -p $ISO_DIR/usr/lib
mkdir -p $ISO_DIR/usr/lib/osutils
mkdir -p $ISO_DIR/usr/lib/drivers

# Copy the loader and kernel
cp bin/loader $ISO_DIR/boot/loader
cp bin/kernel $ISO_DIR/boot/kernel

# Copy the libraries
cp bin/libc_crt.a $ISO_DIR/usr/lib/
cp bin/libc_posix.a $ISO_DIR/usr/lib/
cp bin/osutils.a $ISO_DIR/usr/lib/osutils/
cp bin/drivers_fs_vfs.a $ISO_DIR/usr/lib/drivers/

# Create grub.cfg
cat > $ISO_DIR/boot/grub/grub.cfg << EOF
set timeout=0
set default=0

menuentry "libreCNCOS" {
    multiboot /boot/loader
    module /boot/kernel
    boot
}
EOF

# Create the ISO
grub-mkrescue -o libreCNCOS.iso $ISO_DIR
