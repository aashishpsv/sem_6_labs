print("q1")
num = float(input('give no:'))
if num>0:
	print('+ no')
elif num==0:
	print('0')
else:
	print('- number')

print("q2")
x=float(input('Enter a number:'))
if x<10:
   print('smaller')
if x>20:
   print('bigger')
print('Finished')

print("q3")
x=5
print('befor 5')
if x==5:
	print('this is 5')
	print('still 5')
print('after 5')
print('bfore 6')
if x==6:
	print('this is 6')
print('after 6')

print("q4")
x=float(input("enter no:"))
if x<20:
	print('below 20')
elif x<10:
	print('below 10')
else:
	print('something else')

print("q5")
x=42
if x>1:
	print('above 1')
	if x<100:
		print('below 100')
print('done')


print("q6")
age = 15
b = ('kid' if age<18 else 'adult')
print(b)
