import re, sys
f1 = open("lowercase.hpp", "w")
c = re.compile('^( *{ \\w+, ")([^"]+)(" *},)')

with open("temp.txt", 'r', encoding='UTF-8') as f0:
  while line := f0.readline():
    line = line.rstrip()
    # print(f" • converting {line}")
    o = c.search(line)
    if o == None:
      print(f"{line}: wrong format!")
    else:
      f1.write(f"{o[1]}{o[2].lower()}{o[3]}\n")
f0.close()
f1.close()
