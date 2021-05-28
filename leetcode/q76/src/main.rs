use std::collections::HashSet;

struct CheckMap {
    t_map: Vec<i32>,
    ch_count: u32,
}

impl CheckMap {
    fn new(t: &[u8]) -> Self {
        let mut t_map = vec![0; u8::MAX as usize + 1];
        let mut ch_set = HashSet::new();
        let mut ch_count = 0;
        for ch in t {
            t_map[*ch as usize] += 1;
            if ch_set.insert(*ch) {
                ch_count += 1;
            }
        }
        CheckMap { t_map, ch_count }
    }
    #[inline]
    fn check(&self) -> bool {
        self.ch_count == 0
    }
    #[inline]
    fn insert(&mut self, ch: u8) {
        self.t_map[ch as usize] -= 1;
        if self.t_map[ch as usize] == 0 {
            self.ch_count -= 1;
        }
    }
    #[inline]
    fn remove(&mut self, ch: u8) {
        self.t_map[ch as usize] += 1;
        if self.t_map[ch as usize] == 1 {
            self.ch_count += 1;
        }
    }
}
struct Solution;
impl Solution {
    fn prepare(s: &[u8], t: &[u8]) -> (CheckMap, Vec<u8>, Vec<usize>) {
        let cm = CheckMap::new(t);
        let mut dist = vec![];
        let mut s1 = vec![];
        let mut d = 0;
        for ch in s {
            if cm.t_map[*ch as usize] != 0 {
                s1.push(*ch);
                dist.push(d);
            }
            d += 1;
        }
        (cm, s1, dist)
    }
    pub fn min_window(s1: String, t: String) -> String {
        let t = t.as_bytes();
        let (mut cm, s, dist) = Solution::prepare(s1.as_bytes(), t);
        let mut left = 0;
        let mut right = 0;
        let mut min_len = s1.len() + 1;
        let mut min_left = 0;
        let mut min_right = 0;
        while right < s.len() {
            while !cm.check() && right < s.len() {
                let ch = s[right];
                cm.insert(ch);
                right += 1;
            }
            if !cm.check() {
                break;
            }
            while cm.check() {
                let ch = s[left];
                cm.remove(ch);
                left += 1;
            }
            let tmp_len = dist[right - 1] - dist[left - 1] + 1;
            if tmp_len < min_len {
                min_len = tmp_len;
                min_left = left - 1;
                min_right = right;
            }
        }
        if min_right == 0 {
            return "".to_string();
        }
        s1[dist[min_left]..dist[min_right - 1] + 1].to_string()
    }
}

fn main() {
    println!("Hello, world!");
    let s = Solution::min_window("aa".to_string(), "aaa".to_string());
    println!("{}", s);
}
