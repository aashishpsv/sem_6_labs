import numpy as np
a=np.arange(15).reshape(3,5)
print(a)#print
print(a.shape)#size
print(a.T)#tranpose
print("-----------")
c=np.arange(24).reshape(2,3,4)
print(c)
print(c.shape)
print("--")
print(c[1,:,:])
print("--")
print(c[:,:,2])