use std::cmp::max;

struct Solution;

impl Solution {
    pub fn longest_increasing_path(matrix: Vec<Vec<i32>>) -> i32 {
        let m = matrix.len();
        let n = matrix[0].len();
        let mut sol = Sol {
            matrix,
            mem: vec![vec![0; n]; m],
            m,
            n,
        };
        sol.solve()
    }
}

struct Sol {
    matrix: Vec<Vec<i32>>,
    mem: Vec<Vec<i32>>,
    m: usize,
    n: usize,
}

impl Sol {
    fn dfs(&mut self, i: usize, j: usize, l: i32) -> i32 {
        let cur = self.matrix[i][j];
        let mut next = 0;
        if j > 0 && self.matrix[i][j - 1] > cur {
            next = max(
                next,
                if self.mem[i][j - 1] != 0 {
                    self.mem[i][j - 1]
                } else {
                    self.dfs(i, j - 1, l + 1)
                },
            );
        }
        if j < self.n - 1 && self.matrix[i][j + 1] > cur {
            next = max(
                next,
                if self.mem[i][j + 1] != 0 {
                    self.mem[i][j + 1]
                } else {
                    self.dfs(i, j + 1, l + 1)
                },
            );
        }
        if i > 0 && self.matrix[i - 1][j] > cur {
            next = max(
                next,
                if self.mem[i - 1][j] != 0 {
                    self.mem[i - 1][j]
                } else {
                    self.dfs(i - 1, j, l + 1)
                },
            );
        }
        if i < self.m - 1 && self.matrix[i + 1][j] > cur {
            next = max(
                next,
                if self.mem[i + 1][j] != 0 {
                    self.mem[i + 1][j]
                } else {
                    self.dfs(i + 1, j, l + 1)
                },
            );
        }
        self.mem[i][j] = next + 1;
        next + 1
    }

    fn solve(&mut self) -> i32 {
        let mut longest = 0;
        for i in 0..self.m {
            for j in 0..self.n {
                if self.mem[i][j] == 0 {
                    longest = max(longest, self.dfs(i, j, 0));
                }
            }
        }
        longest
    }
}

fn main() {
    println!(
        "{}",
        Solution::longest_increasing_path(vec![vec![9, 9, 4], vec![6, 6, 8], vec![2, 1, 1]])
    )
}
