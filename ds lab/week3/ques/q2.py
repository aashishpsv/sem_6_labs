import numpy as np
a = np.arange(9).reshape(3,3)
print(a)
print(a.sum(axis=0))# sum of each column
print(a.sum(axis=1)) #sum of each row