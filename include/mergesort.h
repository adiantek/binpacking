#pragma once

#include <stddef.h>

void mergesort(void *base, size_t nmemb, size_t size, int (*cmp)(const void *, const void *));
