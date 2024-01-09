list=['abcd',786,2.23,'john',70.2000000000000003,123,'john']
tinylist=[123,'john']
print(list,list[0],list[1:3],list[2:],tinylist*2,list+tinylist)

list2 = ['phy','chem',1997,2000]
list2.append('math')
print(list2)
del list[2]
print(list2)
print('phy' in list2)
print('eng' in list2)
print(list2.count('phy'))
list2.pop()
print(list2)
list2.insert(2,'math')
print(list2)
list2.remove('chem')
print(list2)
list2.reverse()
print(list2)

