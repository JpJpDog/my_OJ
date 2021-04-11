//bfs

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
#include <queue>
#include <string>

const int kMaxN = 30;
const int kMaxE = kMaxN * (kMaxN - 1) * 2;
int n, m;

int front[kMaxN + 1];
struct Next {
  double w_;
  int n_, v_;
};
Next next[kMaxE];
int next_cnt;

void init_graph() {
  memset(front, -1, sizeof(int) * (n + 1));
  next_cnt = 0;
}

inline void add_edge(int from, int to, double w) {
  next[next_cnt].w_ = w;
  next[next_cnt].n_ = front[from];
  next[next_cnt].v_ = to;
  front[from] = next_cnt++;
}

const double kInit = 0;

double dist[kMaxN + 1];
int route_l[kMaxN + 1];
bool in_st[kMaxN + 1];

void init_spfa() {
  std::fill((double*)dist, (double*)dist + n + 1, kInit);
  memset(route_l, 0, sizeof(int) * (n + 1));
  memset(in_st, 0, sizeof(bool) * (n + 1));
}

bool spfa(int start) {
  std::queue<int> qu;
  qu.push(start);
  in_st[start] = true;
  while (!qu.empty()) {
    int u = qu.front();
    qu.pop();
    in_st[u] = false;
    for (int i = front[u]; i != -1; i = next[i].n_) {
      const int v = next[i].v_;
      const double new_d = dist[u] * next[i].w_;
      if (dist[v] < new_d) {
        dist[v] = new_d;
        if (!in_st[v]) {
          in_st[v] = true;
          qu.push(v);
          route_l[v]++;
          if (route_l[v] >= n) return true;
        }
      }
    }
  }
  return false;
}

bool possitive_circle() {
  init_spfa();
  for (int i = 1; i <= n; i++) {
    if (dist[i] == kInit) {
      dist[i] = 1;
      if (spfa(i)) {
        return true;
      }
    }
  }
  return false;
}

const int kMaxBuf = 200;
char buf[kMaxBuf];
char buf2[kMaxBuf];

int main() {
  std::hash<std::string> str_hash;
  int case_i = 1;
  while (true) {
    scanf("%d", &n);
    if (n == 0) break;
    std::map<std::size_t, int> str_map;
    for (int i = 0; i < n; i++) {
      scanf("%s", buf);
      std::size_t hs = str_hash(buf);
      str_map[hs] = i + 1;
    }
    scanf("%d", &m);
    init_graph();
    for (int i = 0; i < m; i++) {
      double w;
      scanf("%s %lf %s", buf, &w, buf2);
      int u = str_map[str_hash(buf)], v = str_map[str_hash(buf2)];
      add_edge(u, v, w);
    }
    if (possitive_circle()) {
      printf("Case %d: Yes\n", case_i);
    } else {
      printf("Case %d: No\n", case_i);
    }
    case_i++;
  }
}