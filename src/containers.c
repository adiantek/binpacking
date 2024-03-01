#include <containers.h>
#include <stdlib.h>

IRect *IRect_rand(size_t n, int32_t size) {
  IRect *rect = (IRect *)malloc(sizeof(IRect) * n);
  for (size_t i = 0; i < n; i++) {
    rect[i].id = i;
    rect[i].bin_id = 0;
    rect[i].x = -1;
    rect[i].y = -1;
    if (size == 1) {
      rect[i].w = 1;
      rect[i].h = 1;
    } else {
      rect[i].w = 1 + (rand() % (size - 1));
      rect[i].h = 1 + (rand() % (size - 1));
    }
  }
  return rect;
}

FRect *FRect_rand(size_t n, int32_t size) {
  FRect *rect = (FRect *)malloc(sizeof(FRect) * n);
  for (size_t i = 0; i < n; i++) {
    rect[i].id = i;
    rect[i].bin_id = 0;
    rect[i].x = -1;
    rect[i].y = -1;
    rect[i].w = (float)(rand() * 1.0F / RAND_MAX * size);
    rect[i].h = (float)(rand() * 1.0F / RAND_MAX * size);
  }
  return rect;
}

Bin *Bin_rand(size_t n, int32_t size) {
  Bin *bin = (Bin *)malloc(sizeof(Bin) * n);
  for (size_t i = 0; i < n; i++) {
    bin[i].id = i + 1;
    if (size == 1) {
      bin[i].w = 1;
      bin[i].h = 1;
    } else {
      bin[i].w = 1 + (rand() % (size - 1));
      bin[i].h = 1 + (rand() % (size - 1));
    }
  }
  return bin;
}

void IRect_to_FRect(IRect *i_rect, FRect *f_rect, size_t n) {
  for (size_t i = 0; i < n; i++) {
    f_rect[i].id = i_rect[i].id;
    f_rect[i].bin_id = i_rect[i].bin_id;
    f_rect[i].x = (float)i_rect[i].x;
    f_rect[i].y = (float)i_rect[i].y;
    f_rect[i].w = (float)i_rect[i].w;
    f_rect[i].h = (float)i_rect[i].h;
  }
}

void FRect_to_IRect(FRect *f_rect, IRect *i_rect, size_t n) {
  for (size_t i = 0; i < n; i++) {
    i_rect[i].id = f_rect[i].id;
    i_rect[i].bin_id = f_rect[i].bin_id;
    i_rect[i].x = (int32_t)(f_rect[i].x + 0.5F);
    i_rect[i].y = (int32_t)(f_rect[i].y + 0.5F);
    i_rect[i].w = (int32_t)(f_rect[i].w + 0.5F);
    i_rect[i].h = (int32_t)(f_rect[i].h + 0.5F);
  }
}

void IRect_clear(IRect *rect, size_t n) {
  for (size_t i = 0; i < n; i++) {
    rect[i].id = i;
    rect[i].bin_id = 0;
    rect[i].x = -1;
    rect[i].y = -1;
  }
}

void FRect_clear(FRect *rect, size_t n) {
  for (size_t i = 0; i < n; i++) {
    rect[i].id = i;
    rect[i].bin_id = 0;
    rect[i].x = -1;
    rect[i].y = -1;
  }
}

int IRect_cmp_by_h(const void *a, const void *b) {
  const IRect *ia = (const IRect *)a;
  const IRect *ib = (const IRect *)b;
  if (ia->h < ib->h) {
    return -1;
  }
  if (ia->h > ib->h) {
    return 1;
  }
  if (ia->id < ib->id) {
    return -1;
  }
  if (ia->id > ib->id) {
    return 1;
  }
  return 0;
}

int FRect_cmp_by_h(const void *a, const void *b) {
  const FRect *fa = (const FRect *)a;
  const FRect *fb = (const FRect *)b;
  if (fa->h < fb->h) {
    return -1;
  }
  if (fa->h > fb->h) {
    return 1;
  }
  if (fa->id < fb->id) {
    return -1;
  }
  if (fa->id > fb->id) {
    return 1;
  }
  return 0;
}

void IRect_json(IRect *rect, size_t n, FILE *fp) {
  fprintf(fp, "[\n");
  for (size_t i = 0; i < n; i++) {
    fprintf(
        fp, "  {\"id\":%zu,\"bin_id\":%zd,\"x\":%d,\"y\":%d,\"w\":%d,\"h\":%d}",
        rect[i].id, rect[i].bin_id, rect[i].x, rect[i].y, rect[i].w, rect[i].h);
    if (i < n - 1) {
      fprintf(fp, ",");
    }
    fprintf(fp, "\n");
  }
  fprintf(fp, "]\n");
}

void FRect_json(FRect *rect, size_t n, FILE *fp) {
  fprintf(fp, "[\n");
  for (size_t i = 0; i < n; i++) {
    fprintf(
        fp, "  {\"id\":%zu,\"bin_id\":%zd,\"x\":%f,\"y\":%f,\"w\":%f,\"h\":%f}",
        rect[i].id, rect[i].bin_id, rect[i].x, rect[i].y, rect[i].w, rect[i].h);
    if (i < n - 1) {
      fprintf(fp, ",");
    }
    fprintf(fp, "\n");
  }
  fprintf(fp, "]\n");
}

void Bin_json(Bin *bin, size_t n, FILE *fp) {
  fprintf(fp, "[\n");
  for (size_t i = 0; i < n; i++) {
    fprintf(fp, "  {\"id\":%zu,\"w\":%d,\"h\":%d}", bin[i].id, bin[i].w,
            bin[i].h);
    if (i < n - 1) {
      fprintf(fp, ",");
    }
    fprintf(fp, "\n");
  }
  fprintf(fp, "]\n");
}
