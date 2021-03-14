#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  int a, b;
  scanf("%d %d", &a, &b);
  int sum = a + b;
  bool minus = 0;
  if (sum < 0) {
    sum = -sum;
    minus = 1;
  }
  int arr[3], arrlen = 0;
  while (sum) {
    arr[arrlen] = sum % 1000;
    sum /= 1000;
    arrlen++;
  }
  if (minus) {
    printf("-");
  }
  switch (arrlen) {
    case 0:
      printf("0\n");
      break;
    case 1:
      printf("%d\n", arr[0]);
      break;
    case 2:
      printf("%d,%03d\n", arr[1], arr[0]);
      break;
    case 3:
      printf("%d,%03d,%03d\n", arr[2], arr[1], arr[0]);
  }
  return 0;
}