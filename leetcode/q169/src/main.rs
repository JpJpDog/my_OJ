struct Solution;

impl Solution {
    pub fn majority_element(nums: Vec<i32>) -> i32 {
        let mut cnt = 1;
        let mut cur = nums[0];
        let mut i = 1;
        while i < nums.len() {
            if nums[i] != cur {
                if cnt == 0 {
                    cur = nums[i];
                } else {
                    cnt -= 1;
                }
            } else {
                cnt += 1;
            }
            i += 1;
        }
        cur
    }
}

fn main() {
    let nums = vec![1, 2, 3, 2, 1, 2, 3, 2, 1, 1, 1, 1, 1];
    println!("Hello, world!");
}
