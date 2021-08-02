use std::{
    cmp::Reverse,
    collections::{BinaryHeap, HashMap},
    hash::Hash,
};

struct RemoveHeap<T: Ord + Hash + Clone> {
    heap: BinaryHeap<T>,
    delay: HashMap<T, u32>,
    len: usize,
}

impl<T: Ord + Hash + Clone> RemoveHeap<T> {
    fn prune(&mut self) {
        while let Some(item) = self.heap.peek() {
            if let Some(times) = self.delay.get_mut(item) {
                if *times == 1 {
                    self.delay.remove(item);
                } else {
                    *times -= 1;
                }
                self.heap.pop();
            } else {
                break;
            }
        }
    }

    fn new() -> Self {
        Self {
            heap: BinaryHeap::new(),
            delay: HashMap::new(),
            len: 0,
        }
    }

    fn push(&mut self, item: T) {
        self.heap.push(item);
        self.len += 1;
    }

    fn peek(&mut self) -> Option<&T> {
        self.prune();
        self.heap.peek()
    }

    fn pop(&mut self) -> Option<T> {
        self.prune();
        self.len -= 1;
        self.heap.pop()
    }

    fn remove(&mut self, item: &T) {
        self.len -= 1;
        if let Some(pk) = self.heap.peek() {
            if pk == item {
                self.heap.pop();
                return;
            }
        }
        if let Some(times) = self.delay.get_mut(item) {
            *times += 1;
        } else {
            self.delay.insert(item.to_owned(), 1);
        }
    }

    #[inline]
    fn len(&self) -> usize {
        self.len
    }
}

struct MedianFinder {
    lo: RemoveHeap<i64>,
    hi: RemoveHeap<Reverse<i64>>,
}

impl MedianFinder {
    fn new() -> Self {
        Self {
            lo: RemoveHeap::new(),
            hi: RemoveHeap::new(),
        }
    }

    fn make_balance(&mut self) {
        if self.lo.len() < self.hi.len() {
            let Reverse(rpk) = self.hi.pop().unwrap();
            self.lo.push(rpk);
        } else if self.lo.len() > self.hi.len() + 1 {
            let lpk = self.lo.pop().unwrap();
            self.hi.push(Reverse(lpk));
        }
    }

    fn add(&mut self, num: i64) {
        match self.lo.peek() {
            Some(lpk) => {
                if num <= *lpk {
                    self.lo.push(num);
                } else {
                    self.hi.push(Reverse(num));
                }
            }
            None => self.lo.push(num),
        }
        self.make_balance();
    }

    fn find(&mut self) -> f64 {
        if self.lo.len() != self.hi.len() {
            let lpk = self.lo.peek().unwrap().to_owned();
            lpk as f64
        } else {
            let lpk = self.lo.peek().unwrap().to_owned();
            let Reverse(rpk) = self.hi.peek().unwrap().to_owned();
            (lpk + rpk) as f64 / 2.0
        }
    }

    fn remove(&mut self, num: &i64) {
        let lpk = self.lo.peek().unwrap();
        if num <= lpk {
            self.lo.remove(num);
        } else {
            self.hi.remove(&Reverse(*num));
        }
        self.make_balance();
    }
}

struct Solution;

impl Solution {
    pub fn median_sliding_window(nums: Vec<i32>, k: i32) -> Vec<f64> {
        let k = k as usize;
        let mut result = vec![];
        let mut finder = MedianFinder::new();
        for i in 0..k {
            finder.add(nums[i] as i64);
        }
        result.push(finder.find());
        for i in k..nums.len() {
            finder.remove(&(nums[i - k] as i64));
            finder.add(nums[i] as i64);
            result.push(finder.find());
        }
        result
    }
}

fn main() {
    let nums = vec![1, 3, -1, -3, 5, 3, 6, 7];
    let k = 3;
    println!("{:?}", Solution::median_sliding_window(nums, k));
}
