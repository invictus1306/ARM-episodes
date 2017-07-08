#include <stdio.h>
#include <string.h>
 
static char password[] = "compiler_options";
 
int main()
{
  char input_pwd[20]={0};
 
  fgets(input_pwd, sizeof(input_pwd), stdin);
 
  int size = sizeof(password);
 
  if(input_pwd[size] != 0)
  {
    printf("The password is not correct! \n");
    return 0;
  }
 
  int ret = strncmp(password, input_pwd, size-1);
 
  if (ret==0)
  {
    printf("Good done! \n");
  }
  else
  {
    printf("The password is not correct! \n");
  }
 
  return 0;
}
