#include <algorithm>
#include <cstdio>
#include <vector>

struct Graph {
  std::vector<std::vector<int>> vertices_;
  Graph(int v_num) : vertices_(v_num + 1) {}
  void add_edge(int v1, int v2) {
    vertices_[v1].push_back(v2);
    vertices_[v2].push_back(v1);
  }
};

void DFS(int v_i, bool* visited, const Graph* g) {
  const auto& v = g->vertices_[v_i];
  visited[v_i] = true;
  for (auto iter = v.begin(); iter != v.end(); iter++) {
    if (!visited[*iter]) {
      DFS(*iter, visited, g);
    }
  }
}

int main() {
  int N, M, K;
  scanf("%d %d %d", &N, &M, &K);
  Graph g(N);
  for (int i = 0; i < M; i++) {
    int v1, v2;
    scanf("%d %d", &v1, &v2);
    g.add_edge(v1, v2);
  }
  int cared[K];
  for (int i = 0; i < K; i++) {
    scanf("%d", cared + i);
  }
  bool visited[N + 1];
  for (int i = 0; i < K; i++) {
    std::fill(visited, visited + N + 1, false);
    const auto& v = g.vertices_[cared[i]];
    visited[cared[i]] = true;
    int count = 0;
    for (auto iter = v.begin(); iter != v.end(); iter++) {
      if (!visited[*iter]) {
        count++;
        DFS(*iter, visited, &g);
      }
    }
    printf("%d\n", count - 1);
  }
}