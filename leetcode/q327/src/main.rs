use crate::solution1::Solution1;

mod solution1;
mod solution2;

fn main() {
    println!("Hello, world!");
    let nums = vec![1, 2, 3, 4, 4, 5, -1, 2, 3, -3, -4, -1, -2, 3, -5];
    let lower = -2;
    let upper = 3;
    let r = Solution1::count_range_sum(nums, lower, upper);
    println!("{}", r);
}
