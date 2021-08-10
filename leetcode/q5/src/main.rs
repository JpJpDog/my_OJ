struct Solution;

impl Solution {
    pub fn longest_palindrome(s: String) -> String {
        let s1 = s.into_bytes();
        let mut s = vec![0; s1.len() * 2 - 1];
        for i in 0..s1.len() {
            s[2 * i] = s1[i];
        }
        let mut dp = vec![0; s.len()];
        dp[0] = 1;
        let (mut center, mut right) = (0, 1);
        let mut max_i = s.len() - 1;
        for i in 1..s.len() {
            if i < right {
                let j = 2 * center - i;
                if j + 1 - dp[j] <= 2 * center + 1 - right {
                    let mut k = right;
                    while k < s.len() && 2 * i >= k && s[k] == s[2 * i - k] {
                        k += 1;
                    }
                    center = i;
                    right = k;
                    dp[i] = k - i;
                } else {
                    dp[i] = dp[j];
                }
            } else {
                let mut k = i + 1;
                while k < s.len() && 2 * i >= k && s[k] == s[2 * i - k] {
                    k += 1;
                }
                center = i;
                right = k;
                dp[i] = k - i;
            }
            if right == s.len() {
                max_i = i;
                break;
            }
        }
        let (mut max_s, mut max_e) = (0, 0);
        for (i, r) in dp[..max_i + 1].into_iter().enumerate() {
            let s = (i + 2 - r) / 2;
            let e = (i + r - 1) / 2 + 1;
            if e - s > max_e - max_s {
                max_s = s;
                max_e = e;
            }
        }
        String::from_utf8(s1[max_s..max_e].to_vec()).unwrap()
    }
}

fn main() {
    let s = "bb".to_string();
    println!("{}", Solution::longest_palindrome(s));
}
