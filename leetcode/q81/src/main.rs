struct Solution;

impl Solution {
    pub fn search(nums: Vec<i32>, target: i32) -> bool {
        let (mut s, mut e): (isize, isize) = (0, nums.len() as isize - 1);
        while s <= e {
            let m = (s + e) / 2;
            let (start, mid, end) = (nums[s as usize], nums[m as usize], nums[e as usize]);
            if target == mid {
                return true;
            } else if start == mid && mid == end {
                s += 1;
                e -= 1;
            } else if start <= mid && mid <= end {
                if target < mid {
                    e = m - 1;
                } else {
                    s = m + 1;
                }
                break;
            } else if mid > end {
                if target >= start && target < mid {
                    e = m - 1;
                    break;
                } else {
                    s = m + 1;
                }
            } else {
                //start > mid
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
                return true;
            } else if target < mid {
                e = m - 1;
            } else {
                s = m + 1;
            }
        }
        return false;
    }
}

fn main() {
    let nums = vec![
        1, 1, 1, 1, 1, 1, 1, 1, 1, 13, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    ];
    let target = 13;
    // let nums = vec![3, 1, 2, 3, 3, 3, 3];
    // let target = 2;
    println!("{}", Solution::search(nums, target));
}
