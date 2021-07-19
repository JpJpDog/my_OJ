#include <algorithm>
#include <cstdio>

// O(nlog(n))

int main() {
  int N, M;
  scanf("%d", &N);
  int *arr = new int[N];
  for (int i = 0; i < N; i++) {
    scanf("%d", arr + i);
  }
  scanf("%d", &M);
  int *qlens = new int[M];
  for (int i = 0; i < M; i++) {
    scanf("%d", qlens + i);
  }
  // dp[i] is the max length of increasing array start by arr[i]
  int *dp = new int[N];
  std::fill(dp, dp + N, 1);
  dp[N - 1] = 1;
  int max_lis_len = 1;
  for (int i = N - 2; i >= 0; i--) {
    // for (int j = i + 1; j < N; j++) {
    //   if (arr[i] < arr[j] && dp[i] < dp[j] + 1) {
    //     dp[i] = dp[j] + 1;
    //   }
    //   max_lis_len = std::max(max_lis_len, dp[i]);
    // }
    
  }
  int *result = new int[N];
  for (int i = 0; i < M; i++) {
    int qlen = qlens[i];
    if (qlen > max_lis_len) {
      printf("Impossible\n");
    } else if (qlen == 0) {
      printf("\n");
    } else {
      int r_i = 0;
      for (int j = 0; j < N && r_i < qlen; j++) {
        if (dp[j] >= qlen - r_i && (r_i == 0 || arr[j] > result[r_i - 1])) {
          result[r_i++] = arr[j];
        }
      }
      printf("%d", result[0]);
      for (int i = 1; i < qlen; i++) {
        printf(" %d", result[i]);
      }
      printf("\n");
    }
  }
  delete[] result;
  delete[] dp;
  delete[] qlens;
  delete[] arr;
}