auto i, t;
auto start=0x200f1;
for (i=0;i<=0x5C;i=i+4) 
{ 
  t = Dword(start)^0x123456;
  PatchDword(start,t);
  start=start+4;
}
