use std::cmp::{max, Ordering};

struct Solution;

const ALICE: &str = "Alice";
const BOB: &str = "Bob";
const TIE: &str = "Tie";

impl Solution {
    pub fn stone_game_iii(mut vs: Vec<i32>) -> String {
        let s_len = vs.len();
        vs.push(0);
        vs.push(0);
        let mut dp = vec![0; s_len + 3];
        for i in (0..s_len).rev() {
            let mut opt = vs[i] - dp[i + 1];
            opt = max(vs[i] + vs[i + 1] - dp[i + 2], opt);
            opt = max(vs[i] + vs[i + 1] + vs[i + 2] - dp[i + 3], opt);
            dp[i] = opt;
        }
        match dp[0].cmp(&0) {
            Ordering::Less => BOB.to_string(),
            Ordering::Equal => TIE.to_string(),
            Ordering::Greater => ALICE.to_string(),
        }
    }
}

fn main() {
    assert_eq!(Solution::stone_game_iii(vec![1, 2, 3, 7]), "Bob");
    assert_eq!(Solution::stone_game_iii(vec![1, 2, 3, -9]), "Alice");
    assert_eq!(Solution::stone_game_iii(vec![1, 2, 3, 6]), "Tie");
    assert_eq!(
        Solution::stone_game_iii(vec![1, 2, 3, -1, -2, -3, 7]),
        "Alice"
    );
    assert_eq!(Solution::stone_game_iii(vec![-1, -2, -3]), "Tie");
}
