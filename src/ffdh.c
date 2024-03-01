#include <ffdh.h>
#include <mergesort.h>

void ffdh_f(Bin *bin, FRect *rect, size_t n) {
  // first fit decreasing height
  merge_sort(rect, n, sizeof(FRect), FRect_cmp_by_h);

  float curr_y = 0;
  while (true) {
    bool skipped = false;
    float max_h = -1;
    float curr_x = 0;
    for (size_t i = n; i-- > 0;) {
      if (rect[i].bin_id) {
        continue;
      }
      if (curr_y + rect[i].h > bin->h) {
        skipped = true;
        continue;
      }
      if (curr_x + rect[i].w > bin->w) {
        skipped = true;
        continue;
      }
      if (max_h < rect[i].h) {
        max_h = rect[i].h;
      }
      rect[i].x = curr_x;
      rect[i].y = curr_y;
      rect[i].bin_id = bin->id;

      curr_x += rect[i].w;
    }
    if (skipped && max_h > 0) {
      curr_y += max_h;
    } else {
      break;
    }
  }
}

void ffdh_i(Bin *bin, IRect *rect, size_t n) {
  merge_sort(rect, n, sizeof(IRect), IRect_cmp_by_h);

  int32_t curr_y = 0;
  while (true) {
    bool skipped = false;
    int32_t max_h = -1;
    int32_t curr_x = 0;
    for (size_t i = n; i-- > 0;) {
      if (rect[i].bin_id) {
        continue;
      }
      if (curr_y + rect[i].h > bin->h) {
        skipped = true;
        continue;
      }
      if (curr_x + rect[i].w > bin->w) {
        skipped = true;
        continue;
      }
      if (max_h < rect[i].h) {
        max_h = rect[i].h;
      }
      rect[i].x = curr_x;
      rect[i].y = curr_y;
      rect[i].bin_id = bin->id;

      curr_x += rect[i].w;
    }
    if (skipped && max_h > 0) {
      curr_y += max_h;
    } else {
      break;
    }
  }
}