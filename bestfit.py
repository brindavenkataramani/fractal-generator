import numpy as np
import matplotlib.pyplot as plt

# Get values.

r, ry, t, r2, s = np.loadtxt("dimension.dat", usecols=(0,1,2,3,4), delimiter =" ", unpack = True)
fig, ax = plt.subplots()

# Comment out first three for stickiness plots.
# Comment last line for fractal dimension plots.

# plt.scatter(r, ry)
# plt.scatter(r, t)
# plt.scatter(r, r2)
plt.scatter(s, t)

# Comment out first line for C(r) versus r graphs.
# Comment out second line for stickiness versus C(r) graphs.

plt.plot(np.unique(s), np.poly1d(np.polyfit(s, t, 1))(np.unique(s)), label= "C(r)")
# plt.plot(np.unique(r), np.poly1d(np.polyfit(r, ry, 1))(np.unique(r)), label = "r")
# plt.plot(np.unique(r), np.poly1d(np.polyfit(r, t, 1))(np.unique(r)), label = "C(r)")
# plt.plot(np.unique(r), np.poly1d(np.polyfit(r, r2, 1))(np.unique(r)), label = "r^2")
legend = ax.legend(loc='upper left', shadow=True)

plt.show()
