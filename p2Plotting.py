import numpy as np
import matplotlib.pyplot as plt
import csv

'''
with open('times.csv', newline='') as f:
   reader = csv.reader(f)
   times = []
   for row in reader:
      times.append(float(row[0]))
   f.close()
    
times = np.array(times)
xvals = np.array([1,2,3,4,5,6,7,8,9,10])
plt.plot(xvals, times, "red")
plt.title("Solve Times for 1-10 Threads for Length of f(x)")
plt.xlabel("Number of Threads")
plt.ylabel("Solve Speed in Seconds")
plt.show()
'''

with open('errors.csv', newline='') as f:
   reader = csv.reader(f)
   errors = []
   for row in reader:
      errors.append(float(row[0]))
   f.close()
    
errors = np.array(errors)
newxvals = np.array([10, 100, 1000, 10000, 100000, 1000000])
plt.semilogx(newxvals, errors, "red")
plt.title("Numerical Error for Calculating the Length of f(x)")
plt.xlabel("Number of Partition Points")
plt.ylabel("Numerical Error")
plt.show()