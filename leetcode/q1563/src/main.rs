use std::cmp::{max, Ordering};

struct Solution;

impl Solution {
    pub fn stone_game_v(vs: Vec<i32>) -> i32 {
        let v_len = vs.len();
        let mut sum = vec![0; v_len + 1];
        {
            let mut s = 0;
            for i in 1..v_len + 1 {
                s += vs[i - 1];
                sum[i] = s;
            }
        }
        let mut dp = vec![vec![0; v_len]; v_len];
        for l in 1..v_len {
            for i in 0..v_len - l {
                let j = i + l;
                let mut opt = i32::MIN;
                for k in i..j {
                    // [i,k],[k+1,j]
                    let l_s = sum[k + 1] - sum[i];
                    let r_s = sum[j + 1] - sum[k + 1];
                    let tmp = match l_s.cmp(&r_s) {
                        Ordering::Less => l_s + dp[i][k],
                        Ordering::Equal => l_s + max(dp[i][k], dp[k + 1][j]),
                        Ordering::Greater => r_s + dp[k + 1][j],
                    };
                    opt = max(opt, tmp);
                }
                dp[i][j] = opt;
            }
        }
        dp[0][v_len - 1]
    }
}

fn main() {
    assert_eq!(Solution::stone_game_v(vec![6, 2, 3, 4, 5, 5]), 18);
    assert_eq!(Solution::stone_game_v(vec![7, 7, 7, 7, 7, 7, 7]), 28);
    // assert_eq!(Solution::stone_game_v(vec![4]), 0);
}
