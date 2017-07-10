num = 0x997-0x724
for c in range (0x20,0x7f):
  ref = c^0x69 | (c<<3)
  if (ref==num):
    print "The number is " + hex(c)
print "End!"
