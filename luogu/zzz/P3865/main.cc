#include <algorithm>
#include <cstdio>

int N, M;

const int kMaxN = 100000;
const int kMaxM = 2000000;
const int kMaxLogN = 16;

int arr[kMaxN + 1];

// st[i][j] is the max in [i,i+2^j-1]
int st[kMaxN + 1][kMaxLogN + 1];

void st_init() {
  for (int i = 1; i <= N; i++) {
    st[i][0] = arr[i];
  }
  for (int j = 1; j <= kMaxLogN; j++) {
    const int len = 1 << j;
    if (len > N) break;
    for (int i = 1; i + len - 1 <= N; i++) {
      st[i][j] = std::max(st[i][j - 1], st[i + (len >> 1)][j - 1]);
    }
  }
}

inline int log2_integer(int x) {
  int result = 0;
  while (x >>= 1) result++;
  return result;
}

inline int st_find(const int l, const int r) {
  const int len = r - l + 1;
  const int log_len = log2_integer(len);
  return std::max(st[l][log_len], st[r - (1 << log_len) + 1][log_len]);
}

int main() {
  scanf("%d %d", &N, &M);
  for (int i = 1; i <= N; i++) {
    scanf("%d", arr + i);
  }
  st_init();
  for (int i = 0; i < M; i++) {
    int l, r;
    scanf("%d %d", &l, &r);
    printf("%d\n", st_find(l, r));
  }
}