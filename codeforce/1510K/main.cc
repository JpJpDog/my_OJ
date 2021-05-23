// king's task
// 1200

#include <cstdio>
#include <cstring>

const int kMaxN = 1000;

int n;
int p[kMaxN * 2];
int q[kMaxN * 2];

static inline void swap(int i, int j) {
  int tmp = p[i];
  p[i] = p[j];
  p[j] = tmp;
}

void op1() {
  for (int i = 0; i < 2 * n; i += 2) {
    swap(i, i + 1);
  }
}

void op2() {
  for (int i = 0; i < n; i++) {
    swap(i, n + i);
  }
}

static inline bool check() {
  for (int i = 0; i < 2 * n; i++) {
    if (p[i] != i + 1) {
      return false;
    }
  }
  return true;
}

int main() {
  scanf("%d", &n);
  for (int i = 0; i < 2 * n; i++) {
    scanf("%d", p + i);
  }
  memcpy(q, p, sizeof(int) * 2 * n);
  int step_n;
  if (check()) {
    step_n = 0;
  } else {
    int test_n = 2;
    if (n % 2) {
      test_n = n;
    }
    int step_n1 = -1;
    for (int i = 0; i < test_n; i++) {
      op1();
      if (check()) {
        step_n1 = 2 * i + 1;
        break;
      }
      op2();
      if (check()) {
        step_n1 = 2 * i + 2;
        break;
      }
    }
    int step_n2 = -1;
    memcpy(p, q, sizeof(int) * 2 * n);
    for (int i = 0; i < test_n; i++) {
      op2();
      if (check()) {
        step_n2 = 2 * i + 1;
        break;
      }
      op1();
      if (check()) {
        step_n2 = 2 * i + 2;
        break;
      }
    }
    if (step_n1 == -1 && step_n2 == -1) {
      step_n = -1;
    } else if (step_n1 == -1) {
      step_n = step_n2;
    } else if (step_n2 == -1) {
      step_n = step_n1;
    } else {
      step_n = step_n1 > step_n2 ? step_n2 : step_n1;
    }
  }
  printf("%d\n", step_n);
}
