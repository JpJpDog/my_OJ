#include <cstdio>

void print_in_english(int x, bool space = false) {
  int digit = x % 10;
  int y = x / 10;
  if (y) {
    print_in_english(y, true);
  }
  switch (digit) {
    case 0:
      printf("zero");
      break;
    case 1:
      printf("one");
      break;
    case 2:
      printf("two");
      break;
    case 3:
      printf("three");
      break;
    case 4:
      printf("four");
      break;
    case 5:
      printf("five");
      break;
    case 6:
      printf("six");
      break;
    case 7:
      printf("seven");
      break;
    case 8:
      printf("eight");
      break;
    default:
      printf("nine");
      break;
  }
  if (space) {
    printf(" ");
  }
}

#define MAX_LEN 105
char buf[MAX_LEN];

int main() {
  scanf("%s", buf);
  int sum = 0, i = 0;
  while (buf[i] != '\0') {
    sum += buf[i] - '0';
    i++;
  }
  print_in_english(sum);
  printf("\n");
}