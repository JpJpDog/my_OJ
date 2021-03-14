#include <algorithm>
#include <cstdio>

int main() {
  int T, M;
  scanf("%d %d", &T, &M);
  int *v = new int[M], *t = new int[M];
  for (int i = 0; i < M; i++) scanf("%d %d", t + i, v + i);
  int *value = new int[T + 1];
  std::fill(value, value + T + 1, 0);
  for (int i = 0; i < M; i++) {
    for (int j = T; j >= t[i]; j--) {
      value[j] = std::max(value[j], value[j - t[i]] + v[i]);
    }
  }
  printf("%d\n", value[T]);
  delete[] value;
  delete[] v;
  delete[] t;
}
