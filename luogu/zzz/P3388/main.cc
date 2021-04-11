#include <algorithm>
#include <cstdio>
#include <cstring>

int n, m;

const int kMaxN = 20000;
const int kMaxM = 100000;

int front[kMaxN + 1];
struct Next {
  int v_, n_;
};
Next next[2 * kMaxM];
int cnt;

void init_graph() {
  cnt = 0;
  memset(front + 1, -1, sizeof(int) * n);
}

inline void add_edge(int from, int to) {
  next[cnt].v_ = to;
  next[cnt].n_ = front[from];
  front[from] = cnt++;
}

int dfn[kMaxN + 1];
int low[kMaxN + 1];
int parent[kMaxN + 1];
int cur_t;

int sep_v[kMaxM + 1];
int sep_i;

void dfs(int u) {
  low[u] = dfn[u] = cur_t++;
  bool sep = false;
  int cnt = 0;
  for (int i = front[u]; i != -1; i = next[i].n_) {
    const int v = next[i].v_;
    if (parent[u] == v) continue;
    if (dfn[v] == -1) {
      parent[v] = u;
      cnt++;
      dfs(v);
      low[u] = std::min(low[u], low[v]);
      if (low[v] >= dfn[u]) {
        sep = true;
      }
    } else {
      low[u] = std::min(low[u], dfn[v]);
    }
  }
  if (parent[u] != -1 && sep || parent[u] == -1 && cnt > 1) {
    sep_v[sep_i++] = u;
  }
}

void tarjan() {
  memset(dfn + 1, -1, sizeof(int) * n);
  cur_t = 0;
  sep_i = 0;
  for (int i = 1; i <= n; i++) {
    if (dfn[i] == -1) {
      parent[i] = -1;
      dfs(i);
    }
  }
}

int main() {
  FILE *fin = stdin;
  fscanf(fin, "%d %d", &n, &m);
  init_graph();
  for (int i = 0; i < m; i++) {
    int x, y;
    fscanf(fin, "%d %d", &x, &y);
    add_edge(x, y);
    add_edge(y, x);
  }
  tarjan();
  std::sort(sep_v, sep_v + sep_i);
  printf("%d\n", sep_i);
  for (int i = 0; i < sep_i; i++) {
    printf("%d ", sep_v[i]);
  }
  printf("\n");
}