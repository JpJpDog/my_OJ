#include <cstdio>
#include <stack>

class DisjointSet {
  struct Set {
    int parent_;
    int rank_;
  };
  Set* sets_;
  int max_index_;

 public:
  DisjointSet(int max_i) : sets_(new Set[max_i + 1]), max_index_(max_i) {
    for (int i = 0; i <= max_i; i++) {
      sets_[i].parent_ = i;
      sets_[i].rank_ = 1;
    }
  }
  ~DisjointSet() { delete[] sets_; }
  int find(int i) {
    std::stack<int> st;
    while (sets_[i].parent_ != i) {
      st.push(i);
      i = sets_[i].parent_;
    }
    while (!st.empty()) {
      sets_[st.top()].parent_ = i;
      st.pop();
    }
    return i;
  }
  void merge(int a, int b) {
    int p1 = find(a), p2 = find(b);
    if (sets_[p1].rank_ <= sets_[p2].rank_) {
      sets_[p1].parent_ = p2;
    } else {
      sets_[p2].parent_ = p1;
    }
    if (sets_[p1].rank_ == sets_[p2].rank_ && p1 != p2) {
      sets_[p2].rank_++;
    }
  }
};

int main() {
  struct Operation {
    int type_, x_, y_;
  };
  int N, M;
  scanf("%d %d", &N, &M);
  DisjointSet set(N);
  Operation* ops = new Operation[M];
  for (int i = 0; i < M; i++) {
    scanf("%d %d %d", &(ops[i].type_), &(ops[i].x_), &(ops[i].y_));
  }
  for (int i = 0; i < M; i++) {
    if (ops[i].type_ == 1) {
      set.merge(ops[i].x_, ops[i].y_);
    } else {
      if (set.find(ops[i].x_) == set.find(ops[i].y_)) {
        printf("Y\n");
      } else {
        printf("N\n");
      }
    }
  }
  delete[] ops;
}