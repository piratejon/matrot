
bits 64

; from the system's C library
extern rand

; parameter order: rdi, rsi, rdx, rcx, r8, r9

global asmrotatematrix
global asmfillmatrixrandom
global asmfillmatrixfixed

section .text

asmrotatematrix: ; parameters are address of a[0][0] (rdi), and dimension (rsi)
push rbx
push rdx

mov ecx, esi ; 32-bit mov zero-extends to fill 64-bit reg
mov ecx, edx
shr ecx, 1

; so now ecx has floor(n/2) and edx has n
_rowloop: ; in this loop, ecx is the row number r

; compute a_x in eax and store in r1x
mov eax, esi
inc eax
mul ecx
add eax, edi
mov r10d, eax ; a0

; compute n-1-2r factor
mov eax, edx
dec eax
sub eax, ecx
sub eax, ecx
push rax

mov r11d, r10d
add r11d, eax ; a1

mul edx ; now eax has n*(n-1-2r)
mov r12d, r11d
add r12d, eax ; a2
mov r13d, r10d
add r13d, eax ; a3

pop rax ; used 4 bytes of RAM to save 8 bytes of instructions!
; eax is now n-1-2r again
push rcx
mov ecx, eax ; this is the within-row loop

push qword [r10d]
push qword [r11d]
push qword [r12d]
push qword [r13d]

pop qword [r10d]
pop qword [r13d]
pop qword [r12d]
pop qword [r11d]

pop rcx

loop _rowloop

pop rbx
pop rdx
ret

asmfillmatrixrandom: ; parametrs are: address of a[0][0] (rdi), dimension (rsi)
mov eax, esi
mul eax
mov ecx, eax

lol:
push rcx
push rdi
call rand
cld
pop rdi
pop rcx
and eax, 0x000000ff
stosq
loop lol

ret


asmfillmatrixfixed: ; parameters are: address of a[0][0] (rdi), dimension (rsi), fill value (rdx)
mov eax, esi
mul eax
mov ecx, eax
mov eax, edx
rep stosq

ret

