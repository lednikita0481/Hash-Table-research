section .text

global Asm_Hash_Polynom

Asm_Hash_Polynom: ;rdi - pointer to Word

    push rdi
    push rsi
    push rbx
    push rcx
    push r8
    push r9
    push r10

    mov rsi, [rdi]
    mov rbx, 0
    mov bl, byte [rsi]    ;first letter in rbx
    inc rsi

    mov rcx, qword [rdi+8]    ;strlen in rcx
    ;dec rcx


    mov r9, 31            ; k
    mov r8, 1             ; pow k

    mov r10, 0            ; hash

    cmp rcx, 1
    jb .no_need

    xor rdx, rdx
  .zaloopa:
    mov rax, r8
    imul ebx               ; edx:eax = s[i] * kur_pow_k
    rol rdx, 32
    add rax, rdx          ; rax = s[i] * kur_pow_k
    xor rdx, rdx
    
    add r10, rax          ; hash = hash + (s[i]*pow_k)
    xor rax, rax
    
    mov rax, r8
    mov rbx, r9
    imul ebx               ; rax = next pow_k
    xor rdx, rdx
    mov r8, rax           ; r8 = next pow_k

    xor rbx, rbx
    mov bl, byte [rsi]
    inc rsi

    loop .zaloopa

  .no_need:
    mov rax, r10

    pop r10
    pop r9
    pop r8
    pop rcx 
    pop rbx
    pop rsi
    pop rdi
    ret

