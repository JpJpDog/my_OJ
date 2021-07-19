#include <cstdio>
#include <cstring>

const int kMaxN = 8;

char mid[kMaxN + 1];
char back[kMaxN + 1];
char front[kMaxN + 1];
int front_i = 0;
int n;

void append_root(int back_l, int back_r, int off) {
  if (back_r < back_l) return;
  char root = back[back_r];
  front[front_i++] = root;
  if (back_l == back_r) return;
  int mid_i;
  for (mid_i = back_l + off; mid_i <= back_r + off; mid_i++) {
    if (mid[mid_i] == root) {
      break;
    }
  }
  append_root(back_l, mid_i - off - 1, off);
  append_root(mid_i - off, back_r - 1, off + 1);
}

int main() {
  scanf("%s", mid);
  scanf("%s", back);
  n = strlen(mid);
  append_root(0, n - 1, 0);
  front[n] = '\0';
  printf("%s\n", front);
}