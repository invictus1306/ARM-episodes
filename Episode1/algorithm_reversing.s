.data
.balign 4
  info: .asciz "Please enter your string: "
  format: .asciz "%5s"
.balign 4
  strIN: .skip 5
  strOUT: .skip 5
  val: .byte 0x5
  output: .asciz "your input: %s\n"
.text
.global main
.extern printf
.extern scanf
 
main:
  push {ip, lr}      @ push return address + dummy register
  ldr r0, =info      @ print the info
  bl printf
  ldr r0, =format    
  ldr r1, =strIN     
  bl scanf           
  @ parsing of the message
  ldr r5, =strOUT
  ldr r1, =strIN
  ldrb r2, [r1]
  ldrb r3, [r1,#1]
  eor r0, r2, r3
  str r0, [r5]
  ldrb r4, [r1,#2]
  eor r0, r4, r3
  str r0, [r5,#1]
  add r2, #0x5
  str r2, [r5,#2]
  ldrb r4, [r1,#3]
  eor r0, r3, r4
  str r0, [r5,#3]
  ldrb r2, [r1,#4]
  eor r0, r2, r4
  str r0, [r5,#4]
  @ print of the final string
  ldr r0, =strOUT    @ print num formatted by output string.
  bl printf
  pop {ip, pc}       @ pop return address into pc
