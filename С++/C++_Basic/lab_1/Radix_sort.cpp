#include <iostream>
#include <vector>
#include <algorithm>

void counting_sort(std::vector<int>& arr, int exp) {
    int n = arr.size();
    std::vector<int> output(n);
    std::vector<int> count(10, 0);

    for (int i = 0; i < n; i++) {
        count[(arr[i] / exp) % 10]++;
    }

    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

void radix_sort(std::vector<int>& arr) {
    int maxVal = *std::max_element(arr.begin(), arr.end());
    int exp = 1;

    while (maxVal / exp > 0) {
        counting_sort(arr, exp);
        exp *= 10;
    }
}

int main() {
    std::vector<int> arr = { 10, 3, 8, 4, 9};
    radix_sort(arr);
    std::cout << "Сортированный массив: ";
    for (int i = 0; i < arr.size(); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
