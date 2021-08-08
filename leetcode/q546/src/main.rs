use std::cmp::max;

struct Solution;

impl Solution {
    pub fn remove_boxes(boxes: Vec<i32>) -> i32 {
        let len = boxes.len();
        let mut dp = vec![vec![]; len];
        for (i, v) in dp.iter_mut().enumerate() {
            v.resize(len - i, vec![]);
            for (j, w) in v.iter_mut().enumerate() {
                w.resize(len - i - j + 1, 0);
            }
        }
        let mut sol = Sol { dp, boxes };
        sol.solve(0, len - 1, 0)
    }
}

struct Sol {
    dp: Vec<Vec<Vec<i32>>>,
    boxes: Vec<i32>,
}

impl Sol {
    #[inline]
    fn check_solve(&mut self, i: usize, j: usize, minus: usize, k: usize) -> i32 {
        if j < minus {
            0
        } else {
            self.solve(i, j - minus, k)
        }
    }

    fn solve(&mut self, i: usize, j: usize, k: usize) -> i32 {
        if self.dp[i][j][k] == 0 {
            let mut opt = self.check_solve(i, j, 1, 0) + ((k + 1) * (k + 1)) as i32;
            for l in (0..j).rev() {
                if self.boxes[i + l] == self.boxes[i + j] {
                    opt = max(
                        opt,
                        self.solve(i, l, k + 1) + self.check_solve(i + l + 1, j, l + 2, 0),
                    );
                }
            }
            self.dp[i][j][k] = opt;
        }
        self.dp[i][j][k]
    }
}

fn main() {
    let boxes = vec![
        1, 2, 2, 1, 1, 1, 2, 1, 1, 2, 1, 2, 1, 1, 2, 2, 1, 1, 2, 2, 1, 1, 1, 2, 2, 2, 2, 1, 2, 1,
        1, 2, 2, 1, 2, 1, 2, 2, 2, 2, 2, 1, 2, 1, 2, 2, 1, 1, 1, 2, 2, 1, 2, 1, 2, 2, 1, 2, 1, 1,
        1, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 1, 1,
        1, 1, 1, 1, 1, 2, 1, 2, 2, 1,
    ];
    // let boxes = vec![1, 3, 2, 2, 2, 3, 4, 3, 1];
    // let boxes = vec![1, 1];
    println!("{}", Solution::remove_boxes(boxes))
}
