#include <algorithm>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<vector<int>> threeSum(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    int num_len = nums.size();
    vector<int> next(num_len), prev(num_len);
    int cur_start = 0;
    for (int i = 1; i < num_len; i++) {
      if (nums[i] != nums[cur_start]) {
        for (int j = cur_start; j < i; j++) {
          next[j] = i - j;
          prev[j] = j - cur_start + 1;
        }
        cur_start = i;
      }
    }
    for (int j = cur_start; j < num_len; j++) {
      next[j] = num_len - j;
      prev[j] = j - cur_start + 1;
    }
    vector<vector<int>> result;
    for (int i = 0; i < num_len; i += next[i]) {
      if (nums[i] > 0) break;
      int j = i + 1, k = num_len - 1;
      while (j < k) {
        int sum;
        if ((sum = nums[i] + nums[j] + nums[k]) == 0) {
          result.push_back({nums[i], nums[j], nums[k]});
          j += next[j];
          k -= prev[k];
        } else if (sum < 0) {
          j += next[j];
        } else {
          k -= prev[k];
        }
      }
    }
    return result;
  }
};
