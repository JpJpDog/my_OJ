struct Solution;

impl Solution {
    pub fn maximum_gap(nums: Vec<i32>) -> i32 {
        if nums.len() <= 1 {
            return 0;
        }
        let mut max = i32::MIN;
        let mut min = i32::MAX;
        for e in nums.iter() {
            if *e > max {
                max = *e;
            }
            if *e < min {
                min = *e;
            }
        }
        if max == min {
            return 0;
        }
        let bucket_size = std::cmp::max((max - min) as usize / (nums.len() - 1), 1);
        let bucket_n = (max - min) as usize / bucket_size + 1;
        let mut buckets = vec![(i32::MAX, i32::MIN); bucket_n];
        for n in nums {
            let idx = (n - min) as usize / bucket_size;
            let (mut bmin, mut bmax) = buckets[idx];
            if n < bmin {
                bmin = n;
            }
            if n > bmax {
                bmax = n;
            }
            buckets[idx] = (bmin, bmax);
        }
        let mut max_gap = -1;
        let mut prev_max = buckets[0].1;
        for i in 1..bucket_n {
            let (bmin, bmax) = buckets[i];
            if bmin > bmax {
                continue;
            }
            let gap = bmin - prev_max;
            if gap > max_gap {
                max_gap = gap;
            }
            prev_max = bmax;
        }
        max_gap
    }
}

fn main() {
    let nums = vec![1, 1, 1, 1, 1, 5, 5, 5, 5, 5];
    println!("{}", Solution::maximum_gap(nums));
}
