use std::cmp::min;

struct Solution;

impl Solution {
    pub fn find_median_sorted_arrays(nums1: Vec<i32>, nums2: Vec<i32>) -> f64 {
        let (l1, l2) = (nums1.len(), nums2.len());
        assert!(l1 + l2 > 0);
        let mut k = (l1 + l2 - 1) / 2;
        let (mut off1, mut off2) = (0, 0);
        let m1 = loop {
            if off2 == l2 {
                off1 += k + 1;
                break nums1[off1 - 1];
            }
            if off1 == l1 {
                off2 += k + 1;
                break nums2[off2 - 1];
            }
            if k == 0 {
                if nums1[off1] > nums2[off2] {
                    off2 += 1;
                    break nums2[off2 - 1];
                } else {
                    off1 += 1;
                    break nums1[off1 - 1];
                }
            }
            let i = (k - 1) / 2; // (k-1)/2 * 2 < k
            let (v1, f1) = (nums1[min(off1 + i, l1 - 1)], min(i + 1, l1 - off1));
            let (v2, f2) = (nums2[min(off2 + i, l2 - 1)], min(i + 1, l2 - off2));
            if v1 > v2 {
                k -= f2;
                off2 += f2;
            } else {
                k -= f1;
                off1 += f1;
            }
        };
        if (l1 + l2) % 2 == 1 {
            m1 as f64
        } else {
            let m2 = if l1 == off1 {
                nums2[off2]
            } else if l2 == off2 {
                nums1[off1]
            } else {
                min(nums1[off1], nums2[off2])
            };
            (m1 + m2) as f64 / 2.0
        }
    }
}

fn main() {
    let nums1 = vec![];
    let nums2 = vec![1, 2, 3, 4, 5, 6, 7, 8];
    println!("{}", Solution::find_median_sorted_arrays(nums1, nums2));
    // let nums1 = vec![1, 3, 5, 6, 9, 15, 16, 17, 18, 19, 20];
    // let nums2 = vec![2, 4, 7, 8, 10, 11, 12, 13, 14];
    // for i in 1..nums1.len() + 1 {
    //     for j in 1..nums2.len() + 1 {
    //         println!(
    //             "{}",
    //             Solution::find_median_sorted_arrays(nums1[..i].to_vec(), nums2[..j].to_vec())
    //         );
    //     }
    // }
}
