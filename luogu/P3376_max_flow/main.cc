#include <algorithm>
#include <cstdio>
#include <limits>
#include <queue>
#include <vector>

typedef long long int LL;

struct Edge {
  int v_, opposite_i_;
  LL e_;
  Edge(int v, LL e, int o_i) : v_(v), e_(e), opposite_i_(o_i) {}
};

typedef std::vector<std::vector<Edge>> Graph;

bool bfs(int s, int t, const Graph &graph, std::vector<int> &depth) {
  std::fill(depth.begin(), depth.end(), 0);
  std::queue<int> qu;
  qu.push(s);
  depth[s] = 1;
  while (!qu.empty()) {
    int top = qu.front();
    qu.pop();
    for (auto iter = graph[top].begin(); iter != graph[top].end(); iter++) {
      if (depth[iter->v_] == 0 && iter->e_ > 0) {
        depth[iter->v_] = depth[top] + 1;
        qu.push(iter->v_);
      }
    }
  }
  return depth[t] != 0;
}

LL dfs(int u, int t, LL in, std::vector<int> &depth, Graph &graph) {
  if (u == t) {
    return in;
  }
  LL out = 0;
  for (auto iter = graph[u].begin(); iter != graph[u].end() && in > 0; iter++) {
    if (iter->e_ > 0 && depth[iter->v_] == depth[u] + 1) {
      LL out1 = dfs(iter->v_, t, std::min(in, iter->e_), depth, graph);
      iter->e_ -= out1;
      graph[iter->v_][iter->opposite_i_].e_ += out1;
      out += out1;
      in -= out1;
    }
  }
  if (out == 0) {
    depth[u] = 0;
  }
  return out;
}

int main() {
  int n, m, s, t;
  scanf("%d %d %d %d", &n, &m, &s, &t);
  Graph graph(n + 1);
  for (int i = 0; i < m; i++) {
    int u, v, w;
    scanf("%d %d %d", &u, &v, &w);
    graph[u].push_back(Edge(v, w, graph[v].size()));
    graph[v].push_back(Edge(u, 0, graph[u].size() - 1));
  }
  std::vector<int> depth(n + 1);
  LL total = 0;
  while (bfs(s, t, graph, depth)) {
    total += dfs(s, t, std::numeric_limits<long long>::max(), depth, graph);
  }
  printf("%lld\n", total);
}