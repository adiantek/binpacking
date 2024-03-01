#include <mergesort.h>
#include <stdlib.h>
#include <string.h>

#define arr(x) (base_ + (x) * size)

void merge(char *base_, size_t nmemb, size_t size,
           int (*cmp)(const void *, const void *), size_t start, size_t mid,
           size_t end) {
  size_t start2 = mid + 1;
  if (start2 == nmemb || cmp(arr(mid), arr(start2)) <= 0) {
    return;
  }

  void *value = NULL;
  while (start <= mid && start2 <= end) {
    if (cmp(arr(start), arr(start2)) <= 0) {
      start++;
    } else {
      if (value == NULL) {
        value = malloc(size);
      }
      memcpy(value, arr(start2), size);
      size_t index = start2;

      while (index != start) {
        memcpy(arr(index), arr((index - 1)), size);
        index--;
      }

      memcpy(arr(start), value, size);

      start++;
      mid++;
      start2++;
    }
  }
  if (value != NULL) {
    free(value);
  }
}

#define _min(a, b) ((a) < (b) ? (a) : (b))
void mergesort(void *base, size_t nmemb, size_t size,
               int (*cmp)(const void *, const void *)) {
  char *base_ = (char *)base;
  for (size_t curr_size = 1; curr_size <= nmemb - 1; curr_size *= 2) {
    for (size_t left_start = 0; left_start < nmemb - 1;
         left_start += 2 * curr_size) {
      size_t mid = _min(left_start + curr_size - 1, nmemb - 1);
      size_t right_end = _min(left_start + 2 * curr_size - 1, nmemb - 1);
      merge(base_, nmemb, size, cmp, left_start, mid, right_end);
    }
  }
}
