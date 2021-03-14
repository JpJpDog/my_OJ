#include <cstdio>
#include <vector>

template <typename T>
class MinHeap {
  std::vector<T> datas_;
  inline int lchild(int p) { return (p << 1) + 1; }
  inline int rchild(int p) { return (p << 1) + 2; }
  inline int parent(int c) { return (c + 1 >> 1) - 1; }
  void go_down(int i, T const &tmp) {
    int data_size = datas_.size();
    while (true) {
      int li = lchild(i), ri = rchild(i);
      bool l = li >= data_size || tmp < datas_[li], r = ri >= data_size || tmp < datas_[ri];
      if (l && r) {
        break;
      } else if (l) {
        datas_[i] = datas_[ri];
        i = ri;
      } else if (r) {
        datas_[i] = datas_[li];
        i = li;
      } else if (datas_[ri] < datas_[li]) {
        datas_[i] = datas_[ri];
        i = ri;
      } else {
        datas_[i] = datas_[li];
        i = li;
      }
    }
    datas_[i] = tmp;
  }

 public:
  MinHeap() {}
  MinHeap(const std::vector<T> &datas) : datas_(datas) {
    int data_size = datas.size();
    for (int i = (data_size - 1) / 2; i >= 0; i--) {
      go_down(i, datas[i]);
    }
  }
  MinHeap(const MinHeap &other) : datas_(other.datas_) {}
  MinHeap &operator=(const MinHeap &other) { this->datas_ = other.datas_; }
  void push(const T &data) {
    datas_.push_back(data);
    int last_i = datas_.size() - 1;
    int i = last_i;
    while (i) {
      int pi = parent(i);
      if (data < datas_[pi]) {
        datas_[i] = datas_[pi];
        i = pi;
      } else {
        break;
      }
      if (i != last_i) {
        datas_[i] = data;
      }
    }
  }
  void pop() {
    T tmp = datas_[datas_.size() - 1];
    datas_.pop_back();
    go_down(0, tmp);
  }
  T top() { return datas_[0]; }
  inline bool is_empty() { return datas_.empty(); }
};

int main() {
  struct Operation {
    int type_, x_;
  };
  int n;
  scanf("%d", &n);
  Operation *ops = new Operation[n];
  for (int i = 0; i < n; i++) {
    scanf("%d", &(ops[i].type_));
    if (ops[i].type_ == 1) scanf("%d", &(ops[i].x_));
  }
  MinHeap<int> heap;
  for (int i = 0; i < n; i++) {
    if (ops[i].type_ == 1) {
      heap.push(ops[i].x_);
    } else if (ops[i].type_ == 2) {
      printf("%d\n", heap.top());
    } else {
      heap.pop();
    }
  }
  return 0;
}