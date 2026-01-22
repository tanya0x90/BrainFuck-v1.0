section .text

global _start

_start:
    mov rbx, buff
    add rbx, 15000
    inc rbx
    mov cl,[rbx]
    add cl, 4
    mov [rbx], cl
    cmp rcx, 0
    je AAACC
AAAAI:
    dec rbx
    mov cl,[rbx]
    add cl, 8
    mov [rbx], cl
    inc rbx
    mov cl, [rbx]
    dec cl
    mov [rbx], cl
    cmp rcx, 0
    jne AAAAI
AAACC:
    inc rbx
    mov cl,[rbx]
    add cl, 8
    mov [rbx], cl
    cmp rcx, 0
    je AAAEE
AAADE:
    inc rbx
    mov cl,[rbx]
    add cl, 4
    mov [rbx], cl
    dec rbx
    mov cl, [rbx]
    dec cl
    mov [rbx], cl
    cmp rcx, 0
    jne AAADE
AAAEE:
    add rbx, 2
    mov cl,[rbx]
    add cl, 2
    mov [rbx], cl
    add rbx, 3
    mov cl, [rbx]
    inc cl
    mov [rbx], cl
    add rbx, 3
    mov cl, [rbx]
    inc cl
    mov [rbx], cl
    sub rbx, 10
    mov cl, [rbx]
    cmp rcx, 0
    je AACHE
AAAGJ:
    mov cl, [rbx]
    dec cl
    mov [rbx], cl
    cmp rcx, 0
    je AAAIA
AAAHD:
    mov cl, [rbx]
    dec cl
    mov [rbx], cl
    inc rbx
    mov cl, [rbx]
    inc cl
    mov [rbx], cl
    dec rbx
    mov cl, [rbx]
    cmp rcx, 0
    jne AAAHD
AAAIA:
    inc rbx
    mov cl, [rbx]
    cmp rcx, 0
    je AAAJG
AAAIE:
    mov cl, [rbx]
    dec cl
    mov [rbx], cl
    dec rbx
    mov cl, [rbx]
    inc cl
    mov [rbx], cl
    add rbx, 3
    call print
    sub rbx, 2
    mov cl, [rbx]
    cmp rcx, 0
    jne AAAIE
AAAJG:
    add rbx, 3
    mov cl, [rbx]
    cmp rcx, 0
    je AABIC
AABAC:
    mov cl, [rbx]
    cmp rcx, 0
    je AABHJ
AABAF:
    mov cl, [rbx]
    dec cl
    mov [rbx], cl
    inc rbx
    mov cl,[rbx]
    add cl, 8
    mov [rbx], cl
    cmp rcx, 0
    je AABCI
AABBI:
    inc rbx
    mov cl,[rbx]
    add cl, 4
    mov [rbx], cl
    dec rbx
    mov cl, [rbx]
    dec cl
    mov [rbx], cl
    cmp rcx, 0
    jne AABBI
AABCI:
    inc rbx
    call print
    sub rbx, 2
    mov cl, [rbx]
    cmp rcx, 0
    je AABEC
AABDF:
    mov cl, [rbx]
    dec cl
    mov [rbx], cl
    inc rbx
    mov cl, [rbx]
    inc cl
    mov [rbx], cl
    dec rbx
    mov cl, [rbx]
    cmp rcx, 0
    jne AABDF
AABEC:
    mov cl, [rbx]
    inc cl
    mov [rbx], cl
    inc rbx
    mov cl, [rbx]
    cmp rcx, 0
    je AABGG
AABEH:
    mov cl, [rbx]
    dec cl
    mov [rbx], cl
    inc rbx
    mov cl,[rbx]
    add cl, 10
    mov [rbx], cl
    sub rbx, 2
    mov cl, [rbx]
    inc cl
    mov [rbx], cl
    inc rbx
    mov cl, [rbx]
    cmp rcx, 0
    jne AABEH
AABGG:
    inc rbx
    call print
    mov cl, [rbx]
    cmp rcx, 0
    je AABHF
AABHB:
    mov cl, [rbx]
    dec cl
    mov [rbx], cl
    cmp rcx, 0
    jne AABHB
AABHF:
    inc rbx
    mov cl, [rbx]
    cmp rcx, 0
    jne AABAF
AABHJ:
    mov cl, [rbx]
    cmp rcx, 0
    jne AABAC
AABIC:
    mov cl, [rbx]
    inc cl
    mov [rbx], cl
    sub rbx, 3
    mov cl, [rbx]
    cmp rcx, 0
    je AACEI
AABIJ:
    mov cl, [rbx]
    dec cl
    mov [rbx], cl
    cmp rcx, 0
    je AACAA
AABJD:
    mov cl, [rbx]
    dec cl
    mov [rbx], cl
    inc rbx
    mov cl, [rbx]
    inc cl
    mov [rbx], cl
    dec rbx
    mov cl, [rbx]
    cmp rcx, 0
    jne AABJD
AACAA:
    mov cl, [rbx]
    inc cl
    mov [rbx], cl
    inc rbx
    mov cl, [rbx]
    cmp rcx, 0
    je AACEB
AACAF:
    mov cl, [rbx]
    dec cl
    mov [rbx], cl
    dec rbx
    mov cl, [rbx]
    inc cl
    mov [rbx], cl
    add rbx, 3
    mov cl, [rbx]
    dec cl
    mov [rbx], cl
    cmp rcx, 0
    je AACCC
AACBF:
    mov cl, [rbx]
    dec cl
    mov [rbx], cl
    inc rbx
    mov cl, [rbx]
    inc cl
    mov [rbx], cl
    dec rbx
    mov cl, [rbx]
    cmp rcx, 0
    jne AACBF
AACCC:
    mov cl,[rbx]
    add cl, 2
    mov [rbx], cl
    inc rbx
    mov cl, [rbx]
    cmp rcx, 0
    je AACDF
AACCI:
    mov cl, [rbx]
    dec cl
    mov [rbx], cl
    dec rbx
    mov cl, [rbx]
    dec cl
    mov [rbx], cl
    inc rbx
    mov cl, [rbx]
    cmp rcx, 0
    jne AACCI
AACDF:
    sub rbx, 3
    mov cl, [rbx]
    cmp rcx, 0
    jne AACAF
AACEB:
    sub rbx, 4
    mov cl, [rbx]
    cmp rcx, 0
    jne AABIJ
AACEI:
    mov cl,[rbx]
    add cl, 10
    mov [rbx], cl
    call print
    mov cl,[rbx]
    add cl, 3
    mov [rbx], cl
    call print
    mov cl, [rbx]
    cmp rcx, 0
    je AACHA
AACGG:
    mov cl, [rbx]
    dec cl
    mov [rbx], cl
    cmp rcx, 0
    jne AACGG
AACHA:
    dec rbx
    mov cl, [rbx]
    cmp rcx, 0
    jne AAAGJ
AACHE:
    mov cl,[rbx]
    add cl, 5
    mov [rbx], cl
    xor rdi, rdi
    mov rax, 60
    syscall
scan:
    xor rax, rax
    xor rdi, rdi
    mov rsi, tempbuff
    mov rdx, 0x1
    syscall

    mov rdx, tempbuff
    mov rcx, [rdx]
    cmp rcx, 0xa
    je scan
    mov[rbx], rcx
    xor rcx, rcx
    ret

print:
    mov rax, 0x1
    mov rdi, 0x1
    mov rsi, rbx
    mov rdx, 0x1
    syscall
    xor rcx, rcx
    ret

section .data
    buff db 30000 dup(0)

section .bss
    tempbuff resb 0x0
