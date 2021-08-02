struct Solution;

impl Solution {
    pub fn majority_element(nums: Vec<i32>) -> Vec<i32> {
        let len = nums.len() as i32;
        let (mut cand1, mut cnt1) = (nums[0], 0);
        let (mut cand2, mut cnt2) = (nums[0], 0);
        for n in nums.iter() {
            if *n == cand1 {
                cnt1 += 1;
            } else if cnt1 == 0 && *n != cand2 {
                cnt1 = 1;
                cand1 = *n;
            }
            if *n == cand2 && cand2 != cand1 {
                cnt2 += 1;
            } else if cnt2 == 0 && *n != cand1 {
                cnt2 = 1;
                cand2 = *n;
            }
            if *n != cand1 && *n != cand2 {
                cnt1 -= 1;
                cnt2 -= 1;
            }
        }
        let mut result = vec![];
        cnt1 = 0;
        cnt2 = 0;
        for n in nums {
            if n == cand1 {
                cnt1 += 1;
            } else if n == cand2 {
                cnt2 += 1;
            }
        }
        if cnt1 > len / 3 {
            result.push(cand1);
        }
        if cnt2 > len / 3 {
            result.push(cand2);
        }
        result
    }
}

fn main() {
    let nums = vec![1, 1, 1, 3, 3, 2, 2, 2];
    println!("{:?}", Solution::majority_element(nums));
}
