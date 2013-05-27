
nasm -f elf64 rotatematrix.asm -g
gcc -Wall -ansi -pedantic -std=c99 generate_raw_matrix.c rotatematrix.o -o a.out

