import numpy as np
import matplotlib.pyplot as plt
import csv

with open('readTimes.csv', newline='') as f:
    reader = csv.reader(f)
    read_times = []
    for row in reader:
        read_times.append(float(row[0]))
    f.close()
    
with open('writeTimes.csv', newline='') as f:
    reader = csv.reader(f)
    write_times = []
    for row in reader:
        write_times.append(float(row[0]))
    f.close()
    
read_times = np.array(read_times)
write_times = np.array(write_times)
xvals = np.array([32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384])
plt.semilogx(xvals, write_times, "red")
plt.semilogx(xvals, read_times, "blue")
plt.title("Write and Read Times")
plt.xlabel("Size of Matrix")
plt.ylabel("Speed in Bytes Per Second")
plt.show()