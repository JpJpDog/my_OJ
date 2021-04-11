#include <cstdio>
#include <vector>

#define CEIL_DIV(a, b) (((a)-1) / (b) + 1)
#define MAGIC_DIST 60
#define WALK_DIST 17
#define MAGIC_COST 10
#define MAGIC_RECOVER 4

int main() {
  int M, S, T;
  scanf("%d %d %d", &M, &S, &T);
  int s = 0, m = M, t = 0, stop_t, walk_t;
  while (s < S && t < T) {
    if (s == 6660) {
      int aaa = 1;
    }
    if (m >= MAGIC_COST) {
      s += MAGIC_DIST;
      m -= MAGIC_COST;
      t++;
    } else {
      stop_t = CEIL_DIV(MAGIC_COST - m, MAGIC_RECOVER);
      if (stop_t * WALK_DIST + s < S && stop_t + t < T) {
        t += stop_t;
        m += MAGIC_RECOVER * stop_t;
      } else {
        if (stop_t + t >= T) {
          walk_t = T - t;
        } else {
          walk_t = CEIL_DIV(S - s, WALK_DIST);
        }
        t += walk_t;
        s += WALK_DIST * walk_t;
      }
    }
  }
  if (s >= S) {
    printf("Yes\n%d\n", t);
  } else {
    printf("No\n%d\n", s);
  }
}