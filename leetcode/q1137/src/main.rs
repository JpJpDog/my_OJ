struct Solution;

impl Solution {
    pub fn tribonacci(n: i32) -> i32 {
        if n == 0 {
            return 0;
        } else if n <= 2 {
            return 1;
        }
        let (mut a, mut b, mut c) = (0, 1, 1);
        for i in 3..n + 1 {
            let tmp = a + b + c;
            a = b;
            b = c;
            c = tmp;
        }
        c
    }
}

fn main() {
    println!("Hello, world!");
}
