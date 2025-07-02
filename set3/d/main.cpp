#include <iostream>

void buildMaxHeap(int* arr, int n);
void heapify(int* arr, int n, int i);
void heapSort(int* arr, int n);
void insertionSort(int* arr, int left, int right);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  int* arr = new int[n];
  for (int i = 0; i < n; i++)
    std::cin >> arr[i];
  
  heapSort(arr, n);
  for (int i = 0; i < n; i++)
    std::cout << arr[i] << ' ';
  
  delete[] arr;
  return 0;
}

// void heapify(int* arr, int n, int i) {
//   int largest = i;
//   int left = 2 * i + 1;
//   int right = 2 * i + 2;

//   if (left < n && arr[left] > arr[largest]) largest = left;
//   if (right < n && arr[right] > arr[largest]) largest = right;

//   if (largest != i) {
//     std::swap(arr[i], arr[largest]);
//     heapify(arr, n, largest);
//   }
// }

void heapify(int* arr, int n, int i) {
  int largest, left, right;

  while (true) {
    largest = i;
    left = 2 * i + 1;
    right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;

    if (largest == i) break;
    std::swap(arr[i], arr[largest]);
    i = largest;
  }
}

void buildMaxHeap(int* arr, int n) {
  for (int i = n / 2 - 1; i >= 0; i--) {
    heapify(arr, n, i);
  }
}

void heapSort(int* arr, int n) {
  buildMaxHeap(arr, n);

  // if (n <= 30) {
  //   insertionSort(arr, 0, n - 1);
  //   return;
  // }

  for (int i = n - 1; i >= 1; i--) {
    std::swap(arr[0], arr[i]);
    heapify(arr, i, 0);
  }
}

void insertionSort(int* arr, int left, int right) {
  for (int i = left + 1; i <= right; i++) {
    int key = arr[i];
    int j = i - 1;

    while (j >= left && arr[j] > key) {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = key;
  }
}