#!/usr/bin/env bash


mkdir -p bin
cd bin
mkdir -p x64
mkdir -p x86
mkdir -p drivers
cd drivers
mkdir -p exec
cd exec
mkdir -p elf
cd ../
mkdir -p fs
cd fs
mkdir -p vfs
cd ../
mkdir -p osutils
mkdir -p kernel
cd kernel
mkdir -p mm # Memory Management
mkdir -p sc # System Calls
cd ../
mkdir -p libc
cd libc
mkdir -p crt
mkdir -p posix
mkdir -p posix/sys
cd ../
mkdir -p loader
