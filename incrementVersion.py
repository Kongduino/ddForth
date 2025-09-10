import re, sys
file_object = open("myversion.hpp", "r")
line = file_object.readline()
file_object.close()

c = re.compile("#define myVERSION ([1-9][0-9]+)")
o = c.search(line)
if o == None:
  print(f"Invalid string: {line}")
  sys.exit()

n = int(o[1]) + 1
v = f"#define myVERSION {n}"
print(v)
file_object = open("myversion.hpp", "w")
file_object.write(v)
file_object.close()

