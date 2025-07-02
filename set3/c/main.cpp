#include "math.h"

#include <iostream>

void introSort(int* arr, int n);
void quickSort(int* arr, int left, int right, int health);
void heapify(int* arr, int n, int i);
void heapSort(int* arr, int n);
void insertionSort(int* arr, int left, int right);

int main() {
  int n;
  std::cin >> n;

  int* arr = new int[n];
  for (int i = 0; i < n; i++) std::cin >> arr[i];
  
  introSort(arr, n);
  for (int i = 0; i < n; i++) std::cout << arr[i] << ' ';

  delete[] arr;
  return 0;
}

void introSort(int* arr, int n) {
  int depth = ceil(2 * log2(n));
  quickSort(arr, 0, n - 1, depth);
}

void quickSort(int* arr, int left, int right, int health) {
  if (right - left <= 16) {
    insertionSort(arr, left, right);
    return;
  }
  
  if (!health) {
    heapSort(arr + left, right - left + 1);
    return;
  }

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

  quickSort(arr, left, j, health - 1);
  quickSort(arr, i, right, health - 1);
}

void heapify(int* arr, int n, int i) {
  int largest = i;
  int l = 2 * i + 1;
  int r = 2 * i + 2;

  if (l < n && arr[l] > arr[largest]) largest = l;
  if (r < n && arr[r] > arr[largest]) largest = r;

  if (largest != i) {
    std::swap(arr[i], arr[largest]);
    heapify(arr, n, largest);
  }
}
 
void heapSort(int* arr, int n) {
  if (n <= 1) return;

  for (int i = n / 2 - 1; i >= 0; i--)
    heapify(arr, n, i);

  for (int i = n - 1; i >= 0; i--) {
    std::swap(arr[0], arr[i]);
    heapify(arr, i, 0);
  }
}

void insertionSort(int* arr, int left, int right) {
  if (right <= left) return;

  for (int i = left + 1; i <= right; ++i) {
    int key = arr[i];
    int j = i - 1;

    while (j >= left && arr[j] > key) {
      arr[j + 1] = arr[j];
      --j;
    }
    arr[j + 1] = key;
  }
}
