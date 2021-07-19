#include <algorithm>
#include <cstdio>
#include <stack>
#include <utility>
#include <vector>

struct Graph {
  std::vector<int> vertices_;
  std::vector<std::vector<int>> edges_;

  Graph(std::vector<int> &&vs) : vertices_(vs), edges_(vs.size()) {}
  void add_edge(int a, int b) { edges_[a].push_back(b); }
};

class Tarjan {
  const Graph &graph_;
  std::vector<int> low_, dfn_, group_;
  std::vector<bool> in_st_;
  int group_n_, t_;
  void tarjan(const int v) {
    if (graph_.edges_[v].empty()) {
      t_++;
      group_[v] = group_n_++;
      return;
    }
    struct Record {
      int e_i_, v_i_;
      Record(int e, int v) : e_i_(e), v_i_(v) {}
    };
    std::stack<Record> r_st;
    std::stack<int> st;
    group_[v] = -2;
    low_[v] = dfn_[v] = t_++;
    st.push(v);
    in_st_[v] = true;
    r_st.push(Record(0, v));
    while (true) {
      auto &top = r_st.top();
      auto &es = graph_.edges_[top.v_i_];
      int cur_v = top.v_i_;
      if (es.size() == top.e_i_) {
        if (low_[cur_v] == dfn_[cur_v]) {
          while (true) {
            int top = st.top();
            group_[top] = group_n_;
            in_st_[top] = false;
            st.pop();
            if (top == cur_v) break;
          };
          group_n_++;
        }
        r_st.pop();
        if (r_st.empty()) break;
        int prev_v = r_st.top().v_i_;
        low_[prev_v] = std::min(low_[prev_v], low_[cur_v]);
      } else {
        int next_v = es[top.e_i_++];
        if (group_[next_v] == -1) {
          group_[next_v] = -2;
          low_[next_v] = dfn_[next_v] = t_++;
          st.push(next_v);
          in_st_[next_v] = true;
          r_st.push(Record(0, next_v));
        } else if (in_st_[next_v]) {
          low_[cur_v] = std::min(low_[next_v], low_[cur_v]);
        }
      }
    }
  }

 public:
  Tarjan(const Graph &g) : graph_(g) {}
  Graph operator()() {
    const int vertice_n = graph_.vertices_.size();
    low_.resize(vertice_n);
    dfn_.resize(vertice_n);
    group_.resize(vertice_n, -1);
    in_st_.resize(vertice_n, false);
    group_n_ = t_ = 0;
    for (int v = 0; v < vertice_n; v++) {
      if (group_[v] == -1) {
        tarjan(v);
      }
    }
    std::vector<int> new_v(group_n_);
    for (int i = 0; i < group_.size(); i++) {
      new_v[group_[i]] += graph_.vertices_[i];  // group[2994] -2
    }
    Graph new_g(std::move(new_v));
    for (int cur_v = 0; cur_v < group_.size(); cur_v++) {
      int c_v = group_[cur_v], n_v;
      for (auto next_v : graph_.edges_[cur_v]) {
        if (c_v != (n_v = group_[next_v])) {
          new_g.add_edge(c_v, n_v);
        }
      }
    }
    return new_g;
  }
};

int main() {
  int n, m;
  scanf("%d %d", &n, &m);
  std::vector<int> vertices(n + 1);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &(vertices[i]));
  }
  Graph g(std::move(vertices));
  for (int i = 0; i < m; i++) {
    int a, b;
    scanf("%d %d", &a, &b);
    g.add_edge(a, b);
  }
  Tarjan tj(g);
  Graph new_g = tj();
  int new_v_n = new_g.vertices_.size();
  std::vector<std::vector<int>> prev(new_v_n);
  std::vector<int> in_d(new_v_n, 0);
  std::vector<int> dp(new_v_n, 0);
  std::stack<int> z_d;
  for (int cur_v = 1; cur_v < new_v_n; cur_v++) {
    for (auto next_v : new_g.edges_[cur_v]) {
      prev[next_v].push_back(cur_v);
      in_d[next_v]++;
    }
  }
  for (int i = 1; i < new_v_n; i++) {
    if (in_d[i] == 0) {
      z_d.push(i);
      dp[i] = new_g.vertices_[i];
    }
  }
  while (!z_d.empty()) {
    int cur = z_d.top();
    z_d.pop();
    for (int next : new_g.edges_[cur]) {
      if (!(--in_d[next])) {
        z_d.push(next);
      }
    }
    for (int prev : prev[cur]) {
      dp[cur] = std::max(dp[cur], dp[prev] + new_g.vertices_[cur]);
    }
  }
  int result = *std::max_element(dp.begin() + 1, dp.end());
  printf("%d\n", result);
}