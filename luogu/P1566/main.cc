#include <algorithm>
#include <cstdio>
const int max_len = 30;
const int max_n = 1000;

int main() {
  int *arr = new int[max_len];
  int *dp = new int[max_n + 1];  // dp[i] 表示和为i的方案数
  dp[0] = 1;
  int t;
  scanf("%d", &t);
  int *result = new int[t];
  for (int i = 0; i < t; i++) {
    int m;
    scanf("%d", &m);
    int max_ele = 0;
    for (int i = 0; i < m; i++) {
      scanf("%d", arr + i);
      max_ele = std::max(max_ele, arr[i]);
    }
    std::fill(dp + 1, dp + max_ele + 1, 0);
    for (int i = 0; i < m; i++) {
      for (int j = max_ele; j >= arr[i]; j--) {
        dp[j] += dp[j - arr[i]];
      }
    }
    int sum = 0;
    for (int i = 0; i < m; i++) sum += dp[arr[i]];
    result[i] = sum - m;
  }
  for (int i = 0; i < t; i++) printf("%d\n", result[i]);
  delete[] result;
  delete[] dp;
  delete[] arr;
  return 0;
}