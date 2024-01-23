import numpy as np
a = np.array([[1.,2.5,3],[4,5.2,6]])
print(a,a.dtype)

b=np.array([(1,2,3),(4,5,6)])
print(b)

z = np.zeros((3,4))
print(z)
print(b.T)

d = np.arange(0,20,5)
print(d)

e = np.ones((3,4)).reshape((2,2,3))
print(e)