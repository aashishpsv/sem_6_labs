import numpy as np
import pandas as pd

dict = {"Name":["stu1","stu2","stu3"],"Height":["180","150","160"],"qualification":["btech","inter","phd"] }
df = pd.DataFrame(dict)
print(df)
addrs = ["add1","addr2","addr3"]

df['Address'] = addrs

print(df)