#include <cstdio>
#include <cstring>
#include <stack>

struct Tree {
  struct Edge {
    int next_, v_;
  };
  int v_n_, e_top_, *vertices_;
  Edge *edges_;
  Tree(int v_n) : v_n_(v_n), e_top_(0), vertices_(new int[v_n]), edges_(new Edge[2 * (v_n - 1)]) {
    memset(vertices_, -1, sizeof(*vertices_) * v_n);
  }
  Tree(const Tree &t) : v_n_(t.v_n_), e_top_(t.e_top_), vertices_(new int[t.v_n_]), edges_(new Edge[2 * (t.v_n_ - 1)]) {
    memcpy(vertices_, t.vertices_, sizeof(*vertices_) * v_n_);
    memcpy(edges_, t.edges_, sizeof(*edges_) * 2 * (v_n_ - 1));
  }
  Tree(Tree &&t) : v_n_(v_n_), e_top_(t.e_top_), vertices_(t.vertices_), edges_(t.edges_) {
    t.edges_ = nullptr;
    t.vertices_ = nullptr;
  }
  ~Tree() {
    delete[] vertices_;
    delete[] edges_;
  }
  void add_edge(int x, int y) {
    edges_[e_top_].next_ = vertices_[x];
    edges_[e_top_].v_ = y;
    vertices_[x] = e_top_++;
    edges_[e_top_].next_ = vertices_[y];
    edges_[e_top_].v_ = x;
    vertices_[y] = e_top_++;
  }
};

int main() {
  struct Record {
    int v_, e_, p_;
    Record(int v, int e, int p) : v_(v), e_(e), p_(p) {}
  };
  struct Dp {
    int choose_, not_choose_;
  };
  int n;
  scanf("%d", &n);
  Tree tree(n);
  for (int i = 0; i < n; i++) {
    int x, n, y;
    scanf("%d %d", &x, &n);
    for (int i = 0; i < n; i++) {
      scanf("%d", &y);
      tree.add_edge(x, y);
    }
  }
  auto &vs = tree.vertices_;
  auto &es = tree.edges_;
  Dp *dp = new Dp[n];
  std::stack<Record> st;
  bool *visited = new bool[n];
  std::fill(visited, visited + n, false);
  st.push(Record(0, vs[0], -1));
  visited[0] = true;
  while (true) {
    auto &top = st.top();
    if (top.e_ == -1) {
      int choose = 1, not_choose = 0;
      for (int ei = vs[top.v_]; ei != -1;) {
        auto &e = es[ei];
        if (e.v_ != top.p_) {
          not_choose += dp[e.v_].choose_;
          choose += std::min(dp[e.v_].choose_, dp[e.v_].not_choose_);
        }
        ei = e.next_;
      }
      dp[top.v_].choose_ = choose;
      dp[top.v_].not_choose_ = not_choose;
      st.pop();
      if (st.empty()) break;
      st.top().e_ = es[st.top().e_].next_;
    } else {
      auto &e = es[top.e_];
      if (visited[e.v_]) {
        st.top().e_ = es[st.top().e_].next_;
      } else {
        visited[e.v_] = true;
        st.push(Record(e.v_, vs[e.v_], top.v_));
      }
    }
  }
  int result = std::min(dp[0].choose_, dp[0].not_choose_);
  delete[] dp;
  printf("%d\n", result);
  return 0;
}
