#include <vector>
using namespace std;

class Solution {
 public:

  int singleNumber(vector<int>& nums) {
    int t1 = 0, t2 = 0, tmp;
    for (auto n : nums) {
      t2 ^= t1 & n;
      t1 ^= n;
      tmp = ~(t1 & t2);
      t1 &= tmp;
      t2 &= tmp;
    }
    return t1;
  }
};

int main() {
  vector<int> nums = {2, 2, 2, 3};
  Solution sol;
  int result = sol.singleNumber(nums);
}