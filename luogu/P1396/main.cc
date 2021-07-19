#include <algorithm>
#include <cstdio>
#include <queue>

struct Record {
  int max_pay_;
  int last_;
  Record(int m, int l) : max_pay_(m), last_(l) {}
};

struct RecordCmp {
  bool operator()(const Record &r1, const Record &r2) { return r1.max_pay_ > r2.max_pay_; }
};

bool cmp_record(const Record &r1, const Record &r2) { return r1.max_pay_ < r2.max_pay_; }

struct Edge {
  int e_, v_;
  Edge(int e, int v) : e_(e), v_(v) {}
};

int main() {
  std::priority_queue<Record, std::vector<Record>, RecordCmp> qu;
  int n, m, s, t;
  scanf("%d %d %d %d", &n, &m, &s, &t);
  std::vector<std::vector<Edge>> graph(n + 1);
  std::vector<bool> visited(n + 1, false);
  for (int i = 0; i < m; i++) {
    int u, v, w;
    scanf("%d %d %d", &u, &v, &w);
    graph[u].push_back(Edge(w, v));
    graph[v].push_back(Edge(w, u));
  }
  qu.push(Record(0, s));
  int max_pay = -1;
  while (!qu.empty()) {
    const Record &r = qu.top();
    int last = r.last_, m_pay = r.max_pay_;
    qu.pop();
    if (last == t) {
      max_pay = m_pay;
      break;
    }
    if (visited[last]) {
      continue;
    }
    visited[last] = true;
    for (auto iter = graph[last].begin(); iter != graph[last].end(); iter++) {
      if (!visited[iter->v_]) {
        qu.push(Record(std::max(m_pay, iter->e_), iter->v_));
      }
    }
  }
  printf("%d\n", max_pay);
}