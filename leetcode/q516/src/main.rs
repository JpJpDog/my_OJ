use std::{cmp::max, mem::swap};

struct Solution;

impl Solution {
    pub fn longest_palindrome_subseq(s: String) -> i32 {
        let s = s.into_bytes();
        let mut prev_dp = vec![0; s.len()];
        let mut dp = vec![1; s.len()];
        let mut new_dp = vec![0; s.len()];
        for l in 1..s.len() {
            for i in 0..s.len() - l {
                new_dp[i] = if s[i] == s[i + l] {
                    prev_dp[i + 1] + 2
                } else {
                    max(dp[i], dp[i + 1])
                };
            }
            swap(&mut dp, &mut prev_dp);
            swap(&mut new_dp, &mut dp);
        }
        let mut result = 0;
        for d in dp {
            result = max(d, result);
        }
        result
    }
}

fn main() {}
