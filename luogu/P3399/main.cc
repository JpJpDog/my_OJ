#include <algorithm>
#include <cstdio>

const int inf_pay = int(1e9);

int main() {
  int N, M;
  scanf("%d %d", &N, &M);
  int *dist = new int[N], *climate = new int[M];
  for (int i = 0; i < N; i++) scanf("%d", dist + i);
  for (int i = 0; i < M; i++) scanf("%d", climate + i);
  // a[i][j] is the least pay of reaching the city_i at least at day_j
  // a[i][j]=min(a[i-1][j-1]+c[j]*d[i], a[i][j-1])
  // compress: dp[i]=min(dp[i-1]+c[j]*d[i], dp[i]) in j's iteration
  int *dp1 = new int[N + 1];
  int *dp = dp1 + 1;
  dp[-1] = 0;
  std::fill(dp, dp + N, inf_pay);
  for (int j = 0; j < M; j++) {
    for (int i = std::min(N - 1, j); i >= std::max(0, j - M + N); i--) {
      dp[i] = std::min(dp[i], dp[i - 1] + climate[j] * dist[i]);
    }
  }
  printf("%d\n", dp[N - 1]);
  delete[] dp1;
  delete[] dist;
  delete[] climate;
}
