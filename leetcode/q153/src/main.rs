use std::cmp::min;

struct Solution;

impl Solution {
    pub fn find_min(nums: Vec<i32>) -> i32 {
        let mut result = i32::MAX;
        let (mut s, mut e) = (0, nums.len() as i32 - 1);
        loop {
            let m = (s + e) / 2;
            let (start, mid, end) = (nums[s as usize], nums[m as usize], nums[e as usize]);
            if start <= mid && mid <= end {
                return min(result, start);
            } else if start <= mid {
                result = min(start, result);
                s = m + 1;
            } else {
                result = min(mid, result);
                e = m - 1;
            }
        }
    }
}

fn main() {
    // println!("Hello, world!");
    // let nums = vec![3, 4, 5, 1, 2];
    // let nums = vec![4, 5, 6, 7, 0, 1, 2];
    let nums = vec![11, 13, 15, 17];
    println!("{}", Solution::find_min(nums));
}
