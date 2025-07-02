import matplotlib.pyplot as plt
import math

f = open("data.txt", "r")
lines = [x.split(' ') for x in f.read().split('\n') if len(x) != 0]
# lines = lines[50:] # skip first 50 lines.

y0 = 0.25*math.pi + 1.25*math.asin(0.8) - 1

x = [int(a[0]) for a in lines]
y = [float(a[1]) - y0 for a in lines]


plt.figure(figsize=(12, 7))
plt.plot(x, y, 'o-r', label='calculating', color='blue')
plt.plot([x[0]-5000, x[-1]+5000], [0, 0], label='square', color='black')
plt.legend()
plt.grid(True)
plt.show();
