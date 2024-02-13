#for heart_disease_dataset.csv
import fileinput
for line in fileinput.input():
  data = line.strip().split(",")
  if len(data) == 14:
    print(data[0])
    age, sex, cp, trestbps, chol, fbs, restecg, thalach,exang, oldpeak, slope, ca, thal, target = data
    print ("{0}\t{1}".format(sex, chol))