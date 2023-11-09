#!/usr/bin/python3
from pip import main



from random import random
M = 20


def randomFloat(min, max):
     return min + (random() * (max - min))



if __name__ == '__main__':
    print("static float __attribute__((annotate(\"scalar(range(-100,20000) final)\"))) arr[] = {")
    for i in range(M):
        s = str(randomFloat(-100,100))
        s += ", " + str(randomFloat(20,20000))
        s += ", " + str(randomFloat(-30,50)) + ", "
        if i == M-1:
            s = s[:-2]
        print(s)
    
    print("};\n")
