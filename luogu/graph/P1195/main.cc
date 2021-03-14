#include <algorithm>
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

struct Edge {
  int v1_, v2_, e_;
  Edge() {}
  Edge(int v1, int v2, int e) : v1_(v1), v2_(v2), e_(e) {}
};

bool compare(const Edge& e1, const Edge& e2) { return e1.e_ < e2.e_; }

int main() {
  int N, M, K;
  scanf("%d %d %d", &N, &M, &K);
  int result = 0;
  bool flag = true;
  Edge* edges = new Edge[M];
  for (int i = 0; i < M; i++) {
    scanf("%d %d %d", &edges[i].v1_, &edges[i].v2_, &edges[i].e_);
  }
  std::sort(edges, edges + M, compare);
  DisjointSet set(N + 1);
  int ei = 0;
  for (int i = 0; i < N - K; i++) {
    for (; ei < M && set.find(edges[ei].v1_) == set.find(edges[ei].v2_); ei++)
      ;
    if (ei == M) {
      flag = false;
      break;
    }
    set.merge(edges[ei].v1_, edges[ei].v2_);
    result += edges[ei].e_;
    ei++;
  }
  if (flag) {
    printf("%d\n", result);
  } else {
    printf("No Answer\n");
  }
}
