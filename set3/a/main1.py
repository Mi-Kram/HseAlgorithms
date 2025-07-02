import matplotlib.pyplot as plt
import math

f = open("data.txt", "r")
lines = [x.split(' ') for x in f.read().split('\n') if len(x) != 0]
# lines=lines[50:] # skip first 50 lines.

x = [int(a[0]) for a in lines]
y = [float(a[1]) for a in lines]

y0 = 0.25*math.pi + 1.25*math.asin(0.8) - 1

plt.figure(figsize=(12, 7))
plt.plot(x, y, 'o-r', label='calculating', color='blue')
plt.plot([x[0]-5000, x[-1]+5000], [y0, y0], label='square', color='green')
plt.legend()
plt.grid(True)
plt.show();
