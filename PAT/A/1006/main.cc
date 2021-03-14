#include <string.h>

#include <cstdio>
struct Time {
  int hour_;
  int minute_;
  int second_;
  Time(int h, int m, int s) : hour_(h), minute_(m), second_(s) {}
  bool operator<(const Time& other) const {
    return hour_ < other.hour_ || hour_ == other.hour_ && minute_ < other.minute_ ||
           hour_ == other.hour_ && minute_ == other.minute_ && second_ < other.second_;
  }
  Time& operator=(const Time& other) {
    if (this != &other) {
      hour_ = other.hour_;
      minute_ = other.minute_;
      second_ = other.second_;
    }
    return *this;
  }
};

#define MAX_BUF 20

int main() {
  int M;
  scanf("%d", &M);
  char early_id[MAX_BUF], late_id[MAX_BUF], buf[MAX_BUF];
  Time early_t(23, 59, 59), late_t(0, 0, 0);
  for (int i = 0; i < M; i++) {
    int h1, m1, s1, h2, m2, s2;
    scanf("%s %d:%d:%d %d:%d:%d", buf, &h1, &m1, &s1, &h2, &m2, &s2);
    Time t1(h1, m1, s1), t2(h2, m2, s2);
    if (t1 < early_t) {
      strncpy(early_id, buf, MAX_BUF);
      early_t = t1;
    }
    if (late_t < t2) {
      strncpy(late_id, buf, MAX_BUF);
      late_t = t2;
    }
  }
  printf("%s %s\n", early_id, late_id);
}