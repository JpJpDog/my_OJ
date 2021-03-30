#include <algorithm>
#include <cstdio>
#include <deque>
#include <vector>

const int minus_inf = 0x80000000;

int two_maxsum(const std::vector<int>& arr) {
  // max_end is the max subsum end with arr[i] after every iterationi
  // max_start is the max subsum start with arr[i] after every iteration
  // max_b is the maxsum of max_before[0,i-1]
  // max_a is the maxsum of max_after[i+1,n-1]
  // max_before[i] is the maxsum in [0,i]
  // max_after[i] is the maxsum in [i,n-1]
  int n = arr.size();
  std::vector<int> max_before(n), max_after(n);
  int result = minus_inf;
  int max_end = arr[0], max_b = arr[0];
  max_before[0] = arr[0];
  for (int i = 1; i < n; i++) {
    max_end = std::max(max_end, 0) + arr[i];
    max_before[i] = max_b = std::max(max_b, max_end);
  }
  int max_start = arr[n - 1], max_a = arr[n - 1];
  max_after[n - 1] = arr[n - 1];
  for (int i = n - 2; i >= 0; i--) {
    max_start = std::max(max_start, 0) + arr[i];
    max_after[i] = max_a = std::max(max_a, max_start);
  }
  // i is the diameter
  for (int i = 0; i < n - 1; i++) {
    result = std::max(result, max_before[i] + max_after[i + 1]);
  }
  return result;
}

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> arr(n);
  int sum = 0;
  for (int i = 0; i < n; i++) {
    int tmp;
    scanf("%d", &tmp);
    sum += arr[i] = tmp;
  }
  int result = two_maxsum(arr);
  for (int i = 0; i < n; i++) {
    arr[i] = -arr[i];
  }
  int result2 = two_maxsum(arr) + sum;
  // result2==0 may choose all element in minus_arr which is not allowed
  // or it not choose some 0, and result must be 0 which can be detected by result1
  if (result2 != 0) {
    result = std::max(result2, result);
  }
  printf("%d\n", result);
}