import sys
import os


fileName = "big.bin"
if (len(sys.argv) > 1) :
  fileName = sys.argv[1]

os.system("echo 'ABC' > " + fileName);

for i in range(24) :
  os.system("cat " + fileName + " > .temp")
  os.system("cat .temp >> " + fileName)

os.system("rm -rf .temp")
