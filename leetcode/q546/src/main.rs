use std::cmp::max;

struct Solution;

impl Solution {
    pub fn remove_boxes(boxes: Vec<i32>) -> i32 {
        let len = boxes.len();
        let mut dp = vec![vec![]; len];
        for (i, v) in dp.iter_mut().enumerate() {
            v.resize(len - i + 1, vec![]);
            for (j, w) in v.iter_mut().enumerate() {
                w.resize(len - i - j + 1, 0);
            }
        }
        let mut sol = Sol { dp, boxes };
        sol.solve(0, len, 0)
    }
}

struct Sol {
    dp: Vec<Vec<Vec<i32>>>,
    boxes: Vec<i32>,
}

impl Sol {
    fn solve(&mut self, i: usize, j: usize, k: usize) -> i32 {
        if j == 0 {
            return 0;
        }
        if self.dp[i][j][k] == 0 {
            let mut opt = self.solve(i, j - 1, 0) + ((k + 1) * (k + 1)) as i32;
            for l in (1..j).rev() {
                if self.boxes[i + l - 1] == self.boxes[i + j - 1] {
                    opt = max(
                        opt,
                        self.solve(i, l, k + 1) + self.solve(i + l, j - l - 1, 0),
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
    println!("{}", Solution::remove_boxes(boxes))
}
