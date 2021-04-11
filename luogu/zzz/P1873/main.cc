#include <algorithm>
#include <cstdio>

int N, M;

const int kMaxN = 1000000;
int tree[kMaxN];

typedef long long LL;

int check(int h) {
  LL sum = 0;
  for (int i = 0; i < N; i++) {
    if (tree[i] > h) {
      sum += tree[i] - h;
    }
  }
  if (sum < M) return 0;
  if (sum > M) return 1;
  return 2;
}

int main() {
  scanf("%d %d", &N, &M);
  for (int i = 0; i < N; i++) {
    scanf("%d", tree + i);
  }
  int max_h = *std::max_element(tree, tree + N);
  int low = 0, high = max_h;
  // the answer is non increasing find the last >= M
  // in every iteration, possible answer is in [low-1, high]
  // in last iteration, low==high+1, so answer is high
  int result = -1;
  while (low <= high) {
    int mid = (low + high) / 2;
    int ck = check(mid);
    if (ck == 2) {
      result = mid;
      break;
    }
    if (ck) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }
  if (result == -1) result = high;
  printf("%d\n", result);
}