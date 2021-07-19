#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

// sigma(nume)/sigma(deno) <= result
// find the min result that meet the condition in a loop
// set weight = deno*result-nume, it meet condition if all weight loop > 0
// so binary find the result first make a loop < 0

int N, M;

const int kMaxN = 7000;
const int kMaxM = 20000;

int front[kMaxN + 1];
struct Next {
  int n_, v_, deno_, nume_;
};
Next next[kMaxM];
int cnt = 0;

void init_graph() { memset(front + 1, -1, sizeof(int) * N); }
inline void add_edge(int from, int to, int v, int p) {
  next[cnt].n_ = front[from];
  next[cnt].v_ = to;
  next[cnt].nume_ = v;
  next[cnt].deno_ = p;
  front[from] = cnt++;
}

double weight[kMaxM];

void set_weight(double mid) {
  for (int i = 0; i < M; i++) {
    weight[i] = mid * next[i].deno_ - next[i].nume_;
  }
}

bool in_st[kMaxN + 1];
double dist[kMaxN + 1];

const double kDistInf = 1e10;

bool spfa(int u) {
  in_st[u] = true;
  for (int i = front[u]; i != -1; i = next[i].n_) {
    const int v = next[i].v_;
    if (dist[u] + weight[i] < dist[v]) {
      dist[v] = dist[u] + weight[i];
      if (in_st[v] || spfa(v)) {
        return true;
      }
    }
  }
  in_st[u] = false;
  return false;
}

bool has_minus_loop() {
  std::fill(dist + 1, dist + N + 1, kDistInf);
  memset(in_st + 1, 0, sizeof(bool) * N);
  for (int i = 1; i <= N; i++) {
    if (dist[i] == kDistInf) {
      dist[i] = 0;
      if (spfa(i)) return true;
    }
  }
  return false;
}

char visited[kMaxN + 1];

bool dfs(int u) {
  visited[u] = 1;
  for (int i = front[u]; i != -1; i = next[i].n_) {
    const int v = next[i].v_;
    if (visited[v] == 2) continue;
    if (visited[v]) return true;
    if (dfs(v)) return true;
  }
  visited[u] = 2;
  return false;
}

bool has_loop() {
  memset(visited + 1, 0, sizeof(bool) * N);
  for (int i = 1; i <= N; i++) {
    if (!visited[i] && dfs(i)) {
      return true;
    }
  }
  return false;
}

const double kMaxRange = 200.0;
const int kPrecision = 10;

int main() {
  scanf("%d %d", &N, &M);
  init_graph();
  for (int i = 0; i < M; i++) {
    int s, e, v, p;
    scanf("%d %d %d %d", &s, &e, &v, &p);
    add_edge(s, e, v, p);
  }
  if (!has_loop()) {
    printf("-1\n");
    return 0;
  }
  double low = 0, high = kMaxRange, mid;
  while (true) {
    if ((int)round(low * kPrecision) == (int)round(high * kPrecision)) break;
    mid = (low + high) / 2;
    set_weight(mid);
    if (has_minus_loop()) {
      low = mid;
    } else {
      high = mid;
    }
  }
  printf("%.1f\n", low);
}
