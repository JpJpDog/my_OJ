#include <stack>
#include <string>
#include <string_view>
#include <vector>
using namespace std;

class Solution {
  struct Record {
    int l_, idx_;
    Record(int l, int idx) : l_(l), idx_(idx) {}
  };

 public:
  vector<string> wordBreak(string s, vector<string>& wordDict) {
    string_view sv(s);
    int s_len = s.size(), w_size = wordDict.size();
    vector<vector<int>> last_w_idx(s_len + 1);
    last_w_idx[0].push_back(-1);
    for (int i = 1; i <= s_len; i++) {
      for (int j = 0; j < w_size; j++) {
        string& word = wordDict[j];
        int w_len = word.size();
        if (i >= w_len && !last_w_idx[i - w_len].empty() &&
            word == sv.substr(i - w_len, w_len)) {
          last_w_idx[i].push_back(j);
        }
      }
    }
    if (last_w_idx[s_len].empty()) return vector<string>();
    vector<string> result;
    stack<Record> st;
    vector<int> cur_w_idx;
    int cur_tail = 2 * s_len, cur_head = cur_tail;
    cur_w_idx.resize(cur_tail);
    st.push(Record(s_len, 0));
    while (true) {
      Record& top = st.top();
      if (last_w_idx[top.l_].size() == top.idx_) {
        st.pop();
        if (st.empty()) break;
        st.top().idx_++;
        cur_head++;
        continue;
      }
      cur_w_idx[--cur_head] = last_w_idx[top.l_][top.idx_];
      string& last_w = wordDict[last_w_idx[top.l_][top.idx_]];
      int last_len = last_w.size();
      if (last_len < top.l_ && !last_w_idx[top.l_ - last_len].empty()) {
        st.push(Record(top.l_ - last_w.size(), 0));
      } else if (last_len == top.l_) {
        string cur_str;
        cur_str.reserve(s_len);
        cur_str = wordDict[cur_w_idx[cur_head]];
        for (int i = cur_head + 1; i < cur_tail; i++) {
          cur_str += " ";
          cur_str += wordDict[cur_w_idx[i]];
        }
        result.emplace_back(cur_str);
        top.idx_++;
        cur_head++;
      }
    }
    return result;
  }
};

#include <iostream>

int main() {
  string s = "catsanddog";
  vector<string> wordDict = {"cat", "cats", "and", "sand", "dog"};
  Solution sol;
  auto answer = sol.wordBreak(s, wordDict);
  for (auto s : answer) {
    cout << s << std::endl;
  }
}