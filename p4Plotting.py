import numpy as np
import matplotlib.pyplot as plt
import csv

with open('p4times.csv', newline='') as f:
   reader = csv.reader(f)
   times = []
   for row in reader:
      times.append(float(row[0]))
   f.close()
    
times_array = np.array(times)
xvals = np.arange(2, 41, 1)
plt.plot(xvals, times_array, "red")
plt.title("MPI Bandwidth for myBroadcast")
plt.xlabel("Number of Processes")
plt.ylabel("Bandwidth (in bytes per second)")
plt.show()