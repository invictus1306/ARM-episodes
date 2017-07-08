auto i, res;
auto arr2=0x1098C;

for (i=0;i<3;i++) 
{ 
   res = Byte(arr2)+0x20;
   print(res);
   arr2=arr2+1;
}
