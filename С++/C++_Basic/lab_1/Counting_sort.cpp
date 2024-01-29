#include <iostream>
#include <vector>
#include <algorithm>

void count_sort(std::vector<int>& arr) {
    int n = arr.size();
    int max_elem = *std::max_element(arr.begin(), arr.end());
    std::vector<int> count(max_elem + 1, 0);

    for (int i = 0; i < n; i++) {
        count[arr[i]]++;
    }

    for (int i = 1; i <= max_elem; i++) {
        count[i] += count[i - 1];
    }

    std::vector<int> output(n);
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

int main() {
    std::vector<int> arr = {5, 3, 8, 4, 2};
    count_sort(arr);
    std::cout << "Сортированный массив: ";
    for (int i = 0; i < arr.size(); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";

    return 0;
}
