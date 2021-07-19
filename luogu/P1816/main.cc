#include <algorithm>
#include <cmath>
#include <cstdio>

class RMQ {
 private:
  int len_, range_;
  int* dp_;
  inline int get_dp(int i, int j) { return dp_[range_ * i + j]; }
  inline void set_dp(int i, int j, int value) { dp_[range_ * i + j] = value; }

 public:
  RMQ(int* arr, int len) : len_(len), range_(int(ceil(log2(len)))), dp_(new int[len * range_]) {
    for (int i = 0; i < len_; i++) {
      set_dp(i, 0, arr[i]);
    }
    for (int j = 1; j < range_; j++) {
      for (int i = 0; i <= len_ - (1 << j); i++) {
        set_dp(i, j, std::min(get_dp(i, j - 1), get_dp(i + (1 << j - 1), j - 1)));
      }
    }
  }
  ~RMQ() { delete[] dp_; }
  int query(int a, int b) {
    int r = int(floor(log2(b - a + 1)));
    return std::min(get_dp(a, r), get_dp(b - (1 << r) + 1, r));
  }
};

int main() {
  int M, N;
  scanf("%d %d", &M, &N);
  int* arr = new int[M];
  int *a = new int[N], *b = new int[N];
  for (int i = 0; i < M; i++) {
    scanf("%d", arr + i);
  }
  for (int i = 0; i < N; i++) {
    scanf("%d %d", a + i, b + i);
  }
  RMQ rmq(arr, M);
  for (int i = 0; i < N; i++) {
    printf("%d ", rmq.query(a[i] - 1, b[i] - 1));
  }
  delete[] a;
  delete[] b;
  delete[] arr;
  return 0;
}
