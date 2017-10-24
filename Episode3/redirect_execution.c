#include <stdio.h>
#include <string.h>

char msgSecret[] = "This is the secret message";
char msgDefault[] = "This is the default message";

typedef struct _msg_struct
{
  char message[32];
  int (*print_msg)();
}msg_struct;

int print_secr()
{
  printf("Congrats! %s\n", msgSecret);
  return 0;
}

int print_default()
{
  printf("Hello! %s\n", msgDefault);
  return 0;
}

int main(int argc, char **argv)
{
  char message[80];
  msg_struct p;
  
  printf("Please enter a message: \n"); 
 
  gets(message);

  if(*message)
  {
    p.print_msg=print_default; 
    strcpy(p.message, message);
    p.print_msg();
  }
  else
  {
    printf("Insert the message!\n");
  }

  return 0;
}

