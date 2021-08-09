struct Solution;

impl Solution {
    pub fn count_substrings(s: String) -> i32 {
        let s = s.into_bytes();
        let mut dp = vec![vec![]; s.len()];
        for (i, v) in dp.iter_mut().enumerate() {
            v.resize(s.len() - i + 1, false);
            v[1] = true;
        }
        let mut cnt = s.len() as i32;
        for l in 2..s.len() + 1 {
            for i in 0..s.len() - l + 1 {
                dp[i][l] = if dp[i + 1][l - 2] && s[i] == s[i + l - 1] {
                    cnt += 1;
                    true
                } else {
                    false
                };
            }
        }
        cnt
    }
}

fn main() {
    println!("{}", Solution::count_substrings("abc".to_string()));
}
