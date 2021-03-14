#include <algorithm>
#include <cstdio>

int main() {
  int n, m;
  scanf("%d %d", &n, &m);
  int *stu = new int[n];
  int *sum = new int[n + 1];  //(j,i] => sum[i]-sum[j]
  sum[0] = 0;
  for (int i = 0; i < n; i++) {
    int tmp;
    scanf("%d", &tmp);
    stu[i] = tmp == 1 ? -1 : 1;
    sum[i + 1] = sum[i] + stu[i];
  }
  int *dp = new int[n + 1];
  dp[0] = 0;
  for (int i = 1; i <= n; i++) {
    int min_n = dp[i - 1] + 1;
    for (int j = 0; j < i; j++) {
      int s = sum[i] - sum[j];
      if (abs(s) <= m || abs(s) == i - j) {
        min_n = std::min(min_n, dp[j] + 1);
      }
    }
    dp[i] = min_n;
  }
  printf("%d\n", dp[n]);
  delete[] dp;
  delete[] sum;
  delete[] stu;
  return 0;
}