#include <algorithm>
#include <cstdio>
#include <cstring>

struct Book {
  int w_, h_;
};

bool compare_asc(const Book &b1, const Book &b2) { return b1.h_ < b2.h_; }

int main() {
  int n, k;
  scanf("%d %d", &n, &k);
  Book *books = new Book[n];
  for (int i = 0; i < n; i++) {
    int h, w;
    scanf("%d %d", &h, &w);
    books[i].h_ = h;
    books[i].w_ = w;
  }
  std::sort(books, books + n, compare_asc);
  // a[i][j] the cost of first i books remain j book and book_i must be remained
  // a[i][j]=min(a[k][j-1]+abs(w[i]-w[k]) for k in [j-1,i-1])
  int *dp = new int[n + 1];
  memset(dp, 0, sizeof(*dp) * n);
  for (int j = 2; j <= n - k; j++) {
    for (int i = n; i >= j; i--) {
      int min_cost = int(1e9);
      for (int k = j - 1; k < i; k++) {
        min_cost = std::min(min_cost, dp[k] + std::abs(books[i - 1].w_ - books[k - 1].w_));
      }
      dp[i] = min_cost;
    }
  }
  int min_cost = int(1e9);
  for (int i = n - k; i <= n; i++) {
    min_cost = std::min(min_cost, dp[i]);
  }
  printf("%d\n", min_cost);
  delete[] dp;
  delete[] books;
}