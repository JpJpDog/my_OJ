#include <algorithm>
#include <cstdio>

int main() {
  int N;
  scanf("%d", &N);
  int *arr = new int[N];
  for (int i = 0; i < N; i++) scanf("%d", arr + i);
  int *dp = new int[N + 1];
  dp[0] = 0;
  for (int i = 0; i < N; i++) {
    int max_v = dp[i] + arr[i];
    for (int j = 0; j < i; j++) {
      max_v = std::max(max_v, dp[j] + std::abs(arr[i] - arr[j]) * (i - j + 1));
    }
    dp[i + 1] = max_v;
  }
  printf("%d\n", dp[N]);
  delete[] arr;
  delete[] dp;
}
