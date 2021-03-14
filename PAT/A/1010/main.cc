#include <string.h>

#include <algorithm>
#include <cstdio>
#define MAX_DIGIT 15

inline int to_digit(char ch) {
  if (ch <= '9' && ch >= '0') {
    return ch - '0';
  }
  return ch - 'a' + 10;
}

inline long long to_number(char* ch, int radix) {
  long long sum = 0;
  int i = 0;
  while (ch[i] != '\0') {
    sum = sum * radix + to_digit(ch[i++]);
    if (sum < 0) {
      return -1;
    }
  }
  return sum;
}

inline long long to_number(int* arr, int len, int radix) {
  long long sum = 0;
  for (int i = 0; i < len; i++) {
    sum = sum * radix + arr[i];
    if (sum < 0) {
      return -1;
    }
  }
  return sum;
}

int main() {
  char c1[MAX_DIGIT], c2[MAX_DIGIT];
  int tag, radix1;
  scanf("%s %s %d %d", c1, c2, &tag, &radix1);
  char *ch1 = c1, *ch2 = c2;
  if (tag == 2) {
    std::swap(ch1, ch2);
  }
  long long n1 = to_number(ch1, radix1);
  int ch2_len = strlen(ch2);
  int arr2[ch2_len];
  int n2_max_digit = 1;
  for (int i = 0; i < ch2_len; i++) {
    int tmp = to_digit(ch2[i]);
    n2_max_digit = std::max(n2_max_digit, tmp);
    arr2[i] = tmp;
  }
  int radix = -1;
  long long n2 = -1;
  int min_radix = n2_max_digit + 1, max_radix = n1 + 1;
  while (min_radix <= max_radix) {
    radix = (min_radix + max_radix) / 2;
    n2 = to_number(arr2, ch2_len, radix);
    if (n2 > n1 || n2 == -1) {
      max_radix = radix - 1;
    } else if (n2 < n1) {
      min_radix = radix + 1;
    } else {
      break;
    }
  }
  if (n1 != n2) {
    printf("Impossible\n");
  } else {
    printf("%d\n", radix);
  }
  return 0;
}