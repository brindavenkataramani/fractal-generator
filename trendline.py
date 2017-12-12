from matplotlib import pyplot as plt
import matplotlib

f = open("dimension.dat","r")
r, ry, t, r2, s = [], [], [], [], []

for l in f:
    row = l.split()
    r.append(row[0])
    ry.append(row[1])
    t.append(row[2])
    r2.append(row[3])
    s.append(row[4])

fig, ax = plt.subplots()

# Omit hashtags to plot dimension against radius.
# Otherwise, plots dimension against stickiness.

# plt.plot(r, ry, label = "r")
# plt.plot(r, r2, label = "r^2")
# plt.plot(r, t, label = "C(r)")
plt.plot(s, t, label = "C(r)")
legend = ax.legend(loc='upper left', shadow=True)
plt.show()
