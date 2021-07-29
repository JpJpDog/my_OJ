struct Solution;

impl Solution {
    fn merge(nums: &mut [i64], lower: i64, upper: i64) -> usize {
        let mut result = 0;
        let len = nums.len();
        let l1 = len >> 1;
        if l1 > 1 {
            result += Self::merge(&mut nums[..l1], lower, upper);
        }
        let l2 = len - l1;
        if l2 > 1 {
            result += Self::merge(&mut nums[l1..], lower, upper);
        }
        let mut j = l1;
        let mut k;
        for i in 0..l1 {
            while j < len && nums[j] - nums[i] < lower {
                j += 1;
            }
            k = j;
            while k < len && nums[k] - nums[i] <= upper {
                k += 1;
            }
            result += k - j;
        }
        let (mut i, mut j, mut k) = (0, 0, 0);
        let mut buf = vec![0; len];
        while i < l1 && j < l2 {
            if nums[i] < nums[l1 + j] {
                buf[k] = nums[i];
                i += 1;
            } else {
                buf[k] = nums[l1 + j];
                j += 1;
            }
            k += 1;
        }
        if i < l1 {
            buf[k..].copy_from_slice(&nums[i..l1]);
        } else if j < l2 {
            buf[k..].copy_from_slice(&nums[j + l1..]);
        }
        nums.copy_from_slice(&buf);
        result
    }

    pub fn count_range_sum(nums: Vec<i32>, lower: i32, upper: i32) -> i32 {
        let len = nums.len();
        if len == 0 {
            return 0;
        } else if len == 1 {
            return if lower <= nums[0] && nums[0] <= upper {
                1
            } else {
                0
            };
        }
        let mut pre_sum = vec![0; len + 1];
        for i in 1..len + 1 {
            pre_sum[i] = pre_sum[i - 1] + (nums[i - 1] as i64);
        }
        Self::merge(&mut pre_sum, lower as i64, upper as i64) as i32
    }
}

fn main() {
    println!("Hello, world!");
    let nums = vec![-2147483647, 0, -2147483647, 2147483647];
    let lower = -564;
    let upper = 3864;
    let r = Solution::count_range_sum(nums, lower, upper);
    println!("{}", r);
}
