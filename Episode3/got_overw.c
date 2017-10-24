#include <stdio.h>
#include <math.h>

#define MAX 12
#define PI 3.14159265

int main()
{
  static int arr[MAX];
  char ch;
  int num, ret;
  int flag=1;
  unsigned int i, in_num, out_num, cos_param, write_index;

  printf("Please fill the array:\n");

  for(i=0;i<MAX;i++){
    if(scanf("%d", &in_num)==1){
      arr[i]=in_num;
    }
    else{
      printf("Please enter a number\n");
      return 0;
    }
  }

  while(flag){
    printf("Select the index of the element that you want to read: \n");
    
    if(scanf("%d", &num)!=1){
      printf("Please enter a number\n");
      return 0;
    }

    printf("At position %d the value is %d\n", num, arr[num]);
    
    printf("Do you want read another number? [y/n]\n");

    scanf(" %c", &ch);

    if(ch!='y'){
      flag=0;
    }
  }

  printf("How many value do you want to modify?\n");

  if(scanf("%d", &cos_param)!=1){
      printf("Please enter a number:\n");
      return 0;
  }
  //param 180
  ret = cos(cos_param * PI /180.0);

  if (ret<0){
  	write_index = MAX;
  }
  else
  {
  	write_index = 1;
  }

  while(write_index){
    if(flag!=0){
      printf("Do you want to edit some value in the array? [y/n]\n");
      scanf(" %c", &ch);
    }

    if(ch=='y' || flag==0){
      printf("Select the index of the element that you want to modify\n");
      scanf("%d", &num);
      
      printf("Enter the new value\n");
      scanf("%d", &out_num);

      arr[num]=out_num;
      write_index--;
      flag=1;
    }
    else{
      break;
    }
  }
  printf("Good done!\n");
  return 0;
 }
