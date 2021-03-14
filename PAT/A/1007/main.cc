#include <cstdio>

int main() {
  int N;
  scanf("%d", &N);
  int arr[N];
  for (int i = 0; i < N; i++) {
    scanf("%d", arr + i);
  }
  int sum = -1, first = 0, end = -1;
  int s = 0, f = first;
  for (int e = 0; e < N; e++) {
    s += arr[e];
    if (s > sum) {
      sum = s;
      first = f;
      end = e;
    } else if (s < 0) {
      s = 0;
      f = e + 1;
    }
  }
  if (sum == -1) {
    printf("0 %d %d\n", arr[0], arr[N - 1]);
  } else {
    printf("%d %d %d\n", sum, arr[first], arr[end]);
  }
}