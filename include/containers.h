#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef RUST_API
#include <stdio.h>
#endif

typedef struct IRect {
  size_t id;

  size_t bin_id;
  int32_t x;
  int32_t y;
  int32_t w;
  int32_t h;
} IRect;

typedef struct FRect {
  size_t id;

  size_t bin_id;
  float x;
  float y;
  float w;
  float h;
} FRect;

typedef struct Bin {
  size_t id;

  int32_t w;
  int32_t h;
} Bin;

IRect *IRect_rand(size_t n, int32_t size);
FRect *FRect_rand(size_t n, int32_t size);

Bin *Bin_rand(size_t n, int32_t size);

void IRect_to_FRect(IRect *i_rect, FRect *f_rect, size_t n);
void FRect_to_IRect(FRect *f_rect, IRect *i_rect, size_t n);

void IRect_clear(IRect *rect, size_t n);
void FRect_clear(FRect *rect, size_t n);

int IRect_cmp_by_h(const void *a, const void *b);
int FRect_cmp_by_h(const void *a, const void *b);

bool FRect_overlap(FRect *a, FRect *b);
bool IRect_overlap(IRect *a, IRect *b);

size_t IRect_packed(IRect *rect, size_t n);
size_t FRect_packed(FRect *rect, size_t n);

#ifndef RUST_API
void IRect_json(IRect *rect, size_t n, FILE *fp);
void FRect_json(FRect *rect, size_t n, FILE *fp);
void Bin_json(Bin *bin, size_t n, FILE *fp);
#endif
