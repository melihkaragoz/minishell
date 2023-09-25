import os, sys
a = ""
try:
	a = sys.argv[1]
except:
	a = input (">> ")
os.system(f"git commit -am {a}")
os.system("git push")
