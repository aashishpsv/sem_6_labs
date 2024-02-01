class q3:
    x=0
    n=0

    def __init__(self,x,h):
        self.x=x
        self.n=n
    def solve(self):
        i=1
        result=1
        while(i<=self.n):
            result = result*self.x
            i+=1
        return result

x=int(input("enter no x:"))
n=int(input("enter number n:"))
q = q3(x,n)
print("pow(x,n) =",q.solve())
