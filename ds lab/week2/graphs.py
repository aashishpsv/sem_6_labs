import pandas as pd
import numpy as np
df=pd.read_csv('xyz.csv',header=None)
print(df.head())

print("---------------------------------")
print(df.tail())

print("---------------------------------")
df.columns=['preg','glu','bp','sft','ins','bmi','dpf','age','class']
print(df.head())
print(df.tail())
print("---------------------------------")

from matplotlib import pyplot as plt
#plt.scatter(df['bmi'],df['glu'])
#plt.xlabel('bmi')
#plt.ylabel('Glucose')
#plt.show()

#print("---------------------------------")
#plt.hist(df['preg'])
#plt.show()

#print("---------------------------------")
#plt.boxplot(df)
#plt.show()

print("---------------------------------")

w= pd.read_csv('wine_for_Week2.xls',header=None)
print(w.head())
#D = np.loadtxt('xyz.data',delimiter=",")
#print(D[:5,:])
G=pd.read_excel('German Credit_for_Week2.xlsx',sheet_name='Sheet1')
print(G.head())
B = pd.read_html('Test runs-1.html')
print(B)
H = pd.read_table('HR.txt')
print(H.head())

print('------------------------------------------')

f=H['Department'].value_counts()
print(f)
#f.plot(kind='bar')
#plt.show()
#f.plot(kind='pie')
#plt.show()
fa=pd.crosstab(H['Gender'],H['Attrition'])
fa.plot(kind='bar')
plt.show()



