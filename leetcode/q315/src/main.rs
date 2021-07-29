// use std::collections::{BTreeSet, HashMap};

// struct TreeArray {
//     data: Vec<i32>,
// }

// impl TreeArray {
//     #[inline]
//     fn low_bits(x: usize) -> usize {
//         x & -(x as isize) as usize
//     }

//     fn new(len: usize) -> Self {
//         Self { data: vec![0; len] }
//     }

//     #[allow(dead_code)]
//     fn new_with_vec(d: &Vec<i32>) -> Self {
//         let mut data = vec![0; d.len()];
//         for i in 0..data.len() {
//             let k = Self::low_bits(i + 1);
//             let mut j = 1;
//             while j < k {
//                 data[i] += data[i - j];
//                 j <<= 1;
//             }
//             data[i] += d[i];
//         }
//         Self { data }
//     }

//     fn add(&mut self, mut i: usize, v: i32) {
//         while i < self.data.len() {
//             self.data[i] += v;
//             i += Self::low_bits(i + 1);
//         }
//     }

//     fn query(&self, mut i: usize) -> i32 {
//         let mut sum = 0;
//         loop {
//             sum += self.data[i];
//             let k = Self::low_bits(i + 1);
//             if i + 1 == k {
//                 break;
//             }
//             i -= k;
//         }
//         sum
//     }
// }

// struct Solution;

// impl Solution {
//     pub fn count_smaller(nums: Vec<i32>) -> Vec<i32> {
//         let l1 = nums.len();
//         let mut set = BTreeSet::new();
//         for e in nums.iter() {
//             set.insert(*e);
//         }
//         let l2 = set.len();
//         let mut map = HashMap::new();
//         for (i, e) in set.into_iter().enumerate() {
//             map.insert(e, i);
//         }
//         let mut tree_arr = TreeArray::new(l2);
//         let mut r = vec![0; l1];
//         for i in (0..l1).rev() {
//             let idx = *map.get(&nums[i]).unwrap();
//             tree_arr.add(idx, 1);
//             r[i] = if idx == 0 { 0 } else { tree_arr.query(idx - 1) };
//         }
//         r
//     }
// }

// fn main() {
//     let v = vec![3, 4, 6, 2, 4, 1, 5, 7, 9];
//     println!("{:?}", Solution::count_smaller(v));
// }

struct Solution;

impl Solution {
    fn merge(nums: &mut [i32], result: &mut [i32], map: &mut [usize], off: usize) {
        let len = nums.len();
        let l1 = len >> 1;
        if l1 > 2 {
            Self::merge(&mut nums[0..l1], &mut result[0..l1], &mut map[0..l1], off);
        } else if l1 == 2 && nums[0] > nums[1] {
            nums.swap(0, 1);
            map.swap(0, 1);
            result[map[1] - off] += 1;
        }
        let l2 = len - l1;
        if l2 > 2 {
            Self::merge(&mut nums[l1..], &mut result[l1..], &mut map[l1..], off + l1);
        } else if l2 == 2 && nums[l1] > nums[l1 + 1] {
            nums.swap(l1, l1 + 1);
            map.swap(l1, l1 + 1);
            result[map[l1 + 1] - off] += 1;
        }
        let (mut i, mut j, mut k) = (0, 0, 0);
        let mut buf = vec![0; len];
        let mut map_buf = vec![0; len];
        while i < l1 && j < l2 {
            if nums[i] <= nums[j + l1] {
                buf[k] = nums[i];
                map_buf[k] = map[i];
                result[map_buf[k] - off] += j as i32;
                i += 1;
            } else {
                buf[k] = nums[j + l1];
                map_buf[k] = map[j + l1];
                j += 1;
            }
            k += 1;
        }
        if i < l1 {
            buf[k..].copy_from_slice(&nums[i..l1]);
            map_buf[k..].copy_from_slice(&map[i..l1]);
            for i in k..len {
                result[map_buf[i] - off] += l2 as i32;
            }
        } else if j < l2 {
            buf[k..].copy_from_slice(&nums[l1 + j..]);
            map_buf[k..].copy_from_slice(&map[l1 + j..]);
        }
        nums.swap_with_slice(&mut buf);
        map.swap_with_slice(&mut map_buf);
    }

    pub fn count_smaller(mut nums: Vec<i32>) -> Vec<i32> {
        let len = nums.len();
        let mut result = vec![0; len];
        if len <= 1 {
            return vec![0; len];
        }
        let mut map = vec![0; len];
        for i in 0..len {
            map[i] = i;
        }
        Self::merge(&mut nums, &mut result, &mut map, 0);
        result
    }
}

fn main() {
    let v = vec![3, 2, 5, 2, 5, 2, 7, 2, 7, 2, 9, 2, 1, 1, 3, 6, 7, 8, 4, 2];
    // let v = vec![3, 4, 2, 1, 3, 6, 2, 8, 2];
    let r = Solution::count_smaller(v);
    println!("{:?}", r);
}
