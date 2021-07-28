use std::collections::{BTreeSet, HashMap};

struct TreeArray {
    data: Vec<i32>,
}

impl TreeArray {
    #[inline]
    fn low_bits(x: usize) -> usize {
        x & -(x as isize) as usize
    }

    fn new(len: usize) -> Self {
        Self { data: vec![0; len] }
    }

    #[allow(dead_code)]
    fn new_with_vec(d: &Vec<i32>) -> Self {
        let mut data = vec![0; d.len()];
        for i in 0..data.len() {
            let k = Self::low_bits(i + 1);
            let mut j = 1;
            while j < k {
                data[i] += data[i - j];
                j <<= 1;
            }
            data[i] += d[i];
        }
        Self { data }
    }

    fn add(&mut self, mut i: usize, v: i32) {
        while i < self.data.len() {
            self.data[i] += v;
            i += Self::low_bits(i + 1);
        }
    }

    fn query(&self, mut i: usize) -> i32 {
        let mut sum = 0;
        loop {
            sum += self.data[i];
            let k = Self::low_bits(i + 1);
            if i + 1 == k {
                break;
            }
            i -= k;
        }
        sum
    }
}

struct Solution;

impl Solution {
    pub fn count_smaller(nums: Vec<i32>) -> Vec<i32> {
        let l1 = nums.len();
        let mut set = BTreeSet::new();
        for e in nums.iter() {
            set.insert(*e);
        }
        let l2 = set.len();
        let mut map = HashMap::new();
        for (i, e) in set.into_iter().enumerate() {
            map.insert(e, i);
        }
        let mut tree_arr = TreeArray::new(l2);
        let mut r = vec![0; l1];
        for i in (0..l1).rev() {
            let idx = *map.get(&nums[i]).unwrap();
            tree_arr.add(idx, 1);
            r[i] = if idx == 0 { 0 } else { tree_arr.query(idx - 1) };
        }
        r
    }
}

fn main() {
    let v = vec![3, 4, 6, 2, 4, 1, 5, 7, 9];
    println!("{:?}", Solution::count_smaller(v));
}
