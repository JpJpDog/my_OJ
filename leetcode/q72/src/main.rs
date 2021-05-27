use std::cmp::min;

struct Solution;

impl Solution {
    pub fn min_distance(word1: String, word2: String) -> i32 {
        let w1 = word1.as_bytes();
        let w2 = word2.as_bytes();
        let mut dp = vec![vec![0; w2.len() + 1]; w1.len() + 1];
        for j in 1..w2.len() + 1 {
            dp[0][j] = j as i32;
        }
        for i in 1..w1.len() + 1 {
            dp[i][0] = i as i32;
        }
        for i in 1..w1.len() + 1 {
            for j in 1..w2.len() + 1 {
                let mut tmp = dp[i - 1][j - 1];
                if w1[i - 1] != w2[j - 1] {
                    tmp += 1;
                }
                dp[i][j] = min(min(dp[i][j - 1] + 1, dp[i - 1][j] + 1), tmp);
            }
        }
        return dp[w1.len()][w2.len()];
    }
}

fn main() {
    println!("Hello, world!");
    let dist = Solution::min_distance(String::from("intention"), String::from("execution"));
    println!("dist is {}", dist);
}
