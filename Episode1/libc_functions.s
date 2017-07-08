.data
  string: .asciz "Hello World!\n"
.text
.global main
.func main
main:
 stmfd sp!, {lr}   @ save lr
 ldr r0, =string   @ store string address into R0
 bl printf         @ call printf
 ldmfd sp!, {pc}   @ restore pc
_exit:
 mov lr, pc        @ exit
