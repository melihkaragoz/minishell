import os
import sys
a = sys.argv[1]
os.system("git add -A")
os.system(f"git commit -m {a}")
os.system("git push")
