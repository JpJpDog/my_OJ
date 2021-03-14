#include <assert.h>

#include <algorithm>
#include <cstdio>

int draw(int *h, int w, int bottom) {
  int min_h = 1e9;
  for (int i = 0; i < w; i++) min_h = std::min(min_h, h[i]);
  int sum = min_h - bottom, start = 0;
  bool in = false;
  for (int i = 0; i < w; i++) {
    if (!in) {
      if (h[i] == min_h)
        start = i + 1;
      else
        in = true;
    } else {
      if (h[i] == min_h) {
        sum += draw(h + start, i - start, min_h);
        start = i + 1;
        in = false;
      }
    }
  }
  if (in) sum += draw(h + start, w - start, min_h);
  return std::min(sum, w);
}

int main() {
  int N;
  scanf("%d", &N);
  int *h = new int[N];
  for (int i = 0; i < N; i++) scanf("%d", h + i);
  printf("%d\n", draw(h, N, 0));
  delete[] h;
}