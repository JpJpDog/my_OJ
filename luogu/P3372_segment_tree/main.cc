#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <stack>

typedef long long LL;

template <typename T>
class SegmentTree {
  struct SegmentCell {
    T value_;
    T lazy_add_;
    SegmentCell() : lazy_add_(0) {}
    SegmentCell(T v) : value_(v), lazy_add_(0) {}
  };
  struct Record {
    int index_, start_, end_;
    Record(int i, int s, int e) : index_(i), start_(s), end_(e) {}
  };
  struct Record1 {
    int time_, index_, start_, end_;
    Record1(int i, int s, int e) : time_(0), index_(i), start_(s), end_(e) {}
  };
  SegmentCell *tree_;
  int tree_len_, arr_len_;
  int ceil_2power(int a) {
    int r = 1;
    while (a > r) {
      r <<= 1;
    }
    return r;
  }
  inline int lchild(int p) { return p << 1; }
  inline int rchild(int p) { return (p << 1) | 1; }
  inline void pushdown(int idx, int l_range, int r_range) {
    T add = tree_[idx].lazy_add_;
    tree_[lchild(idx)].lazy_add_ += add;
    tree_[lchild(idx)].value_ += add * l_range;
    tree_[rchild(idx)].lazy_add_ += add;
    tree_[rchild(idx)].value_ += add * r_range;
    tree_[idx].lazy_add_ = 0;
  }
  //   void debug_print_r(int idx, int s, int e) {
  //     printf("%d (%d %d %d %d)\n", idx, s, e, tree_[idx].value_, tree_[idx].lazy_add_);
  //     if (s != e) {
  //       int m = (s + e) >> 1;
  //       debug_print_r(lchild(idx), s, m);
  //       debug_print_r(rchild(idx), m + 1, e);
  //     }
  //   }

 public:
  SegmentTree(T *arr, int len) : tree_len_((ceil_2power(len) << 1)), arr_len_(len) {
    tree_ = new SegmentCell[tree_len_];
    std::stack<Record1> st;
    st.push(Record1(1, 0, arr_len_ - 1));
    while (!st.empty()) {
      auto &top = st.top();
      if (top.time_ == 0) {
        int mid = (top.start_ + top.end_) >> 1, ci = lchild(top.index_);
        if (mid > top.start_) {
          st.push(Record1(ci, top.start_, mid));
        } else {
          tree_[ci] = SegmentCell(arr[mid]);
        }
        top.time_++;
      } else if (top.time_ == 1) {
        int mid = (top.start_ + top.end_) >> 1, ci = rchild(top.index_);
        if (mid + 1 < top.end_) {
          st.push(Record1(ci, mid + 1, top.end_));
        } else {
          tree_[ci] = SegmentCell(arr[mid + 1]);
        }
        top.time_++;
      } else {
        int pi = top.index_;
        tree_[pi] = SegmentCell(tree_[lchild(pi)].value_ + tree_[rchild(pi)].value_);
        st.pop();
      }
    }
  }
  ~SegmentTree() { delete[] tree_; }
  void range_add(int start, int end, T k) {
    if (k == 0) return;
    std::stack<Record> st;
    st.push(Record(1, 0, arr_len_ - 1));
    while (!st.empty()) {
      auto &top = st.top();
      int s = top.start_, e = top.end_, m = (top.start_ + top.end_) >> 1, idx = top.index_;
      auto &cur = tree_[idx];
      st.pop();
      if (start <= s && end >= e) {
        cur.value_ += (e - s + 1) * k;
        if (s != e) {
          cur.lazy_add_ += k;
        }
      } else {
        if (tree_[idx].lazy_add_ != 0) {
          pushdown(idx, m - s + 1, e - m);
        }
        if (start <= m) {
          st.push(Record(lchild(idx), s, m));
        }
        if (end >= m + 1) {
          st.push(Record(rchild(idx), m + 1, e));
        }
        cur.value_ += k * (std::min(e, end) - std::max(s, start) + 1);
      }
    }
  }
  T range_sum(int start, int end) {
    T sum = 0;
    std::stack<Record> st;
    st.push(Record(1, 0, arr_len_ - 1));
    while (!st.empty()) {
      auto &top = st.top();
      int s = top.start_, e = top.end_, m = (top.start_ + top.end_) >> 1, idx = top.index_;
      st.pop();
      auto &cur = tree_[idx];
      if (start <= s && end >= e) {
        sum += cur.value_;
      } else {
        if (tree_[idx].lazy_add_ != 0) {
          pushdown(idx, m - s + 1, e - m);
        }
        if (start <= m) {
          st.push(Record(lchild(idx), s, m));
        }
        if (end >= m + 1) {
          st.push(Record(rchild(idx), m + 1, e));
        }
      }
    }
    return sum;
  }
  //   void debug_print() { debug_print_r(1, 0, arr_len_ - 1); }
};

int main() {
  struct Operation {
    int op_, s_, e_;
    LL k_;
    Operation() {}
    Operation(int op, int s, int e, LL k) : op_(op), s_(s), e_(e), k_(k) {}
  };
  int n, m;
  scanf("%d %d", &n, &m);
  LL *arr = new LL[n];
  Operation *ops = new Operation[m];
  for (int i = 0; i < n; i++) {
    scanf("%lld", arr + i);
  }
  for (int i = 0; i < m; i++) {
    int op, s, e;
    LL k = 0;
    scanf("%d", &op);
    if (op == 1) {
      scanf("%d %d %lld", &s, &e, &k);
    } else {
      scanf("%d %d", &s, &e);
    }
    ops[i] = Operation(op, s, e, k);
  }
  SegmentTree<LL> tree(arr, n);
  for (int i = 0; i < m; i++) {
    auto &op = ops[i];
    if (op.op_ == 1) {
      tree.range_add(op.s_ - 1, op.e_ - 1, op.k_);
    } else {
      printf("%lld", tree.range_sum(op.s_ - 1, op.e_ - 1));
      if (i != m - 1) {
        printf("\n");
      }
    }
  }
  delete[] arr;
  delete[] ops;
  return 0;
}
