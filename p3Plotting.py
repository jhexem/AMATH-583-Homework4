import numpy as np
import matplotlib.pyplot as plt
import csv


with open('p3times.csv', newline='') as f:
   reader = csv.reader(f)
   times = []
   for row in reader:
      times.append(float(row[0]))
   f.close()
    
times = np.array(times)
xvals = np.arange(1, 41, 1)
plt.plot(xvals, times[40:80], "red")
plt.title("Solve Times for 1-40 Processes for Length of f(x)")
plt.xlabel("Number of Processes")
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
'''