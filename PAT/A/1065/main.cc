#include <cstdio>
typedef long long LL;

int main() {
  int T;
  scanf("%d", &T);
  LL a[T], b[T], c[T];
  char s1[] = "true", s2[] = "false", *s;
  for (int i = 0; i < T; i++) {
    scanf("%lld %lld %lld", a + i, b + i, c + i);
  }
  for (int i = 0; i < T; i++) {
    LL sum = a[i] + b[i];
    if (a[i] > 0 && b[i] > 0 && sum <= 0) {
      s = s1;
    } else if (a[i] < 0 && b[i] < 0 && sum >= 0) {
      s = s2;
    } else {
      s = sum > c[i] ? s1 : s2;
    }
    printf("Case #%d: %s\n", i + 1, s);
  }

  return 0;
}