import pandas as pd
import numpy as np

s=pd.Series([3,9,-2,10,5])
print("sum",s.sum())
print("sum",s.min())
print("sum",s.max())

print("---------------------------------")
data = [['dinesh',10],['nithya',12],['raji',13]]
df = pd.DataFrame(data,columns=['name','age'])
print(df)
print("---------------------------------")

data = {'Name':['Kavitha', 'Sudha', 'Raju','Vignesh'],'Age':[28,34,29,42]}
df = pd.DataFrame(data,index=['rank1','rank2','rank3','rank4'])
print(df)
print("---------------------------------")

df=pd.DataFrame({'A':pd.Timestamp('20130102'),'B':np.array([3]*4,dtype='int32'),'C':pd.Categorical(['Male','Female','Male','Female'])})
print(df)
print(df.shape)
print(df.dtypes)
print(df.head())
print(df.tail())
print(df.describe())
print("---------------------------------")

dates = pd.date_range('20130101',periods=100)
df = pd.DataFrame(np.random.randn(100,4),index=dates,columns=list('ABCD'))
print(df.head())
print(df.tail())
print(df.index)
print(df.columns)
print(df.T)
print(df.sort_index(axis=1,ascending=False))
print(df.sort_values(by='B'))
print(df[0:3])
print(df['20130105':'20130110'])
print(df.iloc[0])
print(df.iloc[0,:2])
print(df.iloc[0,0])
print(df['A'])
print(df[['A','B']])
print(df[['A','B']][:5])
print(df.loc['20130101':'20130105',['A','B']][:5])

print("---------------------------------")

print(df[df.A>0])
#df['F']=['Male','Female','Female','Male','Female']
df.loc[:,'D']=np.array([5]*len(df))
print(df)
print("---------------------------------")

df.drop('A',axis=1,inplace=True)
print(df)
df.drop('2013-01-01',axis=0,inplace=True)
print(df)

print("---------------------------------")
#df1= [['dinesh',10],['nithya',12],['raji',13]]
#df1 = pd.DataFrame(data,columns=['name','age'])
#df2 = pd.date_range('20130101',periods=100)
#df2 = pd.DataFrame(np.random.randn(100,4),index=dates,columns=list('ABCD'))

#df_new = pd.concat([df1,df2])
#print(df_new.shape)
print("---------------------------------")


