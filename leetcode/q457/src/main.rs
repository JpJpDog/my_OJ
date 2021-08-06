struct Solution;

impl Solution {
    #[inline]
    fn step1(nums: &[i32], cur: &mut usize) {
        let mut old = *cur as i32;
        old += nums[*cur];
        old %= nums.len() as i32;
        if old < 0 {
            old += nums.len() as i32
        }
        *cur = old as usize;
    }

    #[inline]
    fn step2(nums: &mut [i32], cur: &mut usize, start: i32) -> bool {
        Self::step1(nums, cur);
        let v = nums[*cur];
        if v * start <= 0 {
            return false;
        }
        Self::step1(nums, cur);
        let v = nums[*cur];
        if v * start <= 0 {
            return false;
        }
        true
    }

    pub fn circular_array_loop(mut nums: Vec<i32>) -> bool {
        let len = nums.len() as i32;
        for e in nums.iter_mut() {
            if *e % len == 0 {
                *e = 0;
            }
        }
        for i in 0..nums.len() {
            let start = nums[i];
            if start == 0 {
                continue;
            }
            let mut fast = i;
            let mut slow = i;
            if loop {
                if !Self::step2(&mut nums, &mut fast, start) {
                    break false;
                }
                Self::step1(&mut nums, &mut slow);
                if slow == fast {
                    break true;
                }
            } {
                return true;
            } else {
                let mut t = i;
                while nums[t] * start > 0 {
                    let tmp = t;
                    Self::step1(&mut nums, &mut t);
                    nums[tmp] = 0;
                }
            }
        }
        false
    }
}

fn main() {
    let nums = vec![-1, -2, -3, -4, -5];
    println!("{}", Solution::circular_array_loop(nums));
}
