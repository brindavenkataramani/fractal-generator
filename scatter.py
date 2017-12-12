from matplotlib import pyplot as plt
import matplotlib

f = open("coords.dat","r")
x, y = [], []

for l in f:
    row = l.split()
    x.append(row[0])
    y.append(row[1])

plt.xlim(0, 100)
plt.ylim(0, 100)
plt.gca().set_aspect('equal', adjustable='box')
plt.scatter(x, y)
plt.show()
