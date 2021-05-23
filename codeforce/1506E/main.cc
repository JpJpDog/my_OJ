// Restoring the Permutation
// 1500
#include <cstdio>
#include <cstring>

const int kMaxN = 2 * 100000;
int q[kMaxN + 1];
int p[kMaxN + 1];
int next[kMaxN + 1];
int n;

void cal_max_p() {
  memset(next, 0, sizeof(int) * (n + 1));
  int max_limit = 0, the_max = 0;
  for (int i = 1; i <= n; i++) {
    if (q[i] > max_limit) {
      next[max_limit] = next[the_max] ? next[the_max] : the_max;
      max_limit = p[i] = q[i];
      the_max = q[i] - 1;
    } else {
      if (next[the_max]) {
        next[max_limit] = next[the_max] ? next[the_max] : the_max;
        the_max = next[the_max];
      }
      p[i] = the_max--;
    }
  }
}

void cal_min_p() {  // next used as a bitmap
  memset(next, 0, sizeof(int) * (n + 1));
  int max_limit = 0, the_min = 1;
  for (int i = 1; i <= n; i++) {
    if (q[i] > max_limit) {
      max_limit = p[i] = q[i];
    } else {
      while (next[the_min]) {
        the_min++;
      }
      p[i] = the_min++;
    }
    next[p[i]] = 1;
  }
}

void print() {
  printf("%d", p[1]);
  for (int i = 2; i <= n; i++) {
    printf(" %d", p[i]);
  }
  printf("\n");
}

int main() {
  int test_n;
  scanf("%d", &test_n);
  for (int i = 0; i < test_n; i++) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%d", q + i);
    }
    cal_min_p();
    print();
    cal_max_p();
    print();
  }
}
