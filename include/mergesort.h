#pragma once

#include <stddef.h>

void merge_sort(void *base, size_t nmemb, size_t size, int (*cmp)(const void *, const void *));
