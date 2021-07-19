#include <time.h>

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <memory>

const int inf = 0x7fffffff;

// dp[i] is the length of longest subarr that has end element arr[i]
// dp[i]= 1 if arr[i] bigger than anyone before or max(arr[j]+1)
int LIS_n2(int* arr, int len, int** out_subarr) {
  int *dp = new int[len], *prev = new int[len];
  std::fill(dp, dp + len, 0);
  std::fill(prev, prev + len, -1);
  dp[0] = 1;
  for (int i = 1; i < len; i++) {
    int max_l = 0, p = -1;
    for (int j = 0; j < i; j++) {
      if (arr[j] < arr[i] && dp[j] > max_l) {
        max_l = dp[j];
        p = j;
        max_l = std::max(max_l, dp[j]);
      }
    }
    dp[i] = max_l + 1;
    prev[i] = p;
  }
  int max_l = -1, last = -1;
  for (int i = 0; i < len; i++) {
    if (dp[i] > max_l) {
      max_l = dp[i];
      last = i;
    }
  }
  int* subarr = new int[max_l];
  *out_subarr = subarr;
  int l = max_l - 1;
  for (int i = last; i != -1; i = prev[i]) {
    subarr[l--] = arr[i];
  }
  delete[] dp;
  delete[] prev;
  return max_l;
}

// dp[i] is the minimum end element of the increasing subarr that length is i
// so after every iteration, [0,sub_len) of dp is increasing
int LIS_nlogn(int* arr, int len, int** out_subarr) {
  int *dp = new int[len], dp_len = 0;
  int* mp = new int[len];
  dp[0] = arr[dp_len++];
  for (int i = 1; i < len; i++) {  // in i's iteration, check the first i arr
    if (arr[i] > dp[dp_len - 1]) {
      mp[i] = dp_len;
      dp[dp_len++] = arr[i];
    } else {
      int begin = 0, end = dp_len - 1;
      while (begin <= end) {  // after loop, dp[begin] must be the first element > arr[i] or dp[begin]=arr[i]
                              // dp[end] must be the first element >arr[i]
        int mid = (begin + end) >> 1;
        if (dp[mid] >= arr[i])
          end = mid - 1;
        else
          begin = mid + 1;
      }
      mp[i] = begin;
      dp[begin] = arr[i];
    }
  }
  int* subarr = new int[dp_len];
  *out_subarr = subarr;
  int l = dp_len - 1;
  for (int i = len - 1; i >= 0; i--) {
    if (mp[i] == l) {
      subarr[l--] = arr[i];
    }
  }
  delete[] dp;
  return dp_len;
}

int LCS(int* arr1, int l1, int* arr2, int l2, int** out_subarr) {
  int* dp1 = new int[(l1 + 1) * (l2 + 1)];
  int** dp = new int*[l1 + 1];
  for (int i = 0; i <= l1; i++) dp[i] = dp1 + (l2 + 1) * i;
  for (int i = 0; i <= l1; i++) dp[i][0] = 0;
  for (int i = 0; i <= l2; i++) dp[0][i] = 0;
  for (int i = 1; i <= l1; i++) {
    for (int j = 1; j <= l2; j++) {
      if (arr1[i - 1] == arr2[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      } else if (dp[i][j - 1] < dp[i - 1][j]) {
        dp[i][j] = dp[i - 1][j];
      } else {
        dp[i][j] = dp[i][j - 1];
      }
    }
  }
  int sublen = dp[l1][l2];
  int* subarr = new int[sublen];
  *out_subarr = subarr;
  int ii = l1, jj = l2, ll = sublen - 1;
  while (ll >= 0) {
    if (dp[ii][jj] == dp[ii - 1][jj - 1]) {
      subarr[ll--] = arr1[ii - 1];
      ii--;
      jj--;
    } else if (dp[ii][jj] == dp[ii - 1][jj]) {
      ii--;
    } else {
      jj--;
    }
  }
  delete[] dp;
  delete[] dp1;
  return sublen;
}

int LIS(int* map, int* arr, int len) {
  int *dp = new int[len], dp_len = 0;
  dp[dp_len++] = map[arr[1]];
  for (int i = 1; i <= len; i++) {
    int key = map[arr[i]];
    if (key > dp[dp_len - 1]) {
      dp[dp_len++] = key;
    } else {
      // int begin = 0, end = dp_len - 1;
      // while (begin <= end) {
      //   int mid = (begin + end) / 2;
      //   if (dp[mid] <= key) {
      //     begin = mid + 1;
      //   } else {
      //     end = mid - 1;
      //   }
      // }
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