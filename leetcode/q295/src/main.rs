use std::{cmp::Reverse, collections::BinaryHeap};

struct MedianFinder {
    lo: BinaryHeap<i32>,
    hi: BinaryHeap<Reverse<i32>>,
}

/**
 * `&self` means the method takes an immutable reference.
 * If you need a mutable reference, change it to `&mut self` instead.
 */
impl MedianFinder {
    /** initialize your data structure here. */
    fn new() -> Self {
        let lo = BinaryHeap::new();
        let hi = BinaryHeap::new();
        // lo.push(i32::MIN);
        // hi.push(Reverse(i32::MAX));
        Self { lo, hi }
    }

    fn add_num(&mut self, num: i32) {
        match self.lo.peek() {
            Some(lpk) => match self.hi.peek() {
                Some(Reverse(hpk)) => {
                    if num < *lpk {
                        if self.lo.len() > self.hi.len() {
                            self.hi.push(Reverse(self.lo.pop().unwrap()));
                        }
                        self.lo.push(num);
                    } else if num <= *hpk {
                        if self.lo.len() == self.hi.len() {
                            self.lo.push(num);
                        } else {
                            self.hi.push(Reverse(num));
                        }
                    } else {
                        if self.lo.len() == self.hi.len() {
                            self.lo.push(*hpk);
                            self.hi.pop();
                        }
                        self.hi.push(Reverse(num));
                    }
                }
                None => {
                    if num < *lpk {
                        self.hi.push(Reverse(self.lo.pop().unwrap()));
                        self.lo.push(num);
                    } else {
                        self.hi.push(Reverse(num));
                    }
                }
            },
            None => self.lo.push(num),
        }
    }

    fn find_median(&self) -> f64 {
        let lpk = self.lo.peek().unwrap();
        if self.lo.len() > self.hi.len() {
            *lpk as f64
        } else {
            let Reverse(hpk) = self.hi.peek().unwrap().to_owned();
            (lpk + hpk) as f64 / 2.0
        }
    }
}

/**
 * Your MedianFinder object will be instantiated and called as such:
 * let obj = MedianFinder::new();
 * obj.add_num(num);
 * let ret_2: f64 = obj.find_median();
 */

fn main() {
    let mut finder = MedianFinder::new();
    finder.add_num(1);
    finder.add_num(2);
    println!("{}", finder.find_median());
    finder.add_num(3);
    println!("{}", finder.find_median());
}
