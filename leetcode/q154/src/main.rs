use std::cmp::min;

struct Solution;

impl Solution {
    pub fn find_min(nums: Vec<i32>) -> i32 {
        let (mut s, mut e) = (0, nums.len() as i32 - 1);
        let mut result = i32::MAX;
        loop {
            let m = (s + e) / 2;
            let (start, mid, end) = (nums[s as usize], nums[m as usize], nums[e as usize]);
            if start == mid && mid == end {
                if s + 1 >= e {
                    return min(result, start);
                }
                s += 1;
                e -= 1;
            } else if start <= mid && mid <= end {
                return min(result, start);
            } else if start > mid {
                e = m - 1;
                result = min(result, mid);
            } else {
                s = m + 1;
                result = min(result, start);
            }
        }
    }
}

fn main() {
    // let nums = vec![1, 3, 5];
    // let nums = vec![2, 2, 2, 0, 1];
    // let nums = vec![2, 2, 2, 2, 2];
    // let nums = vec![1, 1];
    let nums = vec![3, 1, 1];
    println!("{}", Solution::find_min(nums));
}
