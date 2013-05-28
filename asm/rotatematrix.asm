
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
push rdx

cmp rsi, 1
jle .exit

mov ecx, esi ; 32-bit mov zero-extends to fill 64-bit reg
; mov edx, ecx
shr ecx, 1

; so now ecx has floor(n/2)
.rowloop: ; in this loop, ecx is the row number r
dec ecx ; decrement to make it zero-indexed

; compute anchors in eax and store in r1x
mov eax, esi
inc eax
mul ecx
; add eax, edi
mov r10d, eax ; a0

; compute n-1-2r factor
mov eax, esi
dec eax
sub eax, ecx
sub eax, ecx
push rax

mov r11d, r10d
add r11d, eax ; a1

mul esi ; now eax has n*(n-1-2r)
mov r8d, r11d
add r8d, eax ; a2
mov r9d, r10d
add r9d, eax ; a3

pop rax ; used 8 bytes of RAM to save 8 bytes of instructions!
; eax is now n-1-2r again
push rcx
mov ecx, eax ; this is the within-row loop

.colloop:

mov rax, [rdi+8*r9]
xchg rax, [rdi+8*r10]
xchg rax, [rdi+8*r11]
xchg rax, [rdi+8*r8]
mov [rdi+8*r9], rax

inc r10d
add r11d, esi
dec r8d
sub r9d, esi

loop .colloop
pop rcx

test ecx, ecx
jnz .rowloop ; because we need zero to count, can't use the loop instruction

.exit:
pop rdx
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

testvalgrindboundschecking: ; rdi is an array with rsi elements; try to access the bytes before and after to trigger a valgrind warning
sub rdi, 8
mov rax, [rdi+8*rsi+8]
inc rax ; the former mov seems to get optimized out without this
mov rax, [rdi]
ret

