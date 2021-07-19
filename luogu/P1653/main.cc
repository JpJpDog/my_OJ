#include <algorithm>
#include <cstdio>
#include <stack>
#include <vector>

class DisjointSet {
  int max_n_;
  struct SetEle {
    int parent_;
    int rank_;
    int tail_;
  };
  std::vector<int> group_;
  std::vector<SetEle> data_;

 public:
  DisjointSet(int max_n) : max_n_(max_n), data_(max_n), group_(max_n) {
    for (int i = 0; i < max_n_; i++) {
      data_[i].parent_ = i;
      data_[i].rank_ = 1;
      data_[i].tail_ = i;
      group_[i] = -1;
    }
  }
  int get_parent(int idx) {
    std::stack<int> st;
    while (idx != data_[idx].parent_) {
      st.push(idx);
      idx = data_[idx].parent_;
    }
    while (!st.empty()) {
      data_[st.top()].parent_ = idx;
      st.pop();
    }
    return idx;
  }
  void merge(int a, int b) {
    int pa = get_parent(a), pb = get_parent(b);
    int high = pb, low = pa;
    if (data_[pa].rank_ > data_[pb].rank_) {
      std::swap(high, low);
    }
    data_[low].parent_ = high;
    group_[data_[high].tail_] = low;
    data_[high].tail_ = data_[low].tail_;
    if (data_[pa].rank_ == data_[pb].rank_ && pa != pb) {
      data_[high].rank_++;
    }
  }
  class Iterator {
    int p_;
    DisjointSet &set_;

   public:
    Iterator(DisjointSet &set, int p) : set_(set), p_(set.get_parent(p)) {}
    int inline get_next() {
      if (p_ == -1) return -1;
      int old_p = p_;
      p_ = set_.group_[p_];
      return old_p;
    }
  };
};

struct Node {
  int l_, r_;
};

struct Release {
  int p_, ch_;
};

int main() {
  int N, M;
  scanf("%d %d", &N, &M);
  static std::vector<bool> fallen(N + 1, true);
  static std::vector<int> result(N + 1);
  fallen.resize(N + 1, true);
  result.resize(N + 1, -1);
  std::vector<Node> nodes(N + 1);
  std::vector<Release> releases(M);
  DisjointSet set(N + 1);
  for (int i = 1; i <= N; i++) {
    int l, r;
    scanf("%d %d", &l, &r);
    nodes[i].l_ = l;
    nodes[i].r_ = r;
  }
  for (int i = 0; i < M; i++) {
    int idx, h;
    int pa = get_parent(a), pb = get_parent(b);
    int high = pb, low = pa;
    if (data_[pa].rank_ > data_[pb].rank_) {
      std::swap(high, low);
    scanf("%d %d", &idx, &h);
    releases[i].p_ = idx;
    if (h == 1) {
      releases[i].ch_ = nodes[idx].l_;
      nodes[idx].l_ = -1;
    } else {
      releases[i].ch_ = nodes[idx].r_;
      nodes[idx].r_ = -1;
    }
  }

  for (int i = 1; i <= N; i++) {
    if (nodes[i].l_ != -1) {
      set.merge(i, nodes[i].l_);
    }
    if (nodes[i].r_ != -1) {
      set.merge(i, nodes[i].r_);
    }
  }
  std::stack<int> st;
  std::vector<bool> visited(N + 1, false);
  st.push(1);
  visited[1] = true;
  while (!st.empty()) {
    Node &n = nodes[st.top()];
    if (n.l_ != -1 && !visited[n.l_]) {
      visited[n.l_] = true;
      st.push(n.l_);
    }
    if (n.r_ != -1 && !visited[n.r_]) {
      visited[n.r_] = true;
      st.push(n.r_);
    }
    result[st.top()] = -1;
    fallen[st.top()] = false;
    st.pop();
  }
  for (int i = M - 1; i >= 0; i--) {
    Release &r = releases[i];
    bool fall_ch = fallen[r.ch_], fall_p = fallen[r.p_];
    if (!fall_ch && !fall_p) continue;
    if (fall_ch ^ fall_p) {
      int low, cur;
      low = fall_p ? r.p_ : r.ch_;
      DisjointSet::Iterator iter(set, low);
      while ((cur = iter.get_next()) != -1) {
        result[cur] = i;
        fallen[cur] = false;
      }
    }
    set.merge(r.ch_, r.p_);
  }
  for (int i = 1; i <= N; i++) {
    printf("%d\n", result[i]);
  }
}
