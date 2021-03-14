#include <assert.h>

#include <algorithm>
#include <cstdio>
#include <cstring>

const int max_str_len = 101;

int LCS3(char *str1, char *str2, char *str3, char **out_substr) {
  int l1 = strlen(str1), l2 = strlen(str2), l3 = strlen(str3);
  char *dp1 = new char[(l1 + 1) * (l2 + 1) * (l3 + 1)];
  char **dp2 = new char *[(l1 + 1) * (l2 + 1)];
  char ***dp = new char **[l1 + 1];
  for (int i = 0; i < (l1 + 1) * (l2 + 1); i++) dp2[i] = dp1 + i * (l3 + 1);
  for (int i = 0; i < l1 + 1; i++) dp[i] = dp2 + i * (l2 + 1);
  for (int i = 0; i < l1 + 1; i++) dp[i][0][0] = 0;
  for (int i = 0; i < l2 + 1; i++) dp[0][i][0] = 0;
  for (int i = 0; i < l3 + 1; i++) dp[0][0][i] = 0;
  for (int i = 1; i < l1 + 1; i++) {
    for (int j = 1; j < l2 + 1; j++) {
      for (int k = 1; k < l3 + 1; k++) {
        if (str1[i - 1] == str2[j - 1] && str2[j - 1] == str3[k - 1]) {
          dp[i][j][k] = dp[i - 1][j - 1][k - 1] + 1;
        } else {
          dp[i][j][k] = std::max(std::max(dp[i][j][k - 1], dp[i][j - 1][k]), dp[i - 1][j][k]);
        }
      }
    }
  }
  int substr_len = dp[l1][l2][l3];
  char *substr = new char[substr_len + 1];
  substr[substr_len] = '\0';
  int i = l1, j = l2, k = l3;
  for (int l = substr_len - 1; l >= 0;) {
    if (str1[i - 1] == str2[j - 1] && str1[i - 1] == str3[k - 1]) {
      //   assert(dp[i][j][k] == dp[i - 1][j - 1][k - 1] + 1);
      substr[l--] = str1[i - 1];
      i--;
      j--;
      k--;
    } else if (dp[i - 1][j][k] == dp[i][j][k]) {
      i--;
    } else if (dp[i][j - 1][k] == dp[i][j][k]) {
      j--;
    } else {
      //   assert(dp[i][j][k-1] == dp[i][j][k]);
      k--;
    }
  }
  delete[] dp;
  delete[] dp2;
  delete[] dp1;
  *out_substr = substr;
  return substr_len;
}

int main() {
  char *str1 = new char[max_str_len], *str2 = new char[max_str_len], *str3 = new char[max_str_len];
  scanf("%s", str1);
  scanf("%s", str2);
  scanf("%s", str3);
  char *substr = nullptr;
  int substr_len = LCS3(str1, str2, str3, &substr);
  printf("%s\n", substr);
  delete[] substr;
  delete[] str1;
  delete[] str2;
  delete[] str3;
  return 0;
}