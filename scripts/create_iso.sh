#!/bin/bash

# Define the target directories
ISO_DIR="iso"
BOOT_DIR="$ISO_DIR/boot"
GRUB_DIR="$BOOT_DIR/grub"

# Create POSIX-compliant directory structure
mkdir -p $GRUB_DIR
mkdir -p $ISO_DIR/bin
mkdir -p $ISO_DIR/dev
mkdir -p $ISO_DIR/etc
mkdir -p $ISO_DIR/home
mkdir -p $ISO_DIR/lib
mkdir -p $ISO_DIR/mnt
mkdir -p $ISO_DIR/opt
mkdir -p $ISO_DIR/proc
mkdir -p $ISO_DIR/root
mkdir -p $ISO_DIR/run
mkdir -p $ISO_DIR/sbin
mkdir -p $ISO_DIR/srv
mkdir -p $ISO_DIR/sys
mkdir -p $ISO_DIR/tmp
mkdir -p $ISO_DIR/usr/bin
mkdir -p $ISO_DIR/usr/lib
mkdir -p $ISO_DIR/usr/sbin
mkdir -p $ISO_DIR/var
mkdir -p $ISO_DIR/var/log

# Copy the kernel binary
cp bin/kernel.bin $BOOT_DIR/

# Create grub.cfg
cat > $GRUB_DIR/grub.cfg <<EOF
set timeout=5
set default=0

menuentry "libreCNCOS" {
    multiboot2 /boot/kernel.bin
    boot
}
EOF

# Create the ISO image
grub-mkrescue -o libreCNCOS.iso $ISO_DIR

# Clean up
rm -rf $ISO_DIR

echo "ISO image created as libreCNCOS.iso"
