class q2:
    array=[]
    target=0

    def __init__(self,array,target):
        self.array=array
        self.target=target
    def solve(self):
        tar = self.target
        for i in range(len(self.array)-1):
            j=i+1
            while(j<len(self.array)):
                if(self.array[i]+self.array[j] ==tar):
                    return i,j
                j=i+1
        return "no soln exist"
    

size = int(input('size?'))
i=0
array=[]
print("enter ele:")
for i in range(size):
    array.append(int(input()))
target = int(input('enter no to find:'))
q = q2(array,target)
print(q.solve())
                     

