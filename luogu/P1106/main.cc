// from i=0, the first time str[i]>str[i+1] (i+1<str_len) then delete str[i] is
// the best choice for deleting one number.
// prove: if delete str[i+1] or after the ith number in result is str[i], but if
// delete str[i], the ith number is str[i+1] which is less and all before is the
// same. if delete str[i-1] or before, let say it is str[j]. then delete str[j]
// will get bigger result than delete str[j+1] for delete str[j] remains the
// bigger jth number.
// so if delete k number, after delete str[i], just continue starting from
// comparing str[i-1] and str[i+1](str[i] is deleted) and go on because all
// before numbers are not decreasing.
// if we reach end (i+1==str_len-1) before deleting k number, then all numbers
// are not decreasing, so delete from the end.

#include <cstdio>
#include <cstring>
#include <vector>

const int max_str_len = 250;

char str[max_str_len + 1];
char result[max_str_len + 1];

int main() {
  scanf("%s", str);
  int str_len = strlen(str);
  std::vector<bool> deleted(str_len, false);
  int k;
  scanf("%d", &k);
  int i = 0, j = 1;
  while (j < str_len) {
    if (str[i] > str[j]) {
      deleted[i] = true;
      if (!(--k)) break;
      while (--i >= 0 && deleted[i])
        ;
      if (i < 0) {
        i = j;
        j++;
      }
    } else {
      i = j;
      j++;
    }
  }
  for (int i = str_len - 1; i >= 0, k; i--) {
    if (!deleted[i]) {
      deleted[i] = true;
      k--;
    }
  }
  int result_i = 0;
  bool start = true;
  for (int i = 0; i < str_len; i++) {
    if (!deleted[i]) {
      if (start && str[i] == '0') {
        continue;
      }
      start = false;
      result[result_i++] = str[i];
    }
  }
  if (!result_i) result[result_i++] = '0';
  result[result_i] = '\0';
  printf("%s\n", result);
  return 0;
}