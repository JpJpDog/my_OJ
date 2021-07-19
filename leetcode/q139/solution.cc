#include <string>
#include <string_view>
#include <vector>
using namespace std;

class Solution {
 public:
  bool wordBreak(string s, vector<string>& wordDict) {
    string_view sv(s);
    int s_len = s.size();
    vector<bool> dp(s_len + 1, false);
    dp[0] = true;
    for (int i = 1; i <= s_len; i++) {
      for (auto& word : wordDict) {
        int w_len = word.size();
        if (i >= w_len && dp[i - w_len] && word == sv.substr(i - w_len, w_len)) {
          dp[i] = true;
        }
      }
    }
    return dp[s_len];
  }
};
