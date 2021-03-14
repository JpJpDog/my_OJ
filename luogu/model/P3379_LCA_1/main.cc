#include <assert.h>

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <stack>

template <typename T>
struct Graph {
  struct Edge {
    int to_v_;
    int next_;
  };
  struct Vertex {
    T t;
    int edges_;
  };
  int vertex_n_, edge_n_, edge_top_;
  Edge *edges_;
  Vertex *vertexes_;

  Graph(int v_n, int e_n)
      : vertex_n_(v_n), edge_n_(e_n), edge_top_(0), edges_(new Edge[e_n]), vertexes_(new Vertex[v_n]) {
    for (int i = 0; i < v_n; i++) vertexes_[i].edges_ = -1;
  }
  ~Graph() {
    delete[] edges_;
    delete[] vertexes_;
  }
  inline void add_edge(int x, int y) {
    edges_[edge_top_].next_ = vertexes_[x].edges_;
    edges_[edge_top_].to_v_ = y;
    vertexes_[x].edges_ = edge_top_++;
    edges_[edge_top_].next_ = vertexes_[y].edges_;
    edges_[edge_top_].to_v_ = x;
    vertexes_[y].edges_ = edge_top_++;
  }
};
struct LCA {
  struct TreeNode {
    int parent_;
    int depth_;
    TreeNode() {}
    TreeNode(int p, int d) : parent_(p), depth_(d) {}
  };
  Graph<TreeNode> tree_;
  int **parents_, root_i_;

  LCA(int v_n) : tree_(v_n, 2 * (v_n - 1)) {}
  ~LCA() {
    delete[] parents_[0];
    delete[] parents_;
  }
  void add_pair(int a, int b) { tree_.add_edge(a, b); }
  void to_tree(int s) {
    struct Record {
      int v_, e_;
      Record(int v, int e) : v_(v), e_(e) {}
    };
    std::stack<Record> st;
    root_i_ = s;
    auto &vs = tree_.vertexes_;
    auto &es = tree_.edges_;
    st.push(Record(s, vs[s].edges_));
    vs[s].t.depth_ = 1;
    vs[s].t.parent_ = s;
    int max_depth = 0;
    while (true) {
      auto &top = st.top();
      if (top.e_ != -1) {
        auto &e = es[top.e_];
        if (e.to_v_ == vs[top.v_].t.parent_) {
          st.top().e_ = es[st.top().e_].next_;
        } else {
          auto &c = vs[e.to_v_];
          c.t.depth_ = st.size() + 1;
          c.t.parent_ = top.v_;
          //   printf("%d %d\n", top.v_, e.to_v_);
          st.push(Record(e.to_v_, c.edges_));
        }
      } else {
        max_depth = std::max(max_depth, int(st.size()));
        st.pop();
        if (st.empty()) break;
        st.top().e_ = es[st.top().e_].next_;
      }
    }
    int log_depth = int(floor(log2(max_depth - 1))) + 1, v_n = tree_.vertex_n_;
    int *parents = new int[v_n * log_depth];
    parents_ = new int *[v_n];
    for (int i = 0; i < v_n; i++) parents_[i] = parents + i * log_depth;
    for (int i = 0; i < v_n; i++) parents_[i][0] = vs[i].t.parent_;
    for (int j = 1; j < log_depth; j++) {
      for (int i = 1; i < v_n; i++) {
        if (vs[i].t.depth_ > (1 << j)) {
          parents_[i][j] = parents_[parents_[i][j - 1]][j - 1];
        }
      }
    }
  }

  int lca(int x, int y) {
    auto &vs = tree_.vertexes_;
    int d_x = vs[x].t.depth_, d_y = vs[y].t.depth_;
    if (d_x < d_y) {
      std::swap(x, y);
      std::swap(d_x, d_y);
    }
    int dd = d_x - d_y;
    for (int i = 0; (1 << i) <= dd; i++) {
      if (dd & (1 << i)) {
        x = parents_[x][i];
      }
    }
    assert(vs[x].t.depth_ == vs[y].t.depth_);
    if (x == y) return x;
    for (int i = int(floor(log2(d_y))); i >= 0;
         i--) {  // after every iteration, the lca must at most at x's 1<<i's parent
      if (parents_[x][i] != parents_[y][i]) {
        x = parents_[x][i];
        y = parents_[y][i];
      } else if (x == root_i_) {
        return x;
      }
    }
    return parents_[x][0];
  }
};

int main() {
  int N, M, S;
    scanf("%d %d %d", &N, &M, &S);
  LCA lca(N + 1);
  for (int i = 0; i < N - 1; i++) {
    int a, b;
    scanf("%d %d", &a, &b);
    lca.add_pair(a, b);
  }
  lca.to_tree(S);
  int *results = new int[M];
  for (int i = 0; i < M; i++) {
    int x, y;
    scanf("%d %d", &x, &y);
    results[i] = lca.lca(x, y);
  }
  for (int i = 0; i < M; i++) {
    printf("%d\n", results[i]);
  }
  delete[] results;
  return 0;
}