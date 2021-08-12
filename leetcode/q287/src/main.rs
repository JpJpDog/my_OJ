struct Solution;

impl Solution {
    pub fn find_duplicate(nums: Vec<i32>) -> i32 {
        let (mut fast, mut slow) = (0, 0);
        loop {
            fast = nums[fast as usize];
            fast = nums[fast as usize];
            slow = nums[slow as usize];
            if fast == slow {
                break;
            }
        }
        let mut slow2 = 0;
        loop {
            slow = nums[slow as usize];
            slow2 = nums[slow2 as usize];
            if slow == slow2 {
                return slow;
            }
        }
    }
}

fn main() {
    println!(
        "{}",
        Solution::find_duplicate(vec![2, 5, 9, 6, 9, 3, 8, 9, 7, 1])
    );
}
