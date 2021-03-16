#include <algorithm>
#include <cstdio>
#include <queue>

struct Cell {
  int a_, b_;
  Cell() : a_(0), b_(0) {}
};

struct Loc {
  int x_, y_;
  Loc(int x, int y) : x_(x), y_(y) {}
};

bool in_danger(const Cell &c, int t) { return c.a_ <= t && c.b_ >= t; }

int main() {
  int n, m, t;
  scanf("%d %d %d", &n, &m, &t);
  Cell *cells1 = new Cell[(n + 1) * (m + 1)];
  bool *in_qu1 = new bool[(n + 1) * (m + 1)];
  Cell **cells = new Cell *[n + 1];
  bool **in_qu = new bool *[n + 1];
  for (int i = 0; i < n + 1; i++) {
    cells[i] = cells1 + (m + 1) * i;
    in_qu[i] = in_qu1 + (m + 1) * i;
  }
  for (int i = 0; i < t; i++) {
    int r, c, a, b;
    scanf("%d %d %d %d", &r, &c, &a, &b);
    cells[r][c].a_ = a;
    cells[r][c].b_ = b;
  }
  std::queue<Loc> qu1;
  std::queue<Loc> qu2;
  qu1.push(Loc(1, 1));
  int time = 1;
  while (true) {
    std::fill(in_qu1, in_qu1 + (m + 1) * (n + 1), false);
    while (!qu1.empty()) {
      Loc top = qu1.front();
      qu1.pop();
      if (top.x_ > 1 && !in_danger(cells[top.x_ - 1][top.y_], time) && !in_qu[top.x_ - 1][top.y_]) {
        qu2.push(Loc(top.x_ - 1, top.y_));
        in_qu[top.x_ - 1][top.y_] = true;
      }
      if (top.y_ > 1 && !in_danger(cells[top.x_][top.y_ - 1], time) && !in_qu[top.x_][top.y_ - 1]) {
        qu2.push(Loc(top.x_, top.y_ - 1));
        in_qu[top.x_][top.y_ - 1] = true;
      }
      if (top.x_ < n && !in_danger(cells[top.x_ + 1][top.y_], time) && !in_qu[top.x_ + 1][top.y_]) {
        if (top.x_ + 1 == n && top.y_ == m) goto END;
        qu2.push(Loc(top.x_ + 1, top.y_));
        in_qu[top.x_ + 1][top.y_] = true;
      }
      if (top.y_ < m && !in_danger(cells[top.x_][top.y_ + 1], time) && !in_qu[top.x_][top.y_ + 1]) {
        if (top.x_ == n && top.y_ + 1 == m) goto END;
        qu2.push(Loc(top.x_, top.y_ + 1));
        in_qu[top.x_][top.y_ + 1] = true;
      }
    }
    time++;
    std::swap(qu1, qu2);
  }
END:
  printf("%d\n", time);
  delete[] in_qu1;
  delete[] in_qu;
  delete[] cells1;
  delete[] cells;
}