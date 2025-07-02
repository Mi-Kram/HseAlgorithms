#include <iostream>

void mergeInsertionSort(int* arr, int left, int right);
void merge(int* arr, int left, int mid, int right);
void insertionSort(int* arr, int left, int right);

int main() {
  size_t n;
  std::cin >> n;
  
  int* arr = new int[n];
  for (size_t i = 0; i < n; i++)
    std::cin >> arr[i];
  
  mergeInsertionSort(arr, 0, n - 1);
  for (size_t i = 0; i < n; i++) std::cout << arr[i] << ' ';

  delete[] arr;
  return 0;
}

void mergeInsertionSort(int* arr, int left, int right) {
  if (right - left <= 15) {
    insertionSort(arr, left, right);
    return;
  }

  int mid = left + (right - left) / 2;
  mergeInsertionSort(arr, left, mid);
  mergeInsertionSort(arr, mid + 1, right);
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
    if (L[i] <= R[j]) arr[k++] = L[i++];
    else arr[k++] = R[j++];
  }
  
  while (i < n1) arr[k++] = L[i++];
  while (j < n2) arr[k++] = R[j++];

  delete[] L;
  delete[] R;
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