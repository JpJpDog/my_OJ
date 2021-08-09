use std::cmp::min;

struct Solution;

impl Solution {
    pub fn nth_super_ugly_number(n: i32, primes: Vec<i32>) -> i32 {
        if n == 1 {
            return 1;
        }
        let mut dp = vec![0; n as usize];
        dp[0] = 1;
        let mut ps = vec![0; primes.len()];
        for i in 1..dp.len() {
            let mut opt = i32::MAX;
            for (idx, p) in ps.iter().cloned().enumerate() {
                opt = min(opt, primes[idx] * dp[p]);
            }
            dp[i] = opt;
            for (idx, p) in ps.iter_mut().enumerate() {
                if opt == primes[idx] * dp[*p] {
                    *p += 1;
                }
            }
        }
        dp[n as usize - 1]
    }
}

fn main() {
    println!(
        "{}",
        Solution::nth_super_ugly_number(12, vec![2, 7, 13, 19])
    );
}
