#include <cstdio>
#include <deque>
#include <vector>

struct MonotonousQueue {
  struct Record {
    int idx_;
    int v_;
    Record(int site, int v) : idx_(site), v_(v) {}
  };
  int k_;
  std::deque<Record> dq_;
  bool (*cmp_)(int, int);

  MonotonousQueue(int k, bool (*cmp)(int, int)) : k_(k), cmp_(cmp) {}
  void push(int val, int idx) {
    while (!dq_.empty() && cmp_(val, dq_.back().v_)) {
      dq_.pop_back();
    }
    dq_.push_back(Record(idx, val));
    if (idx - dq_.front().idx_ >= k_) {
      dq_.pop_front();
    }
  }
  inline int top() const { return dq_.front().v_; }
};

void print_vec(const std::vector<int> arr) {
  if (arr.empty()) {
    printf("\n");
    return;
  }
  printf("%d", arr[0]);
  for (int i = 1; i < arr.size(); i++) {
    printf(" %d", arr[i]);
  }
  printf("\n");
}

int main() {
  int n, k;
  scanf("%d %d", &n, &k);
  std::vector<int> arr(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &arr[i]);
  }
  std::vector<int> max_result(n - k + 1), min_result(n - k + 1);
  MonotonousQueue min_q(k, [](int a, int b) { return a <= b; });
  MonotonousQueue max_q(k, [](int a, int b) { return a >= b; });
  for (int i = 0; i < k; i++) {
    min_q.push(arr[i], i);
    max_q.push(arr[i], i);
  }
  max_result[0] = max_q.top();
  min_result[0] = min_q.top();
  for (int i = k; i < n; i++) {
    min_q.push(arr[i], i);
    max_q.push(arr[i], i);
    max_result[i - k + 1] = max_q.top();
    min_result[i - k + 1] = min_q.top();
  }
  print_vec(min_result);
  print_vec(max_result);
}