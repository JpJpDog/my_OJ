#include <algorithm>
#include <cstdio>
#include <cstring>

const int kMaxN = 1000000;
const int kMaxM = 2000000;

int front[kMaxN + 1];
struct Next {
  int n_, v_;
};
Next next[2 * kMaxM];
int cnt = 0;
static inline void add_edge(int from, int to) {
  next[cnt].n_ = front[from];
  next[cnt].v_ = to;
  front[from] = cnt++;
}

int N, M;
int result[kMaxN + 1];
char visited[kMaxN + 1];

struct Stack {
  int data_[kMaxN];
  int top_;
  inline void push(int x) { data_[top_++] = x; }
  inline int pop() { return data_[--top_]; }
  inline bool empty() { return top_ == 0; }
};

Stack st1, st2;
const int kMod = 100003;

void bfs(int start) {
  Stack *p1 = &st1, *p2 = &st2;
  p1->push(start);
  visited[start] = 2;
  while (!p1->empty()) {
    while (!p1->empty()) {
      const int u = p1->pop();
      for (int j = front[u]; j != -1; j = next[j].n_) {
        const int v = next[j].v_;
        if (visited[v] == 2) continue;
        result[v] += result[u];
        result[v] %= kMod;
        if (visited[v] == 0) {
          p2->push(v);
          visited[v] = 1;
        }
      }
    }
    for (int i = 0; i < p2->top_; i++) {
      visited[p2->data_[i]] = 2;
    }
    std::swap(p1, p2);
  }
}

void init() {
  memset(front, -1, sizeof(front));
  memset(visited, 0, sizeof(visited));
  memset(result, 0, sizeof(result));
  st1.top_ = st2.top_ = 0;
}

int main() {
  init();
  scanf("%d %d", &N, &M);
  for (int i = 0; i < M; i++) {
    int x, y;
    scanf("%d %d", &x, &y);
    add_edge(x, y);
    add_edge(y, x);
  }
  int start = 1;
  result[start] = 1;
  bfs(start);
  for (int i = 1; i <= N; i++) {
    printf("%d\n", result[i]);
  }
}