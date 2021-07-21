use std::{cmp::max, mem::swap};

struct Solution;

impl Solution {
    pub fn super_egg_drop(k: i32, n: i32) -> i32 {
        let (k, n) = (k as usize, n as usize);
        let mut dp = vec![0; n + 1];
        let mut p_dp = vec![0; n + 1];
        for floor_n in 1..n + 1 {
            p_dp[floor_n] = floor_n as i32;
        }
        for _egg_n in 2..k + 1 {
            let mut test = 1;
            for f_n in 1..n + 1 {
                let mut opt = max(p_dp[test - 1], dp[f_n - test]);
                while test < f_n {
                    let nxt = max(p_dp[test], dp[f_n - test - 1]);
                    if opt <= nxt {
                        break;
                    }
                    test += 1;
                    opt = nxt;
                }
                dp[f_n] = opt + 1;
            }
            swap(&mut p_dp, &mut dp);
        }
        p_dp[n]
    }
}

fn main() {
    let k = 4;
    let n = 13;
    println!("{}", Solution::super_egg_drop(k, n));
}
