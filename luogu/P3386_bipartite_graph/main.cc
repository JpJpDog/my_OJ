#include <algorithm>
#include <cstdio>
#include <vector>

typedef std::vector<std::vector<int>> Graph;

class HungaryAlgorithm {
  const Graph &g1_, &g2_;
  std::vector<int> map1_, map2_;
  std::vector<bool> used_;
  // return if u can be added to an augmented path, u is in g1
  // if used_[u] is true, assume u finds the match and cannot change again.
  bool dfs(int u) {
    used_[u] = true;
    for (int i = 0; i < g1_[u].size(); i++) {
      int v = g1_[u][i];
      int u1 = map2_[v];
      if (used_[u1]) {
        continue;
      }
      if (map2_[v] == 0 || dfs(u1)) {
        map1_[u] = v;
        map2_[v] = u;
        return true;
      }
    }
    return false;
  }

 public:
  HungaryAlgorithm(const Graph &g1, const Graph &g2)
      : g1_(g1), g2_(g2), map1_(g1.size(), 0), map2_(g2.size(), 0), used_(g1.size()) {}
  int operator()() {
    int result = 0;
    for (int i = 1; i < g1_.size(); i++) {
      std::fill(used_.begin(), used_.end(), false);
      if (dfs(i)) {
        result++;
      }
    }
    return result;
  }
};

int main() {
  int n, m, e;
  scanf("%d %d %d", &n, &m, &e);
  Graph g1(n + 1), g2(m + 1);
  for (int i = 0; i < e; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    g1[u].push_back(v);
    g2[v].push_back(u);
  }
  HungaryAlgorithm hungary(g1, g2);
  printf("%d\n", hungary());
}