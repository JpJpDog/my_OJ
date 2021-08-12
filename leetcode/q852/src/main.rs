struct Solution;

impl Solution {
    pub fn peak_index_in_mountain_array(arr: Vec<i32>) -> i32 {
        assert!(arr.len() >= 3);
        let (mut s, mut e) = (0, arr.len() as i32 - 1);
        while s < e {
            let m = (s + e) / 2;
            if arr[m as usize] > arr[m as usize + 1] {
                e = m;
            } else {
                s = m + 1;
            }
        }
        s as i32
    }
}

fn main() {
    let arr = vec![24, 69, 100, 99, 79, 78, 67, 36, 26, 19];
    println!("{}", Solution::peak_index_in_mountain_array(arr));
}
