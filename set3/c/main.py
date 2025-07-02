import matplotlib.pyplot as plt

def readData(file):
    f = open(file, "r")
    lines = [x.split(' ') for x in f.read().split('\n') if len(x) != 0]
    # lines=lines[50:] # skip first 50 lines.
    return [int(a[0]) for a in lines], [float(a[1]) for a in lines]

x1, y1 = readData("QuickSort/data1.txt")
x2, y2 = readData("QuickSort/data2.txt")
x3, y3 = readData("QuickSort/data3.txt")

plt.figure(figsize=(12, 7))

plt.plot(x1, y1, label='случайный массив', color='red')
plt.plot(x2, y2, label='отсортированный массив', color='green')
plt.plot(x3, y3, label='почти отсортированный массив', color='blue')

plt.title("Время работы алгоритма Quick Sort")
plt.xlabel("Размер массива N")
plt.ylabel("микро секунды")
# plt.xticks([x1 for x1 in range(0, 10001, 500)])
plt.legend()
plt.grid(True)
plt.show();

