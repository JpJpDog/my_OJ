#include <cstdio>
#include <vector>

#define MAX_LEVEL 100

int count_no_child(const std::vector<std::vector<int>>& tree, int root, int root_lv, std::vector<int>& result) {
  if (tree[root].size() == 0) {
    result[root_lv]++;
    return root_lv;
  } else {
    int max_child_lv = -1;
    for (auto iter = tree[root].begin(); iter != tree[root].end(); iter++) {
      int tmp = count_no_child(tree, *iter, root_lv + 1, result);
      if (tmp > max_child_lv) {
        max_child_lv = tmp;
      }
    }
    return max_child_lv;
  }
}

int main() {
  int N, M;
  scanf("%d %d", &N, &M);
  std::vector<std::vector<int>> tree(N + 1);
  for (int i = 0; i < M; i++) {
    int parent, child_n;
    scanf("%d %d", &parent, &child_n);
    tree[parent].reserve(child_n);
    for (int j = 0; j < child_n; j++) {
      int child;
      scanf("%d", &child);
      tree[parent].push_back(child);
    }
  }
  std::vector<int> no_child_n(MAX_LEVEL, 0);
  no_child_n[0] = 0;
  int max_lv = count_no_child(tree, 1, 0, no_child_n);
  for (int i = 0; i < max_lv; i++) {
    printf("%d ", no_child_n[i]);
  }
  printf("%d\n", no_child_n[max_lv]);
}