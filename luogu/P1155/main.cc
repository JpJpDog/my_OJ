#include <algorithm>
#include <cstdio>
#include <queue>
#include <stack>
#include <vector>

int n;
std::stack<int> st1, st2;
std::vector<char> result;
std::vector<int> arr;
std::vector<char> type;

bool cal_interfere() {
  std::vector<int> map(n + 1), bound(n + 1);
  for (int i = 1; i <= n; i++) {
    map[arr[i]] = i;
  }
  int max_before = -1;
  for (int i = 1; i <= n; i++) {
    bound[i] = max_before = std::max(max_before, map[i]);
  }
  std::vector<std::vector<int>> graph(n + 1);
  for (int j = 1; j <= n; j++) {
    for (int i = 1; i < j; i++) {
      if (arr[i] < arr[j] && bound[arr[i]] > j) {
        graph[arr[i]].push_back(arr[j]);
        graph[arr[j]].push_back(arr[i]);
      }
    }
  }
  type.resize(n + 1, 0);
  std::vector<bool> visited(n + 1, false);
  struct Record {
    int i_;
    bool flip_;
    Record() {}
    Record(int i, int f) : i_(i), flip_(f) {}
  };
  std::queue<Record> qu;
  for (int i = 1; i <= n; i++) {
    if (!graph[i].empty()) {
      qu.push(Record(i, true));
      visited[i] = true;
      type[i] = 1;
      break;
    }
  }
  while (!qu.empty()) {
    int i = qu.front().i_;
    bool flip = !qu.front().flip_;
    char t = flip ? 1 : 2;
    qu.pop();
    for (auto j : graph[i]) {
      if (!visited[j]) {
        visited[j] = true;
        qu.push(Record(j, flip));
        type[j] = t;
      } else if (type[j] + t == 3) {
        return false;
      }
    }
  }
  return true;
}

bool can_push(int i, const std::stack<int> &st, const std::stack<int> &st2) {
  if (st.empty()) return true;
  int j = st.top();
  if (j < i) return false;
  int ti = type[i], tj = type[j], tk = 0;
  if (!st2.empty()) tk = type[st2.top()];
  if (ti == 0 || tj == 0 && tk == 0) return true;
  if (tj != 0) return ti == tj;
  return ti != tk;
}

bool simulate() {
  bool flag = true;
  int last_pop = 0;
  for (int i = 1; i <= n; i++) {
    int cur = arr[i];
    while (!st1.empty() && st1.top() == last_pop + 1) {
      last_pop++;
      result.push_back('b');
      st1.pop();
    }
    if (can_push(cur, st1, st2)) {
      result.push_back('a');
      st1.push(cur);
      continue;
    }
    while (true) {
      if (!st2.empty() && st2.top() == last_pop + 1) {
        last_pop++;
        result.push_back('d');
        st2.pop();
      } else if (!st1.empty() && st1.top() == last_pop + 1) {
        last_pop++;
        result.push_back('b');
        st1.pop();
        if (st1.empty() || st1.top() > cur) break;
      } else {
        break;
      }
    }
    if (can_push(cur, st1, st2)) {
      result.push_back('a');
      st1.push(cur);
    } else if (can_push(cur, st2, st1)) {
      result.push_back('c');
      st2.push(cur);
    } else {
      flag = false;
      break;
    }
  }
  if (flag) {
    while (true) {
      if (!st1.empty() && st1.top() == last_pop + 1) {
        result.push_back('b');
        last_pop++;
        st1.pop();
      } else if (!st2.empty() && st2.top() == last_pop + 1) {
        result.push_back('d');
        last_pop++;
        st2.pop();
      } else {
        break;
      }
    }
    if (!st1.empty() || !st2.empty()) flag = false;
  }
  return flag;
}

int main() {
  scanf("%d", &n);
  arr.resize(n + 1);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &(arr[i]));
  }
  if (cal_interfere() && simulate()) {
    printf("%c", result[0]);
    for (int i = 1; i < result.size(); i++) {
      printf(" %c", result[i]);
    }
    printf("\n");
  } else {
    printf("0\n");
  }
}