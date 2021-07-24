use std::cmp::max;

struct Solution;

impl Solution {
    pub fn stone_game(piles: Vec<i32>) -> bool {
        let p_len = piles.len();
        let mut dp = vec![vec![0; p_len]; p_len];
        for i in 0..p_len {
            dp[i][i] = piles[i];
        }
        for l in 1..p_len {
            for i in 0..(p_len - l) {
                let j = i + l;
                dp[i][j] = max(piles[i] - dp[i + 1][j], piles[j] - dp[i][j - 1]);
            }
        }
        dp[0][p_len - 1] > 0
    }
}

fn main() {
    println!("{}", Solution::stone_game(vec![1, 2, 3, 4, 5, 6]));
}
