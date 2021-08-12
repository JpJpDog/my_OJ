struct Solution;

impl Solution {
    pub fn search(nums: Vec<i32>, target: i32) -> i32 {
        let (mut s, mut e): (isize, isize) = (0, nums.len() as isize - 1);
        while s <= e {
            let m = (s + e) / 2;
            let (start, mid, end) = (nums[s as usize], nums[m as usize], nums[e as usize]);
            if target == mid {
                return m as i32;
            } else if start <= mid && mid <= end {
                if target < mid {
                    e = m - 1;
                } else {
                    s = m + 1;
                }
                break;
            } else if start <= mid {
                if target >= start && target < mid {
                    e = m - 1;
                    break;
                } else {
                    s = m + 1;
                }
            } else {
                if target > mid && target <= end {
                    s = m + 1;
                    break;
                } else {
                    e = m - 1;
                }
            }
        }
        while s <= e {
            let m = (s + e) / 2;
            let mid = nums[m as usize];
            if target == mid {
                return m as i32;
            } else if target < mid {
                e = m - 1;
            } else {
                s = m + 1;
            }
        }
        return -1;
    }
}

fn main() {
    // let nums = vec![4, 5, 6, 7, 0, 1, 2];
    // let target = 0;
    // let nums = vec![4, 5, 6, 7, 0, 1, 2];
    // let target = 3;
    let nums = vec![1];
    let target = 0;
    println!("{}", Solution::search(nums, target));
}
