#include <algorithm>
#include <cstdio>
#include <cstdlib>

void fun1(int *arr, int N, int *qlens, int M) {
  int *dp = new int[N];
  std::fill(dp, dp + N, 1);
  dp[N - 1] = 1;
  int max_lis_len = 1;
  for (int i = N - 2; i >= 0; i--) {
    for (int j = i + 1; j < N; j++) {
      if (arr[i] < arr[j] && dp[i] < dp[j] + 1) {
        dp[i] = dp[j] + 1;
      }
      max_lis_len = std::max(max_lis_len, dp[i]);
    }
  }
  int *result = new int[N];
  for (int i = 0; i < M; i++) {
    int qlen = qlens[i];
    if (qlen > max_lis_len) {
      //   printf("Impossible\n");
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
}

void fun2(int *arr, int N, int *qlens, int M) {
  int *dp = new int[N], *prev = new int[N], *map = new int[N],
      *len = new int[N];
  dp[0] = arr[N - 1];
  prev[N - 1] = -1;
  map[0] = N - 1;
  len[N - 1] = 1;
  int dp_len = 1;
  for (int i = N - 2; i >= 0; i--) {
    // find the idx of first element <= arr[i]
    int idx = std::lower_bound(dp, dp + dp_len, arr[i],
                               [](int a, int b) { return a > b; }) -
              dp;
    dp[idx] = arr[i];
    if (idx == dp_len) {
      dp_len++;
    }
    prev[i] = idx == 0 ? -1 : map[idx - 1];
    map[idx] = i;
    // len[i]
  }
  for (int i = 0; i < M; i++) {
    int qlen = qlens[i];
    if (qlen > dp_len) {
      //   printf("Impossible\n");
    } else if (qlen > 0) {
      int cur_i = map[qlen - 1];
      printf("%d", arr[cur_i]);
      while ((cur_i = prev[cur_i]) != -1) {
        printf(" %d", arr[cur_i]);
      }
      printf("\n");
    } else {
      printf("\n");
    }
  }
  delete[] len;
  delete[] prev;
  delete[] map;
  delete[] dp;
}

const int kMaxLen = 15;
const int kMaxEle = 15;

int main() {
  int N = kMaxLen, M = kMaxLen;
  int *arr = new int[N];
  for (int i = 0; i < N; i++) {
    arr[i] = rand() % kMaxEle;
    printf("%d ", arr[i]);
  }
  printf("\n\n");
  int *qlens = new int[N];
  for (int i = 0; i < N; i++) {
    qlens[i] = i + 1;
  }
  fun1(arr, N, qlens, N);
  printf("\n");
  fun2(arr, N, qlens, N);
  delete[] arr;
}