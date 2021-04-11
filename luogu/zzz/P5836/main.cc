#include <algorithm>
#include <cstdio>
#include <cstring>

const int kMaxN = 100000;
char farms[kMaxN + 1];
int N, M;

int cnt = 0;
int front[kMaxN + 1];
struct Next {
  int next_, v_;
};
Next next[2 * (kMaxN - 1)];  // N-1 direct edge

static inline void add_edge(int from, int to) {
  next[cnt].next_ = front[from];
  next[cnt].v_ = to;
  front[from] = cnt++;
}

const int kMaxLogDepth = 16;  // ceil(log(kMaxN-1))
int parent[kMaxN + 1][kMaxLogDepth + 1];
int depth[kMaxN + 1];  // depth[root]=0
// in_path[i][j][k] shows whether has type k cow in i's 2^k parents
char in_path[kMaxN + 1][kMaxLogDepth + 1];
int log2_int[kMaxN];

bool result[kMaxN];
int result_i = 0;

void dfs(int x, int p) {
  depth[x] = depth[p] + 1;
  in_path[x][0] = farms[p];
  parent[x][0] = p;
  for (int i = 1; (1 << i) <= depth[x]; i++) {
    const int pp = parent[x][i - 1];
    in_path[x][i] = in_path[x][i - 1] | in_path[pp][i - 1];
    parent[x][i] = parent[pp][i - 1];
  }
  for (int i = front[x]; i != -1; i = next[i].next_) {
    if (next[i].v_ != p) {
      dfs(next[i].v_, x);
    }
  }
}

bool lca(int x, int y, char type) {
  if (farms[x] == type || farms[y] == type) return true;
  if (depth[x] > depth[y]) std::swap(x, y);
  while (depth[y] > depth[x]) {
    const int lg_d = log2_int[depth[y] - depth[x]];
    if (in_path[y][lg_d] & type) return true;
    y = parent[y][lg_d];
  }
  if (x == y) {
    return false;
  }
  for (int i = log2_int[depth[x]]; i >= 0; i--) {
    if (parent[x][i] != parent[y][i]) {
      if (in_path[x][i] & type || in_path[y][i] & type) return true;
      x = parent[x][i];
      y = parent[y][i];
    }
  }
  return in_path[x][0] & type;
}

static void init() {
  log2_int[0] = -1;
  for (int i = 1; i < kMaxN; i++) {
    log2_int[i] = log2_int[i - 1] + ((1 << (log2_int[i - 1] + 1)) == i);
  }
  memset(front, -1, sizeof(int) * (kMaxN + 1));
}

// #define DEBUG

int main() {
#ifdef DEBUG
  FILE *fin = fopen("P5836_2.in", "r");
  FILE *fout = fopen("tmp.txt", "w");
#else
  FILE *fin = stdin;
  FILE *fout = stdout;
#endif
  init();
  fscanf(fin, "%d %d\n", &N, &M);
  for (int i = 1; i <= N; i++) {
    char tmp;
    fscanf(fin, "%c", &tmp);
    if (tmp == 'H')
      farms[i] = 1;
    else if (tmp == 'G')
      farms[i] = 2;
  }
  for (int i = 0; i < N - 1; i++) {
    int x, y;
    fscanf(fin, "%d %d", &x, &y);
    add_edge(x, y);
    add_edge(y, x);
  }
  depth[0] = -1;
  dfs(1, 0);
  for (int i = 0; i < M; i++) {
    int a, b;
    char c;
    fscanf(fin, "%d %d %c", &a, &b, &c);
    result[result_i++] = lca(a, b, c == 'H' ? 1 : 2);
  }
  for (int i = 0; i < M; i++) {
    fprintf(fout, "%d", result[i]);
  }
  fprintf(fout, "\n");
  fclose(fin);
  fclose(fout);
}