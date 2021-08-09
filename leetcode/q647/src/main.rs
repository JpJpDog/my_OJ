struct Solution;

impl Solution {
    pub fn count_substrings(s: String) -> i32 {
        let s = s.into_bytes();
        let mut dp = vec![true; s.len()];
        let mut cnt = s.len() as i32;
        for l in 1..s.len() {
            for i in 0..s.len() - l {
                dp[i] = dp[i + 1] && s[i] == s[i + l];
                if dp[i] {
                    cnt += 1;
                }
            }
        }
        cnt
    }
}

fn main() {
    println!("{}", Solution::count_substrings("aaaabc".to_string()));
}
