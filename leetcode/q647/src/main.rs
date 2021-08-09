use std::mem::swap;

struct Solution;

impl Solution {
    pub fn count_substrings(s: String) -> i32 {
        let s = s.into_bytes();
        let mut prev2 = vec![true; s.len()];
        let mut prev = vec![true; s.len()];
        let mut cur = vec![true; s.len()];
        let mut cnt = s.len() as i32;
        for l in 1..s.len() {
            swap(&mut prev2, &mut prev);
            swap(&mut prev, &mut cur);
            for i in 0..s.len() - l {
                cur[i] = prev2[i + 1] && s[i] == s[i + l];
                if cur[i] {
                    cnt += 1;
                }
            }
        }
        cnt
    }
}

fn main() {
    println!("{}", Solution::count_substrings("abcba".to_string()));
}
