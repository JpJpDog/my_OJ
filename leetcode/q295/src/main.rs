use std::{cmp::Ordering, collections::BinaryHeap};

#[derive(PartialEq, Eq)]
struct RevI32(i32);

impl PartialOrd for RevI32 {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

impl Ord for RevI32 {
    fn cmp(&self, other: &Self) -> Ordering {
        other.0.cmp(&self.0)
    }
}

struct MedianFinder {
    lo: BinaryHeap<i32>,
    hi: BinaryHeap<RevI32>,
}

/**
 * `&self` means the method takes an immutable reference.
 * If you need a mutable reference, change it to `&mut self` instead.
 */
impl MedianFinder {
    /** initialize your data structure here. */
    fn new() -> Self {
        let mut lo = BinaryHeap::new();
        let mut hi = BinaryHeap::new();
        lo.push(i32::MIN);
        hi.push(RevI32(i32::MAX));
        Self { lo, hi }
    }

    fn add_num(&mut self, num: i32) {
        let lpk = *self.lo.peek().unwrap();
        let hpk = self.hi.peek().unwrap().0;
        let lsize = self.lo.len();
        let hsize = self.hi.len();
        if num < lpk {
            if lsize > hsize {
                self.hi.push(RevI32(self.lo.pop().unwrap()));
            }
            self.lo.push(num);
        } else if num <= hpk {
            if lsize == hsize {
                self.lo.push(num);
            } else {
                self.hi.push(RevI32(num));
            }
        } else {
            if lsize == hsize {
                self.lo.push(self.hi.pop().unwrap().0);
            }
            self.hi.push(RevI32(num));
        }
    }

    fn find_median(&self) -> f64 {
        let lo_peek = self.lo.peek().unwrap();
        if self.lo.len() > self.hi.len() {
            *lo_peek as f64
        } else {
            let hi_peek = self.hi.peek().unwrap().0;
            (lo_peek + hi_peek) as f64 / 2.0
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
    println!("Hello, world!");
}
