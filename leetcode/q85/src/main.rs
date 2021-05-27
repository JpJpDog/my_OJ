use std::{cmp::max, mem::swap};

struct Solution;

impl Solution {
    fn max_rect_line(hs: &Vec<i32>) -> i32 {
        let mut st = vec![(-1, 0)];
        let mut max_size = 0;
        for (i, h) in hs.iter().enumerate() {
            let mut left = i;
            while let Some((h1, i1)) = st.last() {
                if h1 > h {
                    max_size = max(max_size, (i - *i1) as i32 * *h1);
                    left = *i1;
                    st.pop();
                } else {
                    if *h1 < *h {
                        st.push((*h, left));
                    }
                    break;
                }
            }
        }
        while let Some((h, i)) = st.pop() {
            if h == 0 {
                break;
            }
            max_size = max(max_size, h * (hs.len() - i) as i32);
        }
        max_size
    }
    pub fn maximal_rectangle(matrix: Vec<Vec<char>>) -> i32 {
        let h = matrix.len();
        if h == 0 {
            return 0;
        }
        let w = matrix[0].len();
        if w == 0 {
            return 0;
        }
        let mut max_h1 = vec![0; w];
        let mut max_h2 = vec![0; w];
        let prev_h = &mut max_h1;
        let cur_h = &mut max_h2;
        let mut max_size = 0;
        for i in 0..h {
            for j in 0..w {
                if matrix[i][j] == '0' {
                    cur_h[j] = 0;
                } else {
                    cur_h[j] = prev_h[j] + 1;
                }
            }
            max_size = max(Solution::max_rect_line(&cur_h), max_size);
            swap(prev_h, cur_h);
        }
        max_size
    }
}
fn main() {
    let matrix = vec![
        vec!['0', '1', '1', '0', '1'],
        vec!['1', '1', '0', '1', '0'],
        vec!['0', '1', '1', '1', '0'],
        vec!['1', '1', '1', '1', '0'],
        vec!['1', '1', '1', '1', '1'],
        vec!['0', '0', '0', '0', '0'],
    ];
    println!("{}", Solution::maximal_rectangle(matrix));
    println!("Hello, world!");
}
