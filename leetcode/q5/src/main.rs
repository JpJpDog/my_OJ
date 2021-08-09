use std::mem::swap;

struct Solution;

impl Solution {
    pub fn longest_palindrome(s: String) -> String {
        let s = s.into_bytes();
        let mut prev2 = vec![true; s.len()];
        let mut prev = vec![true; s.len()];
        let mut cur = vec![true; s.len()];
        let mut record = (0, 0);
        let mut prev_found = true;
        for l in 1..s.len() {
            swap(&mut prev2, &mut prev);
            swap(&mut prev, &mut cur);
            let mut update = false;
            for i in 0..s.len() - l {
                cur[i] = prev2[i + 1] && s[i] == s[i + l];
                if cur[i] && !update {
                    update = true;
                    record = (i, l);
                }
            }
            if !update {
                if prev_found {
                    prev_found = false;
                }else{
                    break;
                }
            }else if !prev_found {
                prev_found = true;
            }
        }
        let (i, l) = record;
        return String::from_utf8(s[i..i + l + 1].to_vec()).unwrap();
    }
}

fn main() {
    println!("{}", Solution::longest_palindrome("abccbaa".to_string()));
}
