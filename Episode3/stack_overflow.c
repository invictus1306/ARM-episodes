#include <stdio.h>

void rop_func(){
  asm volatile(
    "pop {r0, r1, r2, lr} \n\t"
    "bx lr \n\t"
  );
}

void msg_func(){
  char message[64];
  read(0, message, 256);
}

int main(){
  msg_func();
  write(1, "Good done!\n",12);
  return 0;
}
