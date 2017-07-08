auto i, res;
auto arr1=0x10988;

for (i=0;i<4;i++) 
{ 
   res = Byte(arr1)+0x40;
   print(res);
   arr1=arr1+1;
}
