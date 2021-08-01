use std::collections::{HashMap, HashSet};


// use std::{
//     cmp::{max, min},
//     collections::HashMap,
// };

// struct SegTree {
//     max: usize,
//     data: Vec<i64>,
//     lazy: Vec<i64>,
// }

// impl SegTree {
//     fn init(d: &[i64], data: &mut [i64], idx: usize) -> i64 {
//         let l = d.len() - 1;
//         if l == 0 {
//             data[idx] = d[0];
//             return data[idx];
//         }
//         let mut sum = Self::init(&d[..(l >> 1) + 1], data, (idx << 1) + 1);
//         sum += Self::init(&d[(l >> 1) + 1..], data, (idx << 1) + 2);
//         data[idx] = sum;
//         sum
//     }

//     fn query_r(&mut self, idx: usize, l: usize, u: usize, lower: usize, upper: usize) -> i64 {
//         if l == lower && u == upper {
//             return self.data[idx];
//         }
//         let m = (l + u) >> 1;
//         let lazy = self.lazy[idx];
//         let li = (idx << 1) + 1;
//         let ri = (idx << 1) + 2;
//         if lazy != 0 {
//             self.data[li] += ((m - l + 1) as i64) * lazy;
//             self.lazy[li] += lazy;
//             self.data[ri] += ((u - m) as i64) * lazy;
//             self.lazy[ri] += lazy;
//             self.lazy[idx] = 0;
//         }
//         let mut sum = 0;
//         if lower <= m {
//             sum += self.query_r(li, l, m, lower, min(m, upper));
//         }
//         if upper >= m + 1 {
//             sum += self.query_r(ri, m + 1, u, max(lower, m + 1), upper);
//         }
//         sum
//     }

//     fn mutli_add_r(&mut self, idx: usize, l: usize, u: usize, lower: usize, upper: usize, add: i64) {
//         let n = (min(u, upper) - max(l, lower)) as i64 + 1;
//         self.data[idx] += n * add;
//         if l == lower && u == upper {
//             self.lazy[idx] += add;
//             return;
//         }
//         let m = (l + u) >> 1;
//         if lower <= m {
//             self.mutli_add_r((idx << 1) + 1, l, m, lower, min(m, upper), add);
//         }
//         if upper >= m + 1 {
//             self.mutli_add_r((idx << 1) + 2, m + 1, u, max(lower, m + 1), upper, add);
//         }
//     }
// }

// impl SegTree {
//     pub fn new(l: usize) -> Self {
//         let mut j = l;
//         let mut i = 0;
//         while j != 0 {
//             j >>= 1;
//             i += 1;
//         }
//         let len = 1 << (i + 1);
//         Self {
//             data: vec![0; len],
//             lazy: vec![0; len],
//             max: l - 1,
//         }
//     }

//     pub fn new_with_data(d: &[i64]) -> Self {
//         let mut j = d.len();
//         let mut i = 0;
//         while j != 0 {
//             j >>= 1;
//             i += 1;
//         }
//         let len = 1 << (i + 1);
//         let mut data = vec![0; len];
//         Self::init(d, &mut data, 0);
//         Self {
//             data,
//             lazy: vec![0; len],
//             max: d.len() - 1,
//         }
//     }

//     pub fn multi_add(&mut self, lower: usize, upper: usize, add: i64) {
//         self.mutli_add_r(0, 0, self.max, lower, upper, add);
//     }

//     pub fn query_sum(&mut self, lower: usize, upper: usize) -> i64 {
//         self.query_r(0, 0, self.max, lower, upper)
//     }
// }

// #[cfg(test)]
// mod test {
//     use super::*;

//     #[test]
//     fn test_init() {
//         let v = vec![4, 2, 6, 1, 6, 2, 6, 8, 11, 3, 1, 5, 2];
//         let mut tree = SegTree::new(&v);
//         println!("{}", tree.query_sum(5, 11));
//         tree.update(0, 12, -1);
//         println!("{}", tree.query_sum(5, 11));
//         tree.update(3, 12, 1);
//         tree.update(2, 10, 2);
//         println!("{}", tree.query_sum(0, 12));
//         println!("{}", tree.query_sum(5, 11));
//         println!("{}", tree.query_sum(0, 12));
//     }
// }

struct SegTree {
    data: Vec<i64>,
    l: usize,
}

impl SegTree {
    fn new(l: usize) -> Self {
        let mut j = l;
        let mut i = 0;
        while j != 0 {
            j >>= 1;
            i += 1;
        }
        let len = 1 << (i + 1);
        Self {
            data: vec![0; len],
            l,
        }
    }

    fn add_one(&mut self, idx: usize, add: i64) {
        let mut i = 0;
        let mut l = 0;
        let mut r = self.l - 1;
        while l < r {
            self.data[i] += add;
            let mid = (l + r) >> 1;
            if idx <= mid {
                i = (i << 1) + 1;
                r = mid;
            } else {
                i = (i << 1) + 2;
                l = mid + 1;
            }
        }
        self.data[i] += add;
    }

    fn query_sum(&self, mut lower: usize, mut upper: usize) -> i64 {
        let mut sum = 0;
        let mut st: Vec<(usize, usize, usize, usize, usize)> = vec![];
        let (mut idx, mut l, mut r) = (0, 0, self.l - 1);
        loop {
            // assert!(lower >= l && upper <= r);
            if l == lower && r == upper {
                sum += self.data[idx];
                if let Some(e) = st.pop() {
                    idx = e.0;
                    l = e.1;
                    r = e.2;
                    lower = e.3;
                    upper = e.4;
                } else {
                    break;
                }
            } else {
                let m = (l + r) >> 1;
                if lower <= m {
                    if upper >= m + 1 {
                        st.push(((idx << 1) + 2, m + 1, r, m + 1, upper));
                        upper = m;
                    }
                    idx = (idx << 1) + 1;
                    r = m;
                } else {
                    idx = (idx << 1) + 2;
                    l = m + 1;
                }
            }
        }
        sum
    }
}

pub struct Solution2;

impl Solution2 {
    pub fn count_range_sum(nums: Vec<i32>, lower: i32, upper: i32) -> i32 {
        let (lower, upper) = (lower as i64, upper as i64);
        let len = nums.len();
        let mut pre_sum = vec![0; len + 1];
        for i in 1..len + 1 {
            pre_sum[i] = pre_sum[i - 1] + nums[i - 1] as i64;
        }
        let mut set = HashSet::new();
        set.reserve(3 * pre_sum.len());
        for e in pre_sum.iter() {
            set.insert(*e);
            set.insert(*e - upper);
            set.insert(*e - lower);
        }
        let mut tmp = set.into_iter().collect::<Vec<_>>();
        tmp.sort();
        let mut map = HashMap::new();
        for (i, e) in tmp.iter().enumerate() {
            map.insert(*e, i);
        }
        let mut tree = SegTree::new(map.len());
        tree.add_one(*map.get(&0).unwrap(), 1);
        let mut sum = 0;
        for i in 1..(len + 1) {
            sum += tree.query_sum(
                *map.get(&(pre_sum[i] - upper)).unwrap(),
                *map.get(&(pre_sum[i] - lower)).unwrap(),
            );
            tree.add_one(*map.get(&pre_sum[i]).unwrap(), 1);
        }
        sum as i32
    }
}

#[test]
fn ttt() {
    let nums = vec![1, 2, 3, 4, 4, 5, -1, 2, 3, -3, -4, -1, -2, 3, -5];
    let lower = -2;
    let upper = 3;
    println!("{}", Solution2::count_range_sum(nums, lower, upper));
}
