#ifndef STATIC_LIBRARY

#include <bfdh.h>
#include <containers.h>
#include <ffdh.h>
#include <mergesort.h>
#include <nfdh.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wfdh.h>

#define BinpackCaller void (*)(Bin *, void *, size_t)

int main(int argc, char **argv) {
  if (argc < 4) {
    fprintf(stderr,
            "Usage for testing: %s <algorithm> <float/int> <num tests>\n",
            argv[0]);
    fprintf(stderr, "algorithm: bfdh | ffdh | nfdh | wfdh | cmp\n");
    fprintf(stderr, "  bfdh - best-fit decreasing height\n");
    fprintf(stderr, "  ffdh - first-fit decreasing height\n");
    fprintf(stderr, "  nfdh - next-fit decreasing height\n");
    fprintf(stderr, "  wfdh - worst-fit decreasing height\n");
    fprintf(
        stderr,
        "  cmp - compare all available algorithms and return result in CSV\n");
    return 1;
  }
  time_t seed = time(NULL);
  printf("Seed: %lld\n", (long long) seed);
  srand(seed);
  char *algorithm = argv[1];
  char *type = argv[2];
  int num_tests = atoi(argv[3]);

  void (*algo)(Bin *, void *, size_t);
  bool float_mode = false;

  if (strcmp(type, "float") == 0) {
    float_mode = true;

    if (strcmp(algorithm, "bfdh") == 0) {
      algo = (BinpackCaller)bfdh_f;
    } else if (strcmp(algorithm, "ffdh") == 0) {
      algo = (BinpackCaller)ffdh_f;
    } else if (strcmp(algorithm, "nfdh") == 0) {
      algo = (BinpackCaller)nfdh_f;
    } else if (strcmp(algorithm, "wfdh") == 0) {
      algo = (BinpackCaller)wfdh_f;
    } else if (strcmp(algorithm, "cmp") == 0) {
      algo = NULL;
    } else {
      fprintf(stderr, "Invalid algorithm: %s\n", algorithm);
      return 1;
    }
  } else if (strcmp(type, "int") == 0) {
    float_mode = false;

    if (strcmp(algorithm, "bfdh") == 0) {
      algo = (BinpackCaller)bfdh_i;
    } else if (strcmp(algorithm, "ffdh") == 0) {
      algo = (BinpackCaller)ffdh_i;
    } else if (strcmp(algorithm, "nfdh") == 0) {
      algo = (BinpackCaller)nfdh_i;
    } else if (strcmp(algorithm, "wfdh") == 0) {
      algo = (BinpackCaller)wfdh_i;
    } else if (strcmp(algorithm, "cmp") == 0) {
      algo = NULL;
    } else {
      fprintf(stderr, "Invalid algorithm: %s\n", algorithm);
      return 1;
    }
  } else {
    fprintf(stderr, "Invalid type: %s\n", type);
    return 1;
  }

  if (algo == NULL) {
    // compare all algorithms
    printf("test,bin_w,bin_h,rectangles,bfdh,ffdh,nfdh,wfdh\n");
    for (int i = 0; i < num_tests; i++) {
      size_t rectangles = rand() % 32 + 32;
      size_t bin_size = rand() % 512 + 512;
      Bin *bin = Bin_rand(1, bin_size);
      void *rect;
      if (float_mode) {
        rect = FRect_rand(rectangles, 256);
      } else {
        rect = IRect_rand(rectangles, 256);
      }
      printf("%d,%d,%d,%zu,", i, bin->w, bin->h, rectangles);
      for (int j = 0; j < 4; j++) {
        if (float_mode) {
          FRect_clear((FRect *)rect, rectangles);
        } else {
          IRect_clear((IRect *)rect, rectangles);
        }
        void (*check_algo)(Bin *, void *, size_t);
        if (float_mode) {
          if (j == 0) {
            check_algo = (BinpackCaller)bfdh_f;
          } else if (j == 1) {
            check_algo = (BinpackCaller)ffdh_f;
          } else if (j == 2) {
            check_algo = (BinpackCaller)nfdh_f;
          } else if (j == 3) {
            check_algo = (BinpackCaller)wfdh_f;
          }
        } else {
          if (j == 0) {
            check_algo = (BinpackCaller)bfdh_i;
          } else if (j == 1) {
            check_algo = (BinpackCaller)ffdh_i;
          } else if (j == 2) {
            check_algo = (BinpackCaller)nfdh_i;
          } else if (j == 3) {
            check_algo = (BinpackCaller)wfdh_i;
          }
        }
        check_algo(bin, rect, rectangles);
        if (float_mode) {
          printf("%zu", FRect_packed((FRect *)rect, rectangles));
        } else {
          printf("%zu", IRect_packed((IRect *)rect, rectangles));
        }
        if (j < 3) {
          printf(",");
        }
      }

      printf("\n");
      free(rect);
      free(bin);
    }
  } else {
    // check if algorithm is correct (no overlaps, no rectangles outside of bin)
    for (int i = 0; i < num_tests; i++) {
      size_t rectangles = rand() % 128 + 128;
      size_t bin_size = rand() % 1024 + 1024;
      Bin *bin = Bin_rand(1, bin_size);
      void *rect;
      if (float_mode) {
        rect = FRect_rand(rectangles, 1000);
      } else {
        rect = IRect_rand(rectangles, 1000);
      }
      algo(bin, rect, rectangles);
      for (int j = 0; j < rectangles; j++) {
        for (int k = 0; k < j; k++) {
          if (float_mode) {
            FRect *rect_j = &((FRect *)rect)[j];
            FRect *rect_k = &((FRect *)rect)[k];
            if (FRect_overlap(rect_j, rect_k)) {
              fprintf(stderr, "Overlap: %d %d\n", j, k);
              FRect_json((FRect *)rect, rectangles, stderr);
              Bin_json(bin, 1, stderr);
            }
          } else {
            IRect *rect_j = &((IRect *)rect)[j];
            IRect *rect_k = &((IRect *)rect)[k];
            if (IRect_overlap(rect_j, rect_k)) {
              fprintf(stderr, "Overlap: %d %d\n", j, k);
              IRect_json((IRect *)rect, rectangles, stderr);
              Bin_json(bin, 1, stderr);
            }
          }
        }

        // check if rectangle is outside of bin
        if (float_mode) {
          FRect *rect_j = &((FRect *)rect)[j];
          if (rect_j->bin_id == 0) {
            // not packed
            continue;
          }
          if (rect_j->x < 0 || rect_j->y < 0 ||
              rect_j->x + rect_j->w > bin->w ||
              rect_j->y + rect_j->h > bin->h) {
            fprintf(stderr, "Outside: %d\n", j);
            FRect_json(rect_j, 1, stderr);
            Bin_json(bin, 1, stderr);
          }
        } else {
          IRect *rect_j = &((IRect *)rect)[j];
          if (rect_j->bin_id == 0) {
            // not packed
            continue;
          }
          if (rect_j->x < 0 || rect_j->y < 0 ||
              rect_j->x + rect_j->w > bin->w ||
              rect_j->y + rect_j->h > bin->h) {
            fprintf(stderr, "Outside: %d\n", j);
            IRect_json(rect_j, 1, stderr);
            Bin_json(bin, 1, stderr);
          }
        }
      }
      free(rect);
      free(bin);
    }
  }

  return 0;
}

#endif