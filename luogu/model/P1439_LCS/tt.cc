#include <time.h>

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <memory>

const int inf = 0x7fffffff;


int LIS(int* map, int* arr, int len) {
  int *dp = new int[len], dp_len = 0;
  dp[dp_len++] = map[arr[1]];
  for (int i = 1; i <= len; i++) {
    int key = map[arr[i]];
    if (key > dp[dp_len - 1]) {
      dp[dp_len++] = key;
    } else {
      int* tmp = std::upper_bound(dp, dp + dp_len, key);
      *tmp = key;
    }
  }
  delete[] dp;
  return dp_len;
}

int main() {
  int m;
  scanf("%d", &m);
  int *arr1 = new int[m + 1], *arr2 = new int[m + 1], *map = new int[m + 1];
  for (int i = 1; i <= m; i++) scanf("%d", arr1 + i);
  for (int i = 1; i <= m; i++) scanf("%d", arr2 + i);
  for (int i = 1; i <= m; i++) map[arr1[i]] = i;
  printf("%d\n", LIS(map, arr2, m));
  delete[] arr1;
  delete[] arr2;
}