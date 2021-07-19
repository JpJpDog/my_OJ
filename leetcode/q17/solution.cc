#include <string>
#include <vector>

using namespace std;

class Solution {
  vector<string> table_ = {"abc", "def",  "ghi", "jkl",
                           "mno", "pqrs", "tuv", "wxyz"};

 public:
  vector<string> letterCombinations(string digits) {
    if (!digits.size()) return vector<string>();
    int str_len = digits.size();
    vector<string> table(str_len);
    vector<int> max_idx(str_len);
    for (int i = 0; i < str_len; i++) {
      table[i] = table_[digits[i] - '2'];
      max_idx[i] = table[i].size() - 1;
    }
    string cur_str;
    cur_str.resize(str_len);
    for (int i = 0; i < str_len - 1; i++) {
      cur_str[i] = table[i][0];
    }
    vector<int> cur_idx(str_len - 1, 0);
    string &last_t = table[str_len - 1];
    vector<string> result;
    while (true) {
      for (auto ch : last_t) {
        cur_str[str_len - 1] = ch;
        result.push_back(cur_str);
      }
      int add_i;
      for (add_i = str_len - 2; add_i >= 0 && cur_idx[add_i] == max_idx[add_i];
           add_i--)
        ;
      if (add_i < 0) break;
      int idx = ++cur_idx[add_i];
      cur_str[add_i] = table[add_i][idx];
      for (int i = add_i + 1; i < str_len - 1; i++) {
        cur_str[i] = table[i][0];
        cur_idx[i] = 0;
      }
    }
    return result;
  }
};
