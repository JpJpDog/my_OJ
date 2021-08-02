use std::collections::VecDeque;

struct Solution;

impl Solution {
    fn push(qu: &mut VecDeque<usize>, idx: usize, nums: &[i32]) {
        let key = nums[idx];
        while let Some(last_idx) = qu.back() {
            if nums[*last_idx] < key {
                qu.pop_back();
            } else {
                break;
            }
        }
        qu.push_back(idx);
    }

    pub fn max_sliding_window(nums: Vec<i32>, k: i32) -> Vec<i32> {
        let k = k as usize;
        let mut qu = VecDeque::new();
        let mut idx = 0;
        while idx < k {
            Self::push(&mut qu, idx, &nums);
            idx += 1;
        }
        let mut result = vec![];
        result.reserve(nums.len() - k + 1);
        result.push(nums[*qu.front().unwrap()]);
        while idx < nums.len() {
            if *qu.front().unwrap() == idx - k {
                qu.pop_front();
            }
            Self::push(&mut qu, idx, &nums);
            result.push(nums[*qu.front().unwrap()]);
            idx += 1;
        }
        result
    }
}

fn main() {
    let nums = vec![1, 3, -1, -3, 5, 3, 6, 7];
    let k = 3;
    println!("{:?}", Solution::max_sliding_window(nums, k));
}
