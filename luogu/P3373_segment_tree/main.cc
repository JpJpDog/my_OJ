#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <stack>

typedef long long LL;

template <typename T>
class SegmentTree {
  struct SegmentCell {
    T value_, lazy_add_, lazy_multi_;
    SegmentCell() : lazy_add_(0), lazy_multi_(1) {}
    SegmentCell(T v) : value_(v), lazy_add_(0), lazy_multi_(1) {}
  };
  struct Record {
    int time_, index_, start_, end_;
    Record(int i, int s, int e) : time_(0), index_(i), start_(s), end_(e) {}
  };
  SegmentCell *tree_;
  int tree_len_, arr_len_;
  T p_;
  int ceil_2power(int a) {
    int r = 1;
    while (a > r) r <<= 1;
    return r;
  }
  inline int lchild(int p) { return p << 1; }
  inline int rchild(int p) { return (p << 1) | 1; }
  void pushdown(int idx, int s, int e) {
    auto &p = tree_[idx], &lc = tree_[lchild(idx)], &rc = tree_[rchild(idx)];
    T add = p.lazy_add_, multi = p.lazy_multi_;
    p.lazy_add_ = 0;
    p.lazy_multi_ = 1;
    int m = (s + e) >> 1;
    if (s != m) {
      lc.lazy_multi_ = lc.lazy_multi_ * multi % p_;
      lc.lazy_add_ = (lc.lazy_add_ * multi + add) % p_;
    }
    lc.value_ = (lc.value_ * multi + add * (m - s + 1)) % p_;
    if (m + 1 != e) {
      rc.lazy_multi_ = rc.lazy_multi_ * multi % p_;
      rc.lazy_add_ = (rc.lazy_add_ * multi + add) % p_;
    }
    rc.value_ = (rc.value_ * multi + add * (e - m)) % p_;
  }
  void debug_print_r(int idx, int s, int e) {
    printf("%d (%d %d %d %d %d)\n", idx, s, e, tree_[idx].value_, tree_[idx].lazy_add_, tree_[idx].lazy_multi_);
    if (s != e) {
      int m = (s + e) >> 1;
      debug_print_r(lchild(idx), s, m);
      debug_print_r(rchild(idx), m + 1, e);
    }
  }

 public:
  SegmentTree(T *arr, int len, T p) : tree_len_((ceil_2power(len) << 1)), arr_len_(len), p_(p) {
    tree_ = new SegmentCell[tree_len_];
    std::stack<Record> st;
    st.push(Record(1, 0, arr_len_ - 1));
    while (!st.empty()) {
      auto &top = st.top();
      if (top.time_ == 0) {
        int s = top.start_, e = top.end_, m = (top.start_ + top.end_) >> 1, idx = top.index_;
        int lci = lchild(idx), rci = rchild(idx);
        if (m + 1 < e) {
          st.push(Record(rci, m + 1, e));
        } else {
          tree_[rci] = SegmentCell((arr[m + 1]) % p_);
        }
        if (m > s) {
          st.push(Record(lci, s, m));
        } else {
          tree_[lci] = SegmentCell((arr[m]) % p_);
        }
        top.time_ += 2;
      } else {
        int pi = top.index_;
        tree_[pi] = SegmentCell((tree_[lchild(pi)].value_ + tree_[rchild(pi)].value_) % p_);
        st.pop();
      }
    }
  }
  ~SegmentTree() { delete[] tree_; }
  T range_sum(int start, int end) {
    T sum = 0;
    std::stack<Record> st;
    st.push(Record(1, 0, arr_len_ - 1));
    while (!st.empty()) {
      auto &top = st.top();
      int s = top.start_, e = top.end_, m = (top.start_ + top.end_) >> 1, idx = top.index_;
      auto &cur = tree_[idx];
      st.pop();
      if (start <= s && end >= e) {
        sum = (sum + cur.value_) % p_;
      } else {
        pushdown(idx, s, e);
        if (start <= m) st.push(Record(lchild(idx), s, m));
        if (end >= m + 1) st.push(Record(rchild(idx), m + 1, e));
      }
    }
    return sum;
  }
  void range_add(int start, int end, T k) {
    if (k == 0) return;
    std::stack<Record> st;
    st.push(Record(1, 0, arr_len_ - 1));
    while (!st.empty()) {
      auto &top = st.top();
      int s = top.start_, e = top.end_, m = (top.start_ + top.end_) >> 1, idx = top.index_;
      auto &cur = tree_[idx];
      if (top.time_ == 0) {
        if (start <= s && end >= e) {
          cur.value_ = (cur.value_ + (e - s + 1) * k) % p_;
          if (s != e) cur.lazy_add_ = (cur.lazy_add_ + k) % p_;
          st.pop();
        } else {
          pushdown(idx, s, e);
          if (start <= m) st.push(Record(lchild(idx), s, m));
          if (end >= m + 1) st.push(Record(rchild(idx), m + 1, e));
          top.time_ += 2;
        }
      } else {
        cur.value_ = (tree_[lchild(idx)].value_ + tree_[rchild(idx)].value_) % p_;
        st.pop();
      }
    }
  }
  void range_multi(int start, int end, T k) {
    if (k == 1) return;
    std::stack<Record> st;
    st.push(Record(1, 0, arr_len_ - 1));
    while (!st.empty()) {
      auto &top = st.top();
      int s = top.start_, e = top.end_, m = (top.start_ + top.end_) >> 1, idx = top.index_;
      auto &cur = tree_[idx];
      if (top.time_ == 0) {
        if (start <= s && end >= e) {
          cur.value_ = cur.value_ * k % p_;
          if (s != e) {
            cur.lazy_add_ = cur.lazy_add_ * k % p_;
            cur.lazy_multi_ = cur.lazy_multi_ * k % p_;
          }
          st.pop();
        } else {
          pushdown(idx, s, e);
          if (start <= m) st.push(Record(lchild(idx), s, m));
          if (end >= m + 1) st.push(Record(rchild(idx), m + 1, e));
          top.time_ += 2;
        }
      } else {
        cur.value_ = (tree_[lchild(idx)].value_ + tree_[rchild(idx)].value_) % p_;
        st.pop();
      }
    }
  }
  void debug_print() { debug_print_r(1, 0, arr_len_ - 1); }
};

int main() {
  struct Operation {
    int op_, s_, e_;
    LL k_;
    Operation() {}
    Operation(int op, int s, int e, LL k) : op_(op), s_(s), e_(e), k_(k) {}
  };
  int n, m, p;
  scanf("%d %d %d", &n, &m, &p);
  LL *arr = new LL[n];
  Operation *ops = new Operation[m];
  for (int i = 0; i < n; i++) scanf("%lld", arr + i);
  for (int i = 0; i < m; i++) {
    int op, s, e;
    LL k = 0;
    scanf("%d", &op);
    if (op != 3) {
      scanf("%d %d %lld", &s, &e, &k);
    } else {
      scanf("%d %d", &s, &e);
    }
    ops[i] = Operation(op, s, e, k);
  }
  SegmentTree<LL> tree(arr, n, p);
  for (int i = 0; i < m; i++) {
    auto &op = ops[i];
    switch (op.op_) {
      case 1:
        tree.range_multi(op.s_ - 1, op.e_ - 1, op.k_);
        break;
      case 2:
        tree.range_add(op.s_ - 1, op.e_ - 1, op.k_);
        break;
      default:
        printf("%lld", tree.range_sum(op.s_ - 1, op.e_ - 1));
        if (i != m - 1) printf("\n");
    }
  }
  delete[] arr;
  delete[] ops;
  return 0;
}
