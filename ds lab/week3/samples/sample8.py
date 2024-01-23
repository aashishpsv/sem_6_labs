import numpy as np
a = np.arange(12)**2
print(a)
i=np.array([1,1,3,8,5])
print(a[i])
j=np.array([[3,4],[9,7]])
print(a[j])
print("----------")
a=np.array([(3,2,9),(1,6,7)])
s1=0
for row in a:
    for col in row:
        s1+=col
print(s1)
print("----------")
a=np.array([(3,2,9),(1,6,7)])
s=0
for i in range(a.shape[0]):
    for j in range(a.shape[1]):
        s+=a[i,j]
print(s)