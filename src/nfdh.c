#include <ffdh.h>
#include <mergesort.h>

void nfdh_f(Bin *bin, FRect *rect, size_t n) {
  // next fit decreasing height
  merge_sort(rect, n, sizeof(FRect), FRect_cmp_by_h);

  float curr_y = 0;
  float max_h = -1;
  float curr_x = 0;
  for (size_t i = n; i-- > 0;) {
    if (rect[i].bin_id || rect[i].w > bin->w) {
      continue;
    }
    if (curr_y + rect[i].h > bin->h) {
      continue;
    }
    if (curr_x + rect[i].w > bin->w) {
      if (curr_y + max_h + rect[i].h > bin->h) {
        continue;
      }
      curr_x = 0;
      curr_y += max_h;
      max_h = -1;
    }
    if (max_h < rect[i].h) {
      max_h = rect[i].h;
    }
    rect[i].x = curr_x;
    rect[i].y = curr_y;
    rect[i].bin_id = bin->id;

    curr_x += rect[i].w;
  }
}

void nfdh_i(Bin *bin, IRect *rect, size_t n) {
  merge_sort(rect, n, sizeof(IRect), IRect_cmp_by_h);

  int32_t curr_y = 0;
  int32_t max_h = -1;
  int32_t curr_x = 0;
  for (size_t i = n; i-- > 0;) {
    if (rect[i].bin_id || rect[i].w > bin->w) {
      continue;
    }
    if (curr_y + rect[i].h > bin->h) {
      continue;
    }
    if (curr_x + rect[i].w > bin->w) {
      if (curr_y + max_h + rect[i].h > bin->h) {
        continue;
      }
      curr_x = 0;
      curr_y += max_h;
      max_h = -1;
    }
    if (max_h < rect[i].h) {
      max_h = rect[i].h;
    }
    rect[i].x = curr_x;
    rect[i].y = curr_y;
    rect[i].bin_id = bin->id;

    curr_x += rect[i].w;
  }
}