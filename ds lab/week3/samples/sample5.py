import numpy as np
print("matrix operations")
a = np.array([[1,1],[0,1]])
b = np.array([[2,0],[3,4]])
print(a*b)
print(a.dot(b))
print(np.dot(a,b))
b = np.arange(12).reshape(3,4)
print(b.sum(axis=0))
print(b.sum(axis=1))