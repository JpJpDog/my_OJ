use std::{cmp::min, mem::swap};

struct Solution;

impl Solution {
    pub fn palindrome_partition(s: String, k: i32) -> i32 {
        let k = k as usize;
        let s = s.as_bytes();
        let mut change = vec![vec![0; s.len()]; s.len()];
        for l in 1..s.len() {
            for i in 0..s.len() - l {
                let j = i + l;
                change[i][j] = if s[i] == s[j] {
                    change[i + 1][j - 1]
                } else {
                    change[i + 1][j - 1] + 1
                };
            }
        }
        let mut dp = vec![0; s.len()];
        let mut prev_dp = vec![0; s.len()];
        for i in 0..s.len() {
            prev_dp[i] = change[0][i];
        }
        for j in 0..k {
            for i in j + 1..s.len() {
                let mut opt = i32::MAX;
                for m in j..i {
                    opt = min(opt, prev_dp[m] + change[m + 1][i]);
                }
                dp[i] = opt;
            }
            swap(&mut prev_dp, &mut dp);
        }
        dp[s.len() - 1]
    }
}

fn main() {
    let s = "aaaaacbbbc".to_string();
    let k = 2;
    let result = Solution::palindrome_partition(s, k);
    println!("{}", result);
}
