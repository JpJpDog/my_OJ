#include <cstdio>
#include <cstring>
#include <regex>
#include <vector>

const int kMaxBuf = 1001;

char buf[kMaxBuf];
char buf1[kMaxBuf];

typedef std::vector<std::string> Route;
typedef std::vector<std::string *> RouteRef;

Route cur_route;

bool parse(const char *str, Route &r) {
  const char *str1 = str;
  std::regex rgx("/[^/]*"), rgx1("[^/]*");
  std::cmatch cm;
  bool abs = true;
  if (str1[0] != '/') {
    std::regex_search(str1, cm, rgx1);
    r.push_back("/" + std::string(cm.begin()->first, cm.begin()->second));
    str1 += cm.length();
    abs = false;
  }
  while (std::regex_search(str1, cm, rgx)) {
    r.push_back(std::string(cm.begin()->first, cm.begin()->second));
    str1 += cm.length();
  }
  return abs;
}

void canonical(const char *str, char *result) {
  Route route;
  bool abs = parse(str, route);
  RouteRef canon_route;
  if (!abs) {
    for (int i = 0; i < cur_route.size(); i++) {
      canon_route.push_back(&cur_route[i]);
    }
  }
  for (auto &s : route) {
    if (s == "/..") {
      if (!canon_route.empty()) {
        canon_route.pop_back();
      }
    } else if (s != "/." && s != "/") {
      canon_route.push_back(&s);
    }
  }
  if (canon_route.empty()) {
    result[0] = '/';
    result[1] = '\0';
    return;
  }
  char *r = result;
  for (auto ps : canon_route) {
    strcpy(r, ps->c_str());
    r += ps->size();
  }
  *r = '\0';
}

int main() {
  int P;
  scanf("%d", &P);
  scanf("%s\n", buf);
  parse(buf, cur_route);
  for (int i = 0; i < P; i++) {
    fgets(buf, kMaxBuf, stdin);
    buf[strlen(buf) - 1] = '\0';
    canonical(buf, buf1);
    printf("%s\n", buf1);
  }
}
