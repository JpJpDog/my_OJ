// Restoring the Permutation
// 1500
#include <cstdio>
#include <cstring>

const int kMaxN = 2 * 100000;
int q[kMaxN + 1];
int p[kMaxN + 1];
bool p_map[kMaxN + 1];
int n;

int min_last;

int max_last;

void init() {
  memset(p_map + 1, 0, n);
  min_last = 1;
  max_last = 0; // init by q[0]
}

int min_choose() {
  while (p_map[min_last]) {
    min_last++;
  }
  return min_last++;
}

int max_choose() {
  while (p_map[max_last]) {
    max_last--;
  }
  return max_last--;
}

void cal_p(int (*choose)()) {
  init();
  int last = -1;
  for (int i = 1; i <= n; i++) {
    if (q[i] > last) {
      last = p[i] = q[i];
      max_last = q[i] - 1;
    } else {
      p[i] = choose();
    }
    p_map[p[i]] = 1;
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
    cal_p(min_choose);
    print();
    cal_p(max_choose);
    print();
  }
}
