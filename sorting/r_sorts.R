# Common sorting algorithms implemented in R.

bubble_sort <- function(data) {
  arr <- as.integer(data)
  n <- length(arr)
  for (i in seq_len(n)) {
    for (j in seq_len(n - i)) {
      if (arr[j] > arr[j + 1]) {
        tmp <- arr[j]
        arr[j] <- arr[j + 1]
        arr[j + 1] <- tmp
      }
    }
  }
  arr
}

selection_sort <- function(data) {
  arr <- as.integer(data)
  n <- length(arr)
  for (i in seq_len(n)) {
    min_idx <- i
    for (j in (i + 1):n) {
      if (j <= n && arr[j] < arr[min_idx]) {
        min_idx <- j
      }
    }
    tmp <- arr[i]
    arr[i] <- arr[min_idx]
    arr[min_idx] <- tmp
  }
  arr
}

insertion_sort <- function(data) {
  arr <- as.integer(data)
  for (i in 2:length(arr)) {
    key <- arr[i]
    j <- i - 1
    while (j >= 1 && arr[j] > key) {
      arr[j + 1] <- arr[j]
      j <- j - 1
    }
    arr[j + 1] <- key
  }
  arr
}

merge_sort <- function(data) {
  arr <- as.integer(data)
  if (length(arr) <= 1) {
    return(arr)
  }
  mid <- length(arr) %/% 2
  left <- merge_sort(arr[1:mid])
  right <- merge_sort(arr[(mid + 1):length(arr)])
  merge_vectors(left, right)
}

merge_vectors <- function(left, right) {
  merged <- integer(0)
  i <- 1
  j <- 1
  while (i <= length(left) && j <= length(right)) {
    if (left[i] <= right[j]) {
      merged <- c(merged, left[i])
      i <- i + 1
    } else {
      merged <- c(merged, right[j])
      j <- j + 1
    }
  }
  if (i <= length(left)) merged <- c(merged, left[i:length(left)])
  if (j <= length(right)) merged <- c(merged, right[j:length(right)])
  merged
}

quick_sort <- function(data) {
  arr <- as.integer(data)
  if (length(arr) <= 1) {
    return(arr)
  }
  pivot <- arr[length(arr)]
  left <- arr[arr < pivot]
  middle <- arr[arr == pivot]
  right <- arr[arr > pivot]
  c(quick_sort(left), middle, quick_sort(right))
}

sample <- c(64, 34, 25, 12, 22, 11, 90)
cat("Original:", sample, "\n")
cat("Bubble:  ", bubble_sort(sample), "\n")
cat("Selection:", selection_sort(sample), "\n")
cat("Insertion:", insertion_sort(sample), "\n")
cat("Merge:   ", merge_sort(sample), "\n")
cat("Quick:   ", quick_sort(sample), "\n")
