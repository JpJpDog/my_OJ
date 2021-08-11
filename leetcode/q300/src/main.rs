use std::cmp::max;

struct Solution;

impl Solution {
    fn find_first_not_less(arr: &[i32], key: i32) -> usize {
        let (mut start, mut end) = (0, arr.len());
        while start < end {
            let mid = (start + end) / 2;
            if arr[mid] < key {
                start = mid + 1;
            } else {
                end = mid;
            }
        }
        start
    }

    pub fn length_of_lis(nums: Vec<i32>) -> i32 {
        let mut dp = vec![0; nums.len()];
        dp[0] = nums[0];
        let mut dp_len = 1;
        for i in 1..nums.len() {
            let j = Self::find_first_not_less(&dp[..dp_len], nums[i]);
            dp[j] = nums[i];
            dp_len = max(j + 1, dp_len);
        }
        dp_len as i32
    }
}

fn main() {
    let nums = vec![5, 4, 3, 2, 1];
    // let nums = vec![10, 9, 2, 5, 3, 7, 101, 18];
    println!("{}", Solution::length_of_lis(nums));
}
