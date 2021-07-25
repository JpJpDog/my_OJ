use std::cmp::{max, min};

struct Solution;

impl Solution {
    pub fn stone_game_ii(piles: Vec<i32>) -> i32 {
        let p_len = piles.len();
        let mut sum = vec![0; p_len + 1];
        {
            let mut s = 0;
            for i in 1..p_len + 1 {
                s += piles[i - 1];
                sum[i] = s;
            }
        }
        let mut dp = vec![];
        for i in 0..p_len {
            let m_num = min(i / 2 + 1, p_len - i);
            dp.push(vec![0; m_num]);
        }
        dp[p_len - 1][0] = piles[p_len - 1];
        for i in (0..p_len - 1).rev() {
            for j in 0..dp[i].len() {
                let m = j + 1;
                let mut opt = i32::MIN;
                for x in 1..2 * j + 3 {
                    let e = x + i;
                    let tmp = if e >= p_len {
                        sum[p_len] - sum[i]
                    } else {
                        let mm = dp[e].len() - 1;
                        (sum[e] - sum[i]) - dp[e][min(mm, max(x, m) - 1)]
                    };
                    opt = max(opt, tmp);
                }
                dp[i][j] = opt;
            }
        }
        (dp[0][0] + piles.iter().sum::<i32>()) / 2
    }
}

fn main() {
    assert_eq!(Solution::stone_game_ii(vec![2, 7, 9, 4, 4]), 10);
    assert_eq!(Solution::stone_game_ii(vec![1, 2, 3, 4, 5, 100]), 104);
    assert_eq!(
        Solution::stone_game_ii(vec![77, 12, 64, 35, 28, 4, 87, 21, 20]),
        217
    );
}
