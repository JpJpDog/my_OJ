struct Solution;

impl Solution {
    pub fn winner_square_game(n: i32) -> bool {
        let n = n as usize;
        let mut dp = vec![false; n + 1];
        let mut k = 1;
        for i in 1..n + 1 {
            if (k + 1) * (k + 1) <= i {
                k += 1;
            }
            let mut opt = false;
            for j in 1..(k + 1) {
                if !dp[i - j * j] {
                    opt = true;
                }
            }
            dp[i] = opt;
        }
        dp[n]
    }
}

fn main() {
    println!("{}", Solution::winner_square_game(1));
    println!("{}", Solution::winner_square_game(2));
    println!("{}", Solution::winner_square_game(4));
    println!("{}", Solution::winner_square_game(7));
    println!("{}", Solution::winner_square_game(17));
}
