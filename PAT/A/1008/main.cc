#include <cstdio>

int main() {
  int N;
  scanf("%d", &N);
  int res[N];
  for (int i = 0; i < N; i++) {
    scanf("%d", res + i);
  }
  int cur = 0;
  int time = 0;
  for (int i = 0; i < N; i++) {
    if (res[i] > cur) {
      time += 6 * (res[i] - cur);
    } else {
      time += 4 * (cur - res[i]);
    }
    cur = res[i];
  }
  time += 5 * N;
  printf("%d\n", time);
}