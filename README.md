# colour-os
Operating system written in C for study (my first osdev proj)

# building
- tools needed to compile: nasm, gcc, qemu
- sudo apt install nasm gcc qemu-all (ubuntu, mint)
- sudo pacman -S nasm, gcc, qemu-all (arch, arch based)
  BUILDING
- nasm -f elf32 kernel.asm -o kasm.o
- gcc -m32 -c main.c -o main.o
- ld -m elf_i386 -T linker.ld -o kernel kasm.o main.o
  RUNNING
- qemu-system-i386 -kernel kernel
