#include <algorithm>
#include <cstdio>
#include <cstring>

const int kMaxN = 100000;
const int kMaxLogDepth = 16;

int N, Q;
int depth[kMaxN + 1];
int parent[kMaxN + 1][kMaxLogDepth];
int log2_int[kMaxN];

struct Next {
  int next_, v_;
};
int front[kMaxN + 1];
Next next[2 * (kMaxN - 1)];
int next_cnt = 0;

static inline void add_edge(int from, int to) {
  next[next_cnt].next_ = front[from];
  next[next_cnt].v_ = to;
  front[from] = next_cnt++;
}

static void init() {
  memset(front, -1, sizeof(int) * (kMaxN + 1));
  log2_int[0] = -1;
  for (int i = 1; i < kMaxN; i++) {
    log2_int[i] = log2_int[i - 1] + (i == (1 << log2_int[i - 1] + 1));
  }
}
void dfs(int x, int p) {
  depth[x] = depth[p] + 1;
  parent[x][0] = p;
  for (int i = 1; i <= log2_int[depth[x]]; i++) {
    parent[x][i] = parent[parent[x][i - 1]][i - 1];
  }
  for (int i = front[x]; i != -1; i = next[i].next_) {
    if (next[i].v_ != p) {
      dfs(next[i].v_, x);
    }
  }
}

int lca(int a, int b) {
  if (depth[a] > depth[b]) std::swap(a, b);
  while (depth[b] > depth[a]) {
    b = parent[b][log2_int[depth[b] - depth[a]]];
  }
  // assert(depth[a] == depth[b]);
  if (a == b) return a;
  for (int i = log2_int[depth[a]]; i >= 0; i--) {
    if (parent[a][i] != parent[b][i]) {
      a = parent[a][i];
      b = parent[b][i];
    }
  }
  // assert(parent[a][0] == parent[b][0]);
  return parent[a][0];
}

bool encounter(int a, int b, int c, int d) {
  int p1 = lca(a, b), p2 = lca(c, d);
  if (p1 == p2) return true;
  if (depth[p1] == depth[p2]) return false;
  int x = a, y = b, p = p1, pp = p2;
  if (depth[p1] > depth[p2]) {  // pp is deeper, so is probably in path of x,y
    x = c;
    y = d;
    std::swap(p, pp);
  }
  return depth[x] >= depth[pp] && lca(x, pp) == pp ||
         depth[y] >= depth[pp] && lca(y, pp) == pp;
}

// #define DEBUG

int main() {
#ifdef DEBUG
  FILE *fin = fopen("P3398_5.in", "r");
  FILE *fout = fopen("tmp.txt", "w");
#else
  FILE *fin = stdin;
  FILE *fout = stdout;
#endif
  init();
  fscanf(fin, "%d %d", &N, &Q);
  for (int i = 0; i < N - 1; i++) {
    int a, b;
    fscanf(fin, "%d %d", &a, &b);
    add_edge(a, b);
    add_edge(b, a);
  }
  depth[0] = -1;
  dfs(1, 0);
  for (int i = 0; i < Q; i++) {
    int a, b, c, d;
    fscanf(fin, "%d %d %d %d", &a, &b, &c, &d);
    if (encounter(a, b, c, d)) {
      fprintf(fout, "Y\n");
    } else {
      fprintf(fout, "N\n");
    }
  }
  fclose(fin);
  fclose(fout);
}