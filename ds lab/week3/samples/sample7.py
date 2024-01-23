import numpy as np
print("Indexing, Slicing & Iterating Array")
a1 = np.array([(3,4,5),(12,6,1)])
a2 = np.array([(1,2,6),(-4,3,8)])
d1 = np.vstack((a1,a2))
print(d1)
d2 = np.hstack((a1,a2))
print(d2)

print("---------")

a = np.array([4.,2.])
b = np.array([3.,8.])
print(np.column_stack((a,b)))
print(np.hstack((a,b)))
print(np.hstack((a[:2],b[:2])))