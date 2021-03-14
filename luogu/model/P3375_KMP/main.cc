#include <cstdio>
#include <cstring>

int *make_next(char *str, int len) {  // next[i] is the max len of common prefix and suffix of str[0..i]
  int *next = new int[len + 1];
  next++;
  next[-1] = -1;
  next[0] = 0;
  // at the beginning of the loop, k is the next element to compare with str[i]
  int i = 1, k = 0;
  while (i < len) {
    if (k < 0 || str[i] == str[k]) {
      next[i++] = ++k;
    } else {
      k = next[k - 1];
    }
  }
  return next;
}

void kmp(char *str1, char *str2, int *out_index_n, int **out_indexes, int *out_next_n, int **out_next) {
  int len1 = strlen(str1), len2 = strlen(str2);
  int *next = make_next(str2, len2), index_n = 0, *indexes = new int[len1 - len2];
  int i = 0, j = 0;
  while (i < len1) {
    if (j < 0 || str1[i] == str2[j]) {
      i++;
      j++;
      if (j == len2) {
        indexes[index_n++] = i - j + 1;
        j = next[j - 1];
      }
    } else {
      j = next[j - 1];
    }
  }
  *out_next = next;
  *out_next_n = len2;
  *out_indexes = indexes;
  *out_index_n = index_n;
}

const int kMaxStrLen = 1000001;

char s1[kMaxStrLen], s2[kMaxStrLen];

int main() {
  scanf("%s\n%s", s1, s2);
  int index_n, *indexes, next_n, *next;
  kmp(s1, s2, &index_n, &indexes, &next_n, &next);
  for (int i = 0; i < index_n; i++) {
    printf("%d\n", indexes[i]);
  }
  for (int i = 0; i < next_n; i++) {
    printf("%d ", next[i]);
  }
  delete[] indexes;
  delete[](next - 1);
}