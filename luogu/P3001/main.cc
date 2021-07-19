#include <cstdio>

#define MAXN 2005
#define MAXM 25005
#define INF 1e15

struct Edge {
  int v_;
  double r_;
  int next_;
  Edge() {}
  Edge(int v, double r, int next) : v_(v), r_(r), next_(next) {}
};

Edge edges[MAXM];
int vertices[MAXN] = {0}, e_len = 0;

void edge_insert(int x, int y, double r) {
  edges[++e_len] = Edge(y, r, vertices[x]);
  vertices[x] = e_len;
}

double dist[MAXN];
bool in_q[MAXN] = {false};
int que[MAXN], q_head = 0, q_tail = 0;
inline void q_push(int v) {
  in_q[v] = true;
  que[q_tail++] = v;
  if (q_tail == MAXN) {
    q_tail = 0;
  }
}
inline int q_pop() {
  int tmp = que[q_head++];
  in_q[tmp] = false;
  if (q_head == MAXN) {
    q_head = 0;
  }
  return tmp;
}
inline bool q_empty() { return q_head == q_tail; }

void SPFA(int N, int V, int A) {
  for (int i = 1; i <= N; i++) {
    dist[i] = INF;
  }
  dist[A] = V;
  q_push(A);
  while (!q_empty()) {
    int u = q_pop();
    Edge& e = edges[vertices[u]];
    for (int v = e.v_; v; e = edges[e.next_], v = e.v_) {
      if (dist[u] * e.r_ < dist[v]) {
        dist[v] = dist[u] * e.r_;
        if (!in_q[v]) {
          q_push(v);
        }
      }
    }
  }
}

int main() {
  int N, M, V, A, B;
  scanf("%d %d %d %d %d", &N, &M, &V, &A, &B);
  for (int i = 0; i < M; i++) {
    int x, y;
    double r;
    scanf("%d %d %lf", &x, &y, &r);
    edge_insert(x, y, r);
  }
  SPFA(N, V, A);
  if (dist[B] == INF) {
    printf("0\n");
  } else {
    printf("%lf\n", dist[B]);
  }
  return 0;
}