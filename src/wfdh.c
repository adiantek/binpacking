#include <ffdh.h>
#include <mergesort.h>
#include <stdlib.h>

typedef struct {
  float x;
  float y;
  float h;
} FShelf;

typedef struct {
  int32_t x;
  int32_t y;
  int32_t h;
} IShelf;

void wfdh_f(Bin *bin, FRect *rect, size_t n) {
  // worst-fit decreasing height
  merge_sort(rect, n, sizeof(FRect), FRect_cmp_by_h);

  size_t shelf_count = 0;
  size_t shelf_capacity = 1;
  FShelf *shelf = malloc(shelf_capacity * sizeof(FShelf));

  for (size_t i = n; i-- > 0;) {
    if (rect[i].bin_id) {
      continue;
    }
    float min_load = -1;
    size_t best_shelf = 0;
    for (size_t j = 0; j < shelf_count; j++) {
      if (shelf[j].y + rect[i].h > bin->h) {
        continue;
      }
      if (shelf[j].x + rect[i].w > bin->w) {
        continue;
      }
      if (shelf[j].x > min_load || min_load == -1) {
        min_load = shelf[j].x;
        best_shelf = j;
      }
    }
    if (min_load == -1) {
      float next_y = shelf_count ? shelf[shelf_count - 1].y + shelf[shelf_count - 1].h : 0;
      if (next_y + rect[i].h > bin->h) {
        continue;
      }
      if (shelf_count == shelf_capacity) {
        shelf_capacity *= 2;
        shelf = realloc(shelf, shelf_capacity * sizeof(FShelf));
      }
      shelf[shelf_count].x = 0;
      shelf[shelf_count].y = next_y;
      best_shelf = shelf_count++;
      shelf[best_shelf].h = rect[i].h;    
    }
    rect[i].x = shelf[best_shelf].x;
    rect[i].y = shelf[best_shelf].y;
    rect[i].bin_id = bin->id;
    shelf[best_shelf].x += rect[i].w;
  }

  free(shelf);
}

void wfdh_i(Bin *bin, IRect *rect, size_t n) {
  merge_sort(rect, n, sizeof(IRect), IRect_cmp_by_h);

  size_t shelf_count = 0;
  size_t shelf_capacity = 1;
  IShelf *shelf = malloc(shelf_capacity * sizeof(IShelf));

  for (size_t i = n; i-- > 0;) {
    if (rect[i].bin_id) {
      continue;
    }
    int32_t min_load = -1;
    size_t best_shelf = 0;
    for (size_t j = 0; j < shelf_count; j++) {
      if (shelf[j].y + rect[i].h > bin->h) {
        continue;
      }
      if (shelf[j].x + rect[i].w > bin->w) {
        continue;
      }
      if (shelf[j].x > min_load || min_load == -1) {
        min_load = shelf[j].x;
        best_shelf = j;
      }
    }
    if (min_load == -1) {
      int32_t next_y = shelf_count ? shelf[shelf_count - 1].y + shelf[shelf_count - 1].h : 0;
      if (next_y + rect[i].h > bin->h) {
        continue;
      }
      if (shelf_count == shelf_capacity) {
        shelf_capacity *= 2;
        shelf = realloc(shelf, shelf_capacity * sizeof(IShelf));
      }
      shelf[shelf_count].x = 0;
      shelf[shelf_count].y = next_y;
      best_shelf = shelf_count++;
      shelf[best_shelf].h = rect[i].h;    
    }
    rect[i].x = shelf[best_shelf].x;
    rect[i].y = shelf[best_shelf].y;
    rect[i].bin_id = bin->id;
    shelf[best_shelf].x += rect[i].w;
  }
}