#include <cstdio>
#include <cstring>
#include <queue>

int n, m;
const int kMaxN = 1000;
const int kMaxM = 100000;

struct Graph {
  int front_[kMaxN + 1];
  struct Next {
    int n_, v_, w_;
  };
  Next next_[kMaxM];
  int cnt_ = 0;

  void init() { memset(front_, -1, sizeof(front_)); }
  inline void add_edge(int from, int to, int w) {
    next_[cnt_].n_ = front_[from];
    next_[cnt_].v_ = to;
    next_[cnt_].w_ = w;
    front_[from] = cnt_++;
  }
};

struct Dij {
  Graph* g_;
  int dist_[kMaxN + 1];
  bool visited_[kMaxN + 1];

  void init(Graph* g) { g_ = g; }
  void dij(int s) {
    struct Record {
      int v_, d_;
      Record(int v, int d) : v_(v), d_(d) {}
    };
    auto cmp = [](Record& r1, Record& r2) -> bool { return r1.d_ > r2.d_; };
    std::priority_queue<Record, std::vector<Record>, decltype(cmp)> pq(cmp);
    memset(visited_, 0, sizeof(visited_));
    pq.push(Record(s, 0));
    while (!pq.empty()) {
      auto top = pq.top();
      pq.pop();
      if (visited_[top.v_]) continue;
      dist_[top.v_] = top.d_;
      visited_[top.v_] = true;
      for (int i = g_->front_[top.v_]; i != -1; i = g_->next_[i].n_) {
        pq.push(Record(g_->next_[i].v_, top.d_ + g_->next_[i].w_));
      }
    }
  }
};

Graph g, rg;
Dij dij_g, dij_rg;

void init() {
  g.init();
  rg.init();
  dij_g.init(&g);
  dij_rg.init(&rg);
}

int main() {
  init();
  scanf("%d %d", &n, &m);
  for (int i = 0; i < m; i++) {
    int u, v, w;
    scanf("%d %d %d", &u, &v, &w);
    g.add_edge(u, v, w);
    rg.add_edge(v, u, w);
  }
  dij_g.dij(1);
  dij_rg.dij(1);
  int sum = 0;
  for (int i = 2; i <= n; i++) {
    sum += dij_g.dist_[i] + dij_rg.dist_[i];
  }
  printf("%d\n", sum);
}