// 292820176
#include "math.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <chrono>

#include "ArrayGenerator.h"

using checker = int64_t (*)(int*, const int, const UniformRandomInt32&);

void quickSort(int* arr, int left, int right);
void calcSort(checker checker, const char* file);
int64_t timeSort(int* arr, const int N);

int64_t checkSort_Random(int* arr, const int N, const UniformRandomInt32& rand);
int64_t checkSort_Sorted(int* arr, const int N, const UniformRandomInt32& rand);
int64_t checkSort_AlmostSorted(int* arr, const int N, const UniformRandomInt32& rand);

const int N = 10'000, K = 10;

int main() {
  calcSort(checkSort_Random,       "../c/QuickSort/data1.txt");
  calcSort(checkSort_Sorted,       "../c/QuickSort/data2.txt");
  calcSort(checkSort_AlmostSorted, "../c/QuickSort/data3.txt");

  return 0;
}

void calcSort(checker checker, const char* file) {
  int* arr = new int[N];
  UniformRandomInt32 rand(0, 6000);
  int64_t time;

  try {
    std::ofstream os(file);
    if (!os.is_open()) {
      std::cout << "Couldn't open " << file << '\n';
      return;
    }
    
    for (int i = 500; i <= 10'000; i += 100) {
      time = 0;
      for (int j = 0; j < K; j++) 
        time += checker(arr, i, rand);

      os << i << ' ' << (time/K) << '\n';
    }

    os.flush();
    os.close();
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }

  delete[] arr;
}

int64_t timeSort(int* arr, const int N) {
  auto start = std::chrono::high_resolution_clock::now();
  quickSort(arr, 0, N - 1);
  auto elapsed = std::chrono::high_resolution_clock::now() - start;

  return std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
}

int64_t checkSort_Random(int* arr, const int N, const UniformRandomInt32& rand) {
  for (int i = 0; i < N; i++) arr[i] = rand();
  return timeSort(arr, N);
}

int64_t checkSort_Sorted(int* arr, const int N, const UniformRandomInt32& rand) {
  for (int i = 0; i < N; i++) arr[i] = rand();
  std::sort(arr, arr + N, std::greater<int>());
  return timeSort(arr, N);
}

int64_t checkSort_AlmostSorted(int* arr, const int N, const UniformRandomInt32& rand) {
  for (int i = 0; i < N; i++) arr[i] = rand();
  std::sort(arr, arr + N, std::greater<int>());
  UniformRandomInt32 idx(0, N - 1);
  for (int i = N / 10; i >= 0; i--) std::swap(arr[idx()], arr[idx()]);
  return timeSort(arr, N);
}

void quickSort(int* arr, int left, int right) {
  if (right <= left) return;
  
  int i = left, j = right;
  int pivot = arr[(left + right) / 2];

  while (i <= j) {
    while (arr[i] < pivot) ++i;
    while (arr[j] > pivot) --j;

    if (i <= j) {
      std::swap(arr[i], arr[j]);
      ++i;
      --j;
    }
  };

  quickSort(arr, left, j);
  quickSort(arr, i, right);
}

