#!/usr/bin/python3
from pip import main



from random import random
M = 20


def randomFloat(min, max):
     return min + (random() * (max - min))




if __name__ == '__main__':
    print("static float __attribute__((annotate(\"scalar(range(1, 100) final)\"))) arr[] = {")
    for i in range(M):
        s = str(randomFloat(1,100))
        s += ", " + str(randomFloat(1,100)) + ", "
        if i == M-1:
            s = s[:-2]
        print(s)
    
    print("};\n")
