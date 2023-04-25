section .text

global CRC32asm

CRC32asm:
  push rsi

  mov rsi, [rdi]

  xor rax, rax
  crc32 rax, qword [rsi + 0x00]
  crc32 rax, qword [rsi + 0x08]
  crc32 rax, qword [rsi + 0x10]
  ;crc32 rax, qword [rsi + 0x18]

  pop rsi
  ret