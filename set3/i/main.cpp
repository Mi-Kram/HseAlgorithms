#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

// Функция для подсчёта количества конфликтов между ферзями
int countConflicts(const vector<int>& positions, int n) {
  int conflicts = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      if (positions[i] == positions[j] || abs(positions[i] - positions[j]) == j - i) {
        ++conflicts;
        break;
      }
    }
  }
  return conflicts;
}

void simulatedAnnealing(int n, vector<int>& result) {
  // Инициализация
  vector<int> positions(n);
  for (int i = 0; i < n; ++i)
    positions[i] = i;
  random_shuffle(positions.begin(), positions.end());

  int currentConflicts = countConflicts(positions, n);
  double temperature = 1.0;
  double coolingRate = 0.9995;

  while (temperature > 1e-8) {
    // Случайная перестановка двух ферзей
    vector<int> newPositions = positions;
    int x = rand() % n, y = rand() % n;
    swap(newPositions[x], newPositions[y]);

    int newConflicts = countConflicts(newPositions, n);

    // Разница в "энергии"
    int delta = newConflicts - currentConflicts;

    // Принимаем новое состояние с вероятностью, зависящей от температуры
    if (delta < 0 || exp(-delta / temperature) > (double)rand() / RAND_MAX) {
      positions = newPositions;
      currentConflicts = newConflicts;
    }

    // Уменьшаем температуру
    temperature *= coolingRate;

    // Если нашли решение без конфликтов, завершаем
    if (currentConflicts == 0)
      break;
  }

  result = positions;
}

int main() {
  srand(time(0));
  
  int n;
  cin >> n;

  vector<int> result;
  simulatedAnnealing(n, result);

  for (int i = 0; i < n; ++i) {
    cout << result[i] + 1 << " ";  // Переводим к 1-индексации
  }
  cout << endl;

  return 0;
}
