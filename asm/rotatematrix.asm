
bits 64

; from the system's C library
extern rand

; parameter order: rdi, rsi, rdx, rcx, r8, r9

global asmrotatematrix
global asmfillmatrixrandom
global asmfillmatrixfixed
global asmfillmatrixsequential
global testvalgrindboundschecking

section .text

asmrotatematrix: ; parameters are address of a[0][0] (rdi), and dimension (rsi)

cmp esi, 1
jle .exit

mov ecx, esi ; 32-bit mov zero-extends to fill 64-bit reg
shr ecx, 1

; so now ecx has floor(n/2)
.rowloop: ; in this loop, ecx is the row number r
dec ecx ; decrement to make it zero-indexed

; compute anchors in eax and store in r1x
mov eax, esi
inc eax
mul ecx
mov r10d, eax ; a0

; compute n-1-2r factor
mov eax, esi
dec eax
sub eax, ecx
sub eax, ecx

mov r11d, r10d
add r11d, eax ; a1

push rax
mul esi ; now eax has n*(n-1-2r)
mov r8d, r11d
add r8d, eax ; a2
mov r9d, r10d
add r9d, eax ; a3
;div esi ; the push rax/pop rax uses less cycles
pop rax ; eax is now n-1-2r again
push rcx ; preserve the rowloop counter
mov ecx, eax ; n-1-2r is the colloop counter

.colloop:

mov rax, [rdi+8*r9]   ; a3
xchg rax, [rdi+8*r10] ; a0
xchg rax, [rdi+8*r11] ; a2
xchg rax, [rdi+8*r8]  ; a1
mov [rdi+8*r9], rax   ; a3

inc r10d
add r11d, esi
dec r8d
sub r9d, esi

loop .colloop
pop rcx ; restore the rowloop counter

test ecx, ecx
jnz .rowloop ; because we need zero to count, can't use the loop instruction

.exit:
ret

asmfillmatrixrandom: ; parametrs are: address of a[0][0] (rdi), dimension (rsi)
mov eax, esi
mul eax
mov ecx, eax

.lol:
push rcx
push rdi
call rand
cld
pop rdi
pop rcx
and rax, 0xff
stosq
loop .lol

ret


asmfillmatrixfixed: ; parameters are: address of a[0][0] (rdi), dimension (rsi), fill value (rdx)
mov eax, esi
mul eax
mov ecx, eax
mov eax, edx
rep stosq
ret

asmfillmatrixsequential: ; rdi is the address of a[0][0], rsi is the dimension
mov eax, esi
mul eax
mov ecx, eax

mov rax, 0
.lol:
stosq
inc rax
loop .lol

ret

testvalgrindboundschecking: ; rdi is an array with rsi elements of size 8; try to access the bytes before and after to trigger a valgrind warning
sub rdi, 8
mov rax, [rdi+8*rsi+8]
inc rax ; the former mov seems to get optimized out without this
mov rax, [rdi]
ret

