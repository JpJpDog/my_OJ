#include <algorithm>
#include <vector>

class Solution {
 public:
  int threeSumClosest(std::vector<int>& nums, int target) {
    std::sort(nums.begin(), nums.end());
    int num_len = nums.size();
    std::vector<int> next(num_len), prev(num_len);
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
    int cur_result = 2000000, cur_diff = 2000000;
    for (int i = 0; i < num_len; i += next[i]) {
      int j = i + 1, k = num_len - 1;
      while (j < k) {
        int diff, sum;
        if (std::abs(diff = (sum = nums[i] + nums[j] + nums[k]) - target) <
            cur_diff) {
          cur_diff = std::abs(diff);
          cur_result = sum;
        }
        if (diff == 0) {
          break;
        }
        if (diff < 0) {
          j += next[j];
        } else {
          k -= prev[k];
        }
      }
    }
    return cur_result;
  }
};
