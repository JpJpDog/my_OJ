struct Solution;

impl Solution {
    pub fn find_peak_element(nums: Vec<i32>) -> i32 {
        let (mut s, mut e) = (0, nums.len() as i32 - 1);
        while s < e {
            let m = (s + e) / 2;
            if nums[m as usize] > nums[m as usize + 1] {
                e = m;
            } else {
                s = m + 1;
            }
        }
        s as i32
    }
}

fn main() {
    println!("Hello, world!");
}
