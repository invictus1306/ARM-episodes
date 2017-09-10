
.text
.global _start
_start:
  @ execve("/bin/sh",["/bin/sh", 0], 0)
 
  mov r0, pc
  add r0, #32
  sub r2, r2, r2
  push {r0, r2}
  mov r1, sp
  mov r7, #11
  swi #0
_exit:
  mov r0, #0
  mov r7, #1
  swi #0 @ exit
shell: .asciz "/bin/sh"
