#include <cstdio>
#include <vector>

inline int parent(int c) { return (c + 1) / 2 - 1; }

inline int lchild(int p) { return 2 * p + 1; }

inline int rchild(int p) { return 2 * p + 2; }

int is_heap(int *arr, int len) {
  struct Record {
    int k_;
    int time_;
    Record(int k, int t) : k_(k), time_(t) {}
  };
  bool is_minheap = true, is_maxheap = true;
  std::vector<Record> st;
  st.push_back(Record(0, 0));
  while (!st.empty()) {
    auto cur = st.rbegin();
    cur->time_++;
    int p = cur->k_;
    int lc = lchild(p), rc = rchild(p);
    if (cur->time_ == 1 && rc < len) {
      if (arr[p] > arr[rc]) {
        is_minheap = false;
      }
      if (arr[p] < arr[rc]) {
        is_maxheap = false;
      }
      st.push_back(Record(rc, 0));
    } else if (cur->time_ == 2 && lc < len) {
      if (arr[p] > arr[lc]) {
        is_minheap = false;
      }
      if (arr[p] < arr[lc]) {
        is_maxheap = false;
      }
      st.push_back(Record(lc, 0));
    } else if (cur->time_ == 3) {
      if (lc >= len && rc >= len) {
        for (auto iter = st.begin(); iter != st.end() - 1; iter++) {
          printf("%d ", arr[iter->k_]);
        }
        printf("%d\n", arr[st.rbegin()->k_]);
      }
      st.pop_back();
    }
  }
  if (is_maxheap) {
    return 0;
  } else if (is_minheap) {
    return 1;
  }
  return 2;
}

int main() {
  int N;
  scanf("%d", &N);
  int tree[N];
  for (int i = 0; i < N; i++) {
    scanf("%d", tree + i);
  }
  int result = is_heap(tree, N);
  if (result == 0) {
    printf("Max Heap\n");
  } else if (result == 1) {
    printf("Min Heap\n");
  } else {
    printf("Not Heap\n");
  }
  return 0;
}