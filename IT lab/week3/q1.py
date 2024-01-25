#calculator
def add(x,y):
    return x+y
def sub(x,y):
    return x-y
def multiply(x,y):
    return x*y
def divide(x,y):
    return x/y
operation =int(input("enter 1.add 2.subtract 3.mutiply 4.divide"))
x=int(input("enter 1st number"))
y = int(input("enter 2nd number"))
if operation == 1:
    print(x,"+",y,"=",add(x,y))
elif operation == 2:
    print(x,"-",y,"=",sub(x,y))
elif operation == 3:
    print(x,"*",y,"=",multiply(x,y))
elif operation == 4:
    print(x,"/",y,"=",divide(x,y))
else:
    print("invalid input")