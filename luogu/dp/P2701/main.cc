#include <algorithm>
#include <cstdio>
#include <cstring>

int main() {
  int N, T;
  scanf("%d %d", &N, &T);
  bool *tree1 = new bool[N * N];
  memset(tree1, 0, sizeof(*tree1) * N * N);
  bool **tree = new bool *[N];
  for (int i = 0; i < N; i++) tree[i] = tree1 + N * i;
  for (int i = 0; i < T; i++) {
    int a, b;
    scanf("%d %d", &a, &b);
    tree[a - 1][b - 1] = true;
  }
  int *dp1 = new int[(N + 1) * (N + 1)];
  int **dp = new int *[N + 1];
  for (int i = 0; i < N + 1; i++) dp[i] = dp1 + (N + 1) * i;
  for (int i = 1; i < N + 1; i++) dp[i][0] = dp[0][i] = 0;
  dp[0][0] = 0;
  int max_a = 0;
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) {
      dp[i][j] = tree[i - 1][j - 1] ? 0 : std::min(std::min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]) + 1;
      max_a = std::max(max_a, dp[i][j]);
    }
  }
  printf("%d\n", max_a);
  delete[] dp;
  delete[] dp1;
  delete[] tree;
  delete[] tree1;
  return 0;
}