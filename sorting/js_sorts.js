// Common sorting algorithms implemented in JavaScript.

function bubbleSort(data) {
  const arr = [...data];
  for (let i = 0; i < arr.length; i++) {
    for (let j = 0; j < arr.length - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        [arr[j], arr[j + 1]] = [arr[j + 1], arr[j]];
      }
    }
  }
  return arr;
}

function selectionSort(data) {
  const arr = [...data];
  for (let i = 0; i < arr.length; i++) {
    let minIdx = i;
    for (let j = i + 1; j < arr.length; j++) {
      if (arr[j] < arr[minIdx]) {
        minIdx = j;
      }
    }
    [arr[i], arr[minIdx]] = [arr[minIdx], arr[i]];
  }
  return arr;
}

function insertionSort(data) {
  const arr = [...data];
  for (let i = 1; i < arr.length; i++) {
    const key = arr[i];
    let j = i - 1;
    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = key;
  }
  return arr;
}

function merge(left, right) {
  const merged = [];
  let i = 0;
  let j = 0;
  while (i < left.length && j < right.length) {
    if (left[i] <= right[j]) {
      merged.push(left[i++]);
    } else {
      merged.push(right[j++]);
    }
  }
  return merged.concat(left.slice(i)).concat(right.slice(j));
}

function mergeSort(data) {
  if (data.length <= 1) {
    return [...data];
  }
  const mid = Math.floor(data.length / 2);
  const left = mergeSort(data.slice(0, mid));
  const right = mergeSort(data.slice(mid));
  return merge(left, right);
}

function quickSort(data) {
  const arr = [...data];
  function quick(low, high) {
    if (low < high) {
      const p = partition(low, high);
      quick(low, p - 1);
      quick(p + 1, high);
    }
  }

  function partition(low, high) {
    const pivot = arr[high];
    let i = low - 1;
    for (let j = low; j < high; j++) {
      if (arr[j] <= pivot) {
        i++;
        [arr[i], arr[j]] = [arr[j], arr[i]];
      }
    }
    [arr[i + 1], arr[high]] = [arr[high], arr[i + 1]];
    return i + 1;
  }

  quick(0, arr.length - 1);
  return arr;
}

const sample = [64, 34, 25, 12, 22, 11, 90];
console.log("Original:", sample);
console.log("Bubble:", bubbleSort(sample));
console.log("Selection:", selectionSort(sample));
console.log("Insertion:", insertionSort(sample));
console.log("Merge:", mergeSort(sample));
console.log("Quick:", quickSort(sample));

module.exports = {
  bubbleSort,
  selectionSort,
  insertionSort,
  mergeSort,
  quickSort,
};
