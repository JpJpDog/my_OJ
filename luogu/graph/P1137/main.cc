#include <algorithm>
#include <cstdio>
#include <stack>
#include <vector>

int main() {
  int N, M;
  scanf("%d %d", &N, &M);
  std::vector<int> ind(N + 1, 0);
  std::vector<int> dp(N + 1);
  std::vector<std::vector<int>> prevs(N + 1);
  std::vector<std::vector<int>> nexts(N + 1);
  for (int i = 1; i <= M; i++) {
    int a, b;
    scanf("%d %d", &a, &b);
    prevs[b].push_back(a);
    nexts[a].push_back(b);
    ind[b]++;
  }
  std::stack<int> st;
  for (int i = 1; i <= N; i++) {
    if (!ind[i]) {
      st.push(i);
      dp[i] = 1;
    }
  }
  while (!st.empty()) {
    int cur = st.top();
    st.pop();
    int cur_dp = 1;
    for (auto prev : prevs[cur]) {
      cur_dp = std::max(cur_dp, dp[prev] + 1);
    }
    dp[cur] = cur_dp;
    for (auto next : nexts[cur]) {
      ind[next]--;
      if (!ind[next]) {
        st.push(next);
      }
    }
  }
  for (int i = 1; i <= N; i++) {
    printf("%d\n", dp[i]);
  }
}