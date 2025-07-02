#include <iostream>
#include <random>

std::mt19937 rnd(234);

int n, m, c;
int cnt[10][10][3];
int a[10][10];

int calc() {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      cnt[i][j][0] = cnt[i][j][1] = cnt[i][j][2] = 0;
    }
  }
  
  int sum = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      for (int k = j + 1; k < m; k++) {
        if (a[i][j] == a[i][k]) {
          sum += cnt[j][k][a[i][j]];
          cnt[j][k][a[i][j]]++;
        }
      }
    }
  }
  return sum;
};

int main() {
  std::cin >> n >> m >> c;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      a[i][j] = rnd() % c;
    }
  }

  while (true) {
    int data = calc();
    for (int it = 0; it < n * m; it++) {
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
          int store = a[i][j];
          a[i][j] = rnd() % c;
          int newData = calc();

          if (newData < data) data = newData;
          else if (newData > data) a[i][j] = store;
        }
      }
    }

    if (!data) break;

    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++) a[i][j] = rnd() % c;
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      std::cout << a[i][j] + 1 << ' ';
    }
    std::cout << '\n';
  }

  return 0;
}
