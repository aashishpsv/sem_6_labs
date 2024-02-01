class q1:
    array=[]
    def __init__(self,array):
        self.array=array
    def solve(self):
        return self.subset([], sorted(self.array))
    def subset(self,current,sset):
        if sset:
            return self.subset(current, sset[1:]) + self.subset(current + [sset[0]], sset[1:])
        return [current]
    
size = int(input("enter size of array:"))
i=0
array=[]
print("enter array elements:")
for i in range(size):
    array.append(int(input()))
q = q1(array)
print(q.solve())