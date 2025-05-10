nasm -f elf32 kernel.asm -o bin/kasm.o
gcc -m32 -c -fno-stack-protector main.c -o bin/main.o
ld -m elf_i386 -T linker.ld -o kernel bin/kasm.o bin/main.o
