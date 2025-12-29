"""Common sorting algorithms implemented in Python.

Each function returns a new sorted list, preserving the original input.
"""

from __future__ import annotations

from typing import List


def bubble_sort(data: List[int]) -> List[int]:
    """Sort values using bubble sort."""
    arr = list(data)
    n = len(arr)
    for i in range(n):
        for j in range(0, n - i - 1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
    return arr


def selection_sort(data: List[int]) -> List[int]:
    """Sort values using selection sort."""
    arr = list(data)
    n = len(arr)
    for i in range(n):
        min_idx = i
        for j in range(i + 1, n):
            if arr[j] < arr[min_idx]:
                min_idx = j
        arr[i], arr[min_idx] = arr[min_idx], arr[i]
    return arr


def insertion_sort(data: List[int]) -> List[int]:
    """Sort values using insertion sort."""
    arr = list(data)
    for i in range(1, len(arr)):
        key = arr[i]
        j = i - 1
        while j >= 0 and key < arr[j]:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key
    return arr


def merge_sort(data: List[int]) -> List[int]:
    """Sort values using merge sort."""

    def _merge(left: List[int], right: List[int]) -> List[int]:
        merged: List[int] = []
        i = j = 0
        while i < len(left) and j < len(right):
            if left[i] <= right[j]:
                merged.append(left[i])
                i += 1
            else:
                merged.append(right[j])
                j += 1
        merged.extend(left[i:])
        merged.extend(right[j:])
        return merged

    arr = list(data)
    if len(arr) <= 1:
        return arr

    mid = len(arr) // 2
    left = merge_sort(arr[:mid])
    right = merge_sort(arr[mid:])
    return _merge(left, right)


def quick_sort(data: List[int]) -> List[int]:
    """Sort values using quick sort (Lomuto partition)."""
    arr = list(data)

    def _quick_sort(low: int, high: int) -> None:
        if low < high:
            pivot_index = _partition(low, high)
            _quick_sort(low, pivot_index - 1)
            _quick_sort(pivot_index + 1, high)

    def _partition(low: int, high: int) -> int:
        pivot = arr[high]
        i = low - 1
        for j in range(low, high):
            if arr[j] <= pivot:
                i += 1
                arr[i], arr[j] = arr[j], arr[i]
        arr[i + 1], arr[high] = arr[high], arr[i + 1]
        return i + 1

    _quick_sort(0, len(arr) - 1)
    return arr


if __name__ == "__main__":
    sample = [64, 34, 25, 12, 22, 11, 90]
    print("Original:", sample)
    print("Bubble:", bubble_sort(sample))
    print("Selection:", selection_sort(sample))
    print("Insertion:", insertion_sort(sample))
    print("Merge:", merge_sort(sample))
    print("Quick:", quick_sort(sample))
