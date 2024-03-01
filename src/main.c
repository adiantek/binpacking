#ifndef STATIC_LIBRARY

#include <containers.h>
#include <stdlib.h>
#include <mergesort.h>
#include <ffdh.h>

int main() {
  Bin *bin = Bin_rand(2, 100);
  // bin[0].w = 50;
  // bin[0].h = 50;
  FRect *rect = FRect_rand(100, 20);
  ffdh_f(bin, rect, 100);
  FRect_json(rect, 100, stdout);
  Bin_json(bin, 2, stdout);
  free(rect);
  free(bin);

  return 0;
}

#endif