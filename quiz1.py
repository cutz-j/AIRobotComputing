import numpy as np
import os
os.chdir("d:/lecture/AIrobotComputing")

## Q1 ##
for i in range(1, 10):
    for j in range(1, 10):
        print("%d x %d = %d\t" %(i, j, i*j))
    print()
    
## Q2 ##
txt = open("python_pros_and_cons.txt", "r").readlines()[0]

# q2 - 1: direct programming #
txt_arr = txt.split(" ")

a = 0
b = 0

for word in txt_arr:
    if word == "language":
        a += 1
    if word == "Python":
        b += 1
print(txt[a:b])

# q2 - 2: count #
a = txt.count("language")
b = txt.count("Python")
print(txt[a:b])



