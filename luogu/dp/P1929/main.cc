#include <algorithm>
#include <cstdio>
const int inf = (int)1e9;
int main() {
  int N;
  scanf("%d", &N);
  int *height = new int[N];
  for (int i = 0; i < N; i++) scanf("%d", height + i);
  int *dp = new int[N];
  std::fill(dp, dp + N, inf);
  dp[0] = 0;
  int result = 0;
  for (int i = 1; i < N; i++) {
    if (height[i] == height[i - 1] + 1) {
      dp[i] = dp[i - 1] + 1;
    }
    for (int j = i - 1; j >= 1; j--) {    // go back from j
      for (int k = j - 1; k >= 0; k--) {  // jump from k
        if ((1 << j - k) + height[k] >= height[i]) {
          dp[i] = std::min(dp[i], dp[j] + j - k + 1);
          break;
        }
      }
      if (dp[i] == inf) {
        result = -1;
        break;
      }
    }
  }
  if (result != -1) result = dp[N - 1];
  printf("%d\n", result);
  delete[] dp;
  delete[] height;
}