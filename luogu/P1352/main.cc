#include <algorithm>
#include <cstdio>
#include <cstring>

struct State {
  int choose_, not_choose_;
};

struct Tree {
  struct Edge {
    int next_, v_;
  };
  struct Vertice {
    int p_, e_, value_;
  };
  int v_n_, e_top_, root_index_;
  bool *roots_;
  Vertice *vertices_;
  Edge *edges_;
  Tree(int v_n, int *values)
      : v_n_(v_n), e_top_(0), vertices_(new Vertice[v_n]), edges_(new Edge[v_n - 1]), roots_(new bool[v_n]) {
    std::fill(roots_, roots_ + v_n, true);
    for (int i = 0; i < v_n; i++) {
      vertices_[i].e_ = -1;
      vertices_[i].value_ = values[i];
    }
  }
  Tree(const Tree &t) = delete;
  Tree(Tree &&t) = delete;
  ~Tree() {
    delete[] roots_;
    delete[] vertices_;
    delete[] edges_;
  }
  void add_edge(int p, int c) {
    roots_[c] = false;
    edges_[e_top_].next_ = vertices_[p].e_;
    edges_[e_top_].v_ = c;
    vertices_[p].e_ = e_top_++;
    vertices_[c].p_ = p;
  }
  void add_finished() {
    for (int i = 1; i < v_n_; i++) {
      if (roots_[i]) {
        root_index_ = i;
        break;
      }
    }
    delete[] roots_;
    roots_ = nullptr;
  }
};

void visit(const Tree &t, bool *visited, int v, int p, State *&dp) {
  visited[v] = true;
  auto &vs = t.vertices_;
  auto &es = t.edges_;
  for (int i = vs[v].e_; i != -1;) {
    auto &e = es[i];
    if (!visited[e.v_]) visit(t, visited, e.v_, v, dp);
    i = e.next_;
  }
  int choose = vs[v].value_, not_choose = 0;
  for (int i = vs[v].e_; i != -1; i = es[i].next_) {
    choose += dp[es[i].v_].not_choose_;
    not_choose += std::max(dp[es[i].v_].choose_, dp[es[i].v_].not_choose_);
  }
  dp[v].choose_ = choose;
  dp[v].not_choose_ = not_choose;
}

int main() {
  int n;
  scanf("%d", &n);
  int *arr = new int[n + 1];
  for (int i = 1; i < n + 1; i++) {
    scanf("%d", arr + i);
  }
  Tree tree(n + 1, arr);
  for (int i = 0; i < n - 1; i++) {
    int k, l;
    scanf("%d %d", &l, &k);
    tree.add_edge(k, l);
  }
  tree.add_finished();
  bool *visited = new bool[n + 1];
  std::fill(visited, visited + n + 1, false);
  State *dp = new State[n + 1];
  visit(tree, visited, tree.root_index_, -1, dp);
  int result = std::max(dp[tree.root_index_].choose_, dp[tree.root_index_].not_choose_);
  printf("%d\n", result);
  delete[] dp;
  delete[] visited;
  delete[] arr;
}
