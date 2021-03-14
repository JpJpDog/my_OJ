#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>

namespace my_ds {
template <typename T>
class MinHeap {
  std::vector<T> datas_;
  inline int lchild(int p) { return (p << 1) + 1; }
  inline int rchild(int p) { return (p << 1) + 2; }
  inline int parent(int c) { return (c + 1 >> 1) - 1; }
  void go_down(int i, T const &tmp) {
    int data_size = datas_.size();
    while (true) {
      int li = lchild(i), ri = rchild(i);
      bool l = li >= data_size || tmp < datas_[li], r = ri >= data_size || tmp < datas_[ri];
      if (l && r) {
        break;
      } else if (l) {
        datas_[i] = datas_[ri];
        i = ri;
      } else if (r) {
        datas_[i] = datas_[li];
        i = li;
      } else if (datas_[ri] < datas_[li]) {
        datas_[i] = datas_[ri];
        i = ri;
      } else {
        datas_[i] = datas_[li];
        i = li;
      }
    }
    datas_[i] = tmp;
  }

 public:
  MinHeap() {}
  MinHeap(const std::vector<T> &datas) : datas_(datas) {
    int data_size = datas.size();
    for (int i = (data_size - 1) / 2; i >= 0; i--) {
      go_down(i, datas[i]);
    }
  }
  MinHeap(const MinHeap &other) : datas_(other.datas_) {}
  MinHeap &operator=(const MinHeap &other) { this->datas_ = other.datas_; }
  void push(const T &data) {
    datas_.push_back(data);
    int last_i = datas_.size() - 1;
    int i = last_i;
    while (i) {
      int pi = parent(i);
      if (data < datas_[pi]) {
        datas_[i] = datas_[pi];
        i = pi;
      } else {
        break;
      }
      if (i != last_i) {
        datas_[i] = data;
      }
    }
  }
  void pop() {
    T tmp = datas_[datas_.size() - 1];
    datas_.pop_back();
    go_down(0, tmp);
  }
  T top() { return datas_[0]; }
  inline bool is_empty() { return datas_.empty(); }
};
}  // namespace my_ds

template <typename T1, typename T2>
struct Graph {
  struct Edge;
  struct Vertice {
    T1 data_;
    std::vector<Edge> edges_;
    Vertice(const T1 &data) : data_(data) {}
  };
  struct Edge {
    int vertice_i_;
    T2 data_;
    Edge(int vertice_i, const T2 &data) : vertice_i_(vertice_i), data_(data) {}
  };

  std::vector<Vertice> vertices_;
  Graph(const std::vector<T1> &vertice_data) {
    int vertice_num = vertice_data.size();
    vertices_.reserve(vertice_num);
    for (auto iter = vertice_data.begin(); iter != vertice_data.end(); iter++) {
      vertices_.push_back(Vertice(*iter));
    }
  }
  void add_edge(int v1, int v2, T2 value) {
    vertices_[v1].edges_.push_back(Edge(v2, value));
    vertices_[v2].edges_.push_back(Edge(v1, value));
  }
};

void shortest_pathes(const Graph<int, int> &graph, int start_i, int end_i, int &out_min_dist, int &out_path_num,
                     int &out_max_value, std::vector<std::vector<int>> &out_paths) {
  class DistVertice {
   public:
    int dist_;
    int vertice_i_;
    int value_;
    int path_num_;
    DistVertice() {}
    DistVertice(int dist, int vertice_i, int value, int path_n)
        : dist_(dist), vertice_i_(vertice_i), value_(value), path_num_(path_n) {}
    bool operator<(const DistVertice &other) const {
      return dist_ < other.dist_ || dist_ == other.dist_ && vertice_i_ < other.vertice_i_;
    }
  };
  auto &vertices = graph.vertices_;
  out_paths.reserve(vertices.size());
  std::vector<bool> vertice_done(vertices.size(), false);
  my_ds::MinHeap<DistVertice> heap;
  heap.push(DistVertice(0, start_i, vertices[start_i].data_, 1));
  while (!heap.is_empty()) {
    DistVertice mindist_v = heap.top();
    heap.pop();
    int vertice_i = mindist_v.vertice_i_;
    if (vertice_done[vertice_i]) {
      continue;
    }
    int path_num = mindist_v.path_num_, max_value = mindist_v.value_;
    while (!heap.is_empty() && heap.top().dist_ == mindist_v.dist_ && heap.top().vertice_i_ == vertice_i) {
      auto top_v = heap.top();
      if (top_v.value_ > max_value) {
        max_value = top_v.value_;
      }
      path_num += top_v.path_num_;
      heap.pop();
    }
    if (vertice_i == end_i) {
      out_min_dist = mindist_v.dist_;
      out_path_num = path_num;
      out_max_value = max_value;
      break;
    }
    vertice_done[vertice_i] = true;
    for (auto iter = vertices[vertice_i].edges_.begin(); iter != vertices[vertice_i].edges_.end(); iter++) {
      if (!vertice_done[iter->vertice_i_]) {
        heap.push(DistVertice(mindist_v.dist_ + iter->data_, iter->vertice_i_,
                              vertices[iter->vertice_i_].data_ + max_value, path_num));
        out_paths[iter->vertice_i_].push_back(vertice_i);
      }
    }
  }
}

void print_paths(const std::vector<std::vector<int>> &paths) {
  
}

int main() {
  int N, M, c1, c2;
  scanf("%d %d %d %d", &N, &M, &c1, &c2);
  std::vector<int> vertice_values(N, 0);
  for (int i = 0; i < N; i++) {
    scanf("%d", &(vertice_values[i]));
  }
  Graph<int, int> graph(vertice_values);
  for (int i = 0; i < M; i++) {
    int v1, v2, value;
    scanf("%d %d %d", &v1, &v2, &value);
    graph.add_edge(v1, v2, value);
  }
  int min_dist, path_num, max_value;
  std::vector<std::vector<int>> paths;
  shortest_pathes(graph, c1, c2, min_dist, path_num, max_value, paths);
  print_paths(paths);
  printf("%d %d %d\n", min_dist, path_num, max_value);
}
