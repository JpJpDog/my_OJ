#include <cstdio>
#include <stack>
#include <vector>

const int mod = 80112002;

struct Vertice {
  int n_, in_d_;
  std::vector<int> es_;
  Vertice() : in_d_(0), n_(0) {}
};

int main() {
  int n, m;
  scanf("%d %d", &n, &m);
  std::vector<Vertice> graph(n + 1);
  for (int i = 0; i < m; i++) {
    int a, b;
    scanf("%d %d", &a, &b);
    graph[a].in_d_++;
    graph[b].es_.push_back(a);
  }
  std::stack<int> st;
  for (int i = 1; i <= n; i++) {
    if (graph[i].in_d_ == 0) {
      graph[i].n_ = 1;
      st.push(i);
    }
  }
  int result = 0;
  while (!st.empty()) {
    int cur = st.top();
    auto &cur_v = graph[cur];
    st.pop();
    if (cur_v.es_.size() == 0) {
      (result += cur_v.n_) %= mod;
      continue;
    }
    for (auto iter = cur_v.es_.begin(); iter != cur_v.es_.end(); iter++) {
      auto &v = graph[*iter];
      v.in_d_--;
      (v.n_ += cur_v.n_) %= mod;
      if (v.in_d_ == 0) {
        st.push(*iter);
      }
    }
  }
  printf("%d\n", result);
}