#include <algorithm>
#include <iostream>
#include <fstream>
#include <chrono>

#include "ArrayGenerator.h"

using checker = int64_t (*)(int*, const int, const UniformRandomInt32&);

void mergeSort(int* arr, int left, int right);
void merge(int* arr, int left, int mid, int right);

void calcSort(checker checker, const char* file);
int64_t timeSort(int* arr, const int N);

int64_t checkSort_Random(int* arr, const int N, const UniformRandomInt32& rand);
int64_t checkSort_Sorted(int* arr, const int N, const UniformRandomInt32& rand);
int64_t checkSort_AlmostSorted(int* arr, const int N, const UniformRandomInt32& rand);

const int N = 10'000, K = 10;

int main() {
  calcSort(checkSort_Random,       "../b/MergeSort/data1.txt");
  calcSort(checkSort_Sorted,       "../b/MergeSort/data2.txt");
  calcSort(checkSort_AlmostSorted, "../b/MergeSort/data3.txt");

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
  mergeSort(arr, 0, N - 1);
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

void mergeSort(int* arr, int left, int right) {
  if (left >= right) return;

  int mid = left + (right - left) / 2;
  mergeSort(arr, left, mid);
  mergeSort(arr, mid + 1, right);
  merge(arr, left, mid, right);
}

void merge(int* arr, int left, int mid, int right) {
  int n1 = mid - left + 1;
  int n2 = right - mid;

  int* L = new int[n1];
  int* R = new int[n2];

  for (int i = 0; i < n1; i++) L[i] = arr[left + i];
  for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

  int i = 0, j = 0, k = left;

  while (i < n1 && j < n2) {
    if (L[i] >= R[j]) arr[k++] = L[i++];
    else arr[k++] = R[j++];
  }
  
  while (i < n1) arr[k++] = L[i++];
  while (j < n2) arr[k++] = R[j++];

  delete[] L;
  delete[] R;
}
