#include <algorithm>
#include <iostream>
#include <vector>

// Common sorting algorithms implemented in C++.

std::vector<int> bubble_sort(const std::vector<int> &data) {
    std::vector<int> arr = data;
    for (size_t i = 0; i < arr.size(); ++i) {
        for (size_t j = 0; j + 1 < arr.size() - i; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
    return arr;
}

std::vector<int> selection_sort(const std::vector<int> &data) {
    std::vector<int> arr = data;
    for (size_t i = 0; i < arr.size(); ++i) {
        size_t min_idx = i;
        for (size_t j = i + 1; j < arr.size(); ++j) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        std::swap(arr[i], arr[min_idx]);
    }
    return arr;
}

std::vector<int> insertion_sort(const std::vector<int> &data) {
    std::vector<int> arr = data;
    for (size_t i = 1; i < arr.size(); ++i) {
        int key = arr[i];
        size_t j = i;
        while (j > 0 && arr[j - 1] > key) {
            arr[j] = arr[j - 1];
            --j;
        }
        arr[j] = key;
    }
    return arr;
}

static std::vector<int> merge(const std::vector<int> &left, const std::vector<int> &right) {
    std::vector<int> merged;
    merged.reserve(left.size() + right.size());
    size_t i = 0, j = 0;
    while (i < left.size() && j < right.size()) {
        if (left[i] <= right[j]) {
            merged.push_back(left[i++]);
        } else {
            merged.push_back(right[j++]);
        }
    }
    while (i < left.size()) {
        merged.push_back(left[i++]);
    }
    while (j < right.size()) {
        merged.push_back(right[j++]);
    }
    return merged;
}

std::vector<int> merge_sort(const std::vector<int> &data) {
    if (data.size() <= 1) {
        return data;
    }
    size_t mid = data.size() / 2;
    std::vector<int> left(data.begin(), data.begin() + mid);
    std::vector<int> right(data.begin() + mid, data.end());
    return merge(merge_sort(left), merge_sort(right));
}

static int partition(std::vector<int> &arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

static void quick_sort_rec(std::vector<int> &arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort_rec(arr, low, pi - 1);
        quick_sort_rec(arr, pi + 1, high);
    }
}

std::vector<int> quick_sort(const std::vector<int> &data) {
    std::vector<int> arr = data;
    quick_sort_rec(arr, 0, static_cast<int>(arr.size()) - 1);
    return arr;
}

template <typename Container>
void print_array(const Container &arr) {
    std::cout << "[";
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << arr[i];
        if (i + 1 < arr.size()) {
            std::cout << ", ";
        }
    }
    std::cout << "]\n";
}

int main() {
    std::vector<int> data = {64, 34, 25, 12, 22, 11, 90};

    std::cout << "Original: ";
    print_array(data);

    std::cout << "Bubble:   ";
    print_array(bubble_sort(data));

    std::cout << "Selection:";
    print_array(selection_sort(data));

    std::cout << "Insertion:";
    print_array(insertion_sort(data));

    std::cout << "Merge:    ";
    print_array(merge_sort(data));

    std::cout << "Quick:    ";
    print_array(quick_sort(data));

    return 0;
}
