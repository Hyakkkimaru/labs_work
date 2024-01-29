#include <iostream>
#include <vector>

void selection_sort(std::vector<int> &arr) {
  int n = arr.size();

  for (int i = 0; i < n - 1; i++) {
    int min_index = i;

    for (int j = i + 1; j < n; j++) {
      if (arr[j] < arr[min_index]) {
        min_index = j;
      }
    }

    if (min_index != i) {
      int temp = arr[i];
      arr[i] = arr[min_index];
      arr[min_index] = temp;
    }
  }
}

int main() {
  std::vector<int> arr = {10, 3, 5, 4, 1};

  selection_sort(arr);

  std::cout << "Сортированный массив: ";
  for (int i = 0; i < arr.size(); i++) {
    std::cout << arr[i] << " ";
  }
  return 0;
}
