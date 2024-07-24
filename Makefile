# Top-level Makefile
.PHONY: all libc osutils drivers loader kernel isodir iso clean

all: libc osutils drivers loader kernel

libc:
	$(MAKE) -C libc/crt/src
	$(MAKE) -C libc/posix/src

osutils:
	$(MAKE) -C osutils

drivers:
	$(MAKE) -C drivers/fs/vfs

loader:
	$(MAKE) -C arch/x86
	$(MAKE) -C loader

kernel:
	$(MAKE) -C arch/x64
	$(MAKE) -C kernel

isodir:
	mkdir -p isodir/boot/grub
	mkdir -p isodir/usr/lib/osutils
	mkdir -p isodir/usr/lib/drivers
	cp bin/loader isodir/boot/loader
	cp bin/kernel isodir/boot/kernel
	cp bin/libc_crt.a isodir/usr/lib/
	cp bin/libc_posix.a isodir/usr/lib/
	cp bin/osutils.a isodir/usr/lib/osutils/
	cp bin/drivers_fs_vfs.a isodir/usr/lib/drivers/
	cp tools/grub.cfg isodir/boot/grub

iso: isodir
	grub-mkrescue -o libreCNCOS.iso isodir

clean:
	$(MAKE) -C libc/crt/src clean
	$(MAKE) -C libc/posix/src clean
	$(MAKE) -C osutils clean
	$(MAKE) -C drivers/fs/vfs clean
	$(MAKE) -C arch/x86 clean
	$(MAKE) -C loader clean
	$(MAKE) -C arch/x64 clean
	$(MAKE) -C kernel clean
	rm -rf isodir
	rm -f libreCNCOS.iso
	rm -rf bin
