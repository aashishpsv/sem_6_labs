import numpy as np

S = np.arange(10,30,5)
print(S)
Z = np.arange(0,2,0.3)
print(Z)
S1 = np.linspace(0,2,9)
print(S1)

print("-------------")
print("random no:")
import random

print(random.choice([1,2,3,4,5]))
print(random.choice('python'))
print(random.randrange(25,50))
print(random.randrange(25,50,2))
print(random.random())
print(random.uniform(5,10))
my_list=([1,2,3,4,5])
random.shuffle(my_list)
print(my_list)
random.seed(10)
print(random.random())