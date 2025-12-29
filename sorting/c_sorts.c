#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

/* Common sorting algorithms implemented in C. */

static void bubble_sort(const int *data, size_t len, int *out) {
    memcpy(out, data, len * sizeof(int));
    for (size_t i = 0; i < len; i++) {
        for (size_t j = 0; j + 1 < len - i; j++) {
            if (out[j] > out[j + 1]) {
                int tmp = out[j];
                out[j] = out[j + 1];
                out[j + 1] = tmp;
            }
        }
    }
}

static void selection_sort(const int *data, size_t len, int *out) {
    memcpy(out, data, len * sizeof(int));
    for (size_t i = 0; i < len; i++) {
        size_t min_idx = i;
        for (size_t j = i + 1; j < len; j++) {
            if (out[j] < out[min_idx]) {
                min_idx = j;
            }
        }
        int tmp = out[i];
        out[i] = out[min_idx];
        out[min_idx] = tmp;
    }
}

static void insertion_sort(const int *data, size_t len, int *out) {
    memcpy(out, data, len * sizeof(int));
    for (size_t i = 1; i < len; i++) {
        int key = out[i];
        ssize_t j = (ssize_t)i - 1;
        while (j >= 0 && out[j] > key) {
            out[j + 1] = out[j];
            j--;
        }
        out[j + 1] = key;
    }
}

static void merge(int *arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));
    if (!L || !R) {
        free(L);
        free(R);
        return;
    }
    memcpy(L, arr + l, n1 * sizeof(int));
    memcpy(R, arr + m + 1, n2 * sizeof(int));
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    while (i < n1) {
        arr[k++] = L[i++];
    }
    while (j < n2) {
        arr[k++] = R[j++];
    }
    free(L);
    free(R);
}

static void merge_sort_rec(int *arr, int l, int r) {
    if (l >= r) {
        return;
    }
    int m = l + (r - l) / 2;
    merge_sort_rec(arr, l, m);
    merge_sort_rec(arr, m + 1, r);
    merge(arr, l, m, r);
}

static void merge_sort(const int *data, size_t len, int *out) {
    memcpy(out, data, len * sizeof(int));
    merge_sort_rec(out, 0, (int)len - 1);
}

static int partition(int *arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            int tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
        }
    }
    int tmp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = tmp;
    return i + 1;
}

static void quick_sort_rec(int *arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort_rec(arr, low, pi - 1);
        quick_sort_rec(arr, pi + 1, high);
    }
}

static void quick_sort(const int *data, size_t len, int *out) {
    memcpy(out, data, len * sizeof(int));
    quick_sort_rec(out, 0, (int)len - 1);
}

static void print_array(const int *arr, size_t len) {
    printf("[");
    for (size_t i = 0; i < len; i++) {
        printf("%d", arr[i]);
        if (i + 1 < len) {
            printf(", ");
        }
    }
    printf("]\\n");
}

int main(void) {
    int data[] = {64, 34, 25, 12, 22, 11, 90};
    size_t len = sizeof(data) / sizeof(data[0]);
    int *out = (int *)malloc(len * sizeof(int));
    if (!out) {
        return 1;
    }

    printf("Original: ");
    print_array(data, len);

    bubble_sort(data, len, out);
    printf("Bubble:   ");
    print_array(out, len);

    selection_sort(data, len, out);
    printf("Selection:");
    print_array(out, len);

    insertion_sort(data, len, out);
    printf("Insertion:");
    print_array(out, len);

    merge_sort(data, len, out);
    printf("Merge:    ");
    print_array(out, len);

    quick_sort(data, len, out);
    printf("Quick:    ");
    print_array(out, len);

    free(out);
    return 0;
}
