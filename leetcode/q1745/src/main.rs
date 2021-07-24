struct Solution;

impl Solution {
    pub fn check_partitioning(s: String) -> bool {
        let s = s.as_bytes();
        let mut check = vec![vec![true; s.len()]; s.len()];
        for l in 1..s.len() {
            for i in 0..s.len() - l {
                let j = i + l;
                check[i][j] = check[i + 1][j - 1] && s[i] == s[j];
            }
        }
        for i in 0..s.len() - 2 {
            for j in i + 1..s.len() - 1 {
                if check[0][i] && check[i + 1][j] && check[j + 1][s.len() - 1] {
                    return true;
                }
            }
        }
        false
    }
}

fn main() {
    let s = "abaaba".to_string();
    println!("{}", Solution::check_partitioning(s));
}
