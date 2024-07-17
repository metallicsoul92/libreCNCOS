# Top-level Makefile
.PHONY: all loader kernel drivers libc isodir iso clean

all: loader kernel drivers libc

loader:
	$(MAKE) -C arch/x86
	$(MAKE) -C loader

kernel:
	$(MAKE) -C kernel

drivers:
	$(MAKE) -C drivers

osutils:
	$(MAKE) -C osutils

libc:
	$(MAKE) -C libc/crt/src
	$(MAKE) -C libc/posix/src

isodir:
	mkdir -p isodir/boot/grub
	cp bin/loader isodir/boot/loader
	cp bin/kernel isodir/boot/kernel
	cp tools/grub.cfg isodir/boot/grub

iso: isodir
	grub-mkrescue -o libreCNCOS.iso isodir

clean:
	$(MAKE) -C arch/x86 clean
	$(MAKE) -C kernel clean
	$(MAKE) -C drivers clean
	$(MAKE) -C osutils clean
	$(MAKE) -C libc/crt/src clean
	$(MAKE) -C libc/posix/src clean
	rm -rf isodir
	rm -f libreCNCOS.iso
	rm -rf bin
