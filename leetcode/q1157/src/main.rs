use std::collections::HashMap;

struct SegTree {
    data: Vec<(i32, i32)>,
    data_l: usize,
}

impl SegTree {
    fn init(data: &mut [(i32, i32)], idx: usize, l: usize, r: usize, d: &[i32]) -> (i32, i32) {
        if l == r {
            data[idx] = (d[l], 1);
            return (d[l], 1);
        }
        let m = (l + r) >> 1;
        let (cand1, cnt1) = Self::init(data, (idx << 1) + 1, l, m, d);
        let (cand2, cnt2) = Self::init(data, (idx << 1) + 2, m + 1, r, d);
        data[idx] = if cand1 == cand2 {
            (cand1, cnt1 + cnt2)
        } else if cnt1 > cnt2 {
            (cand1, cnt1 - cnt2)
        } else if cnt1 == cnt2 {
            (-1, 0)
        } else {
            (cand2, cnt2 - cnt1)
        };
        data[idx]
    }

    fn new(d: &[i32]) -> Self {
        let len = {
            let mut l = d.len();
            let mut i = 0;
            while l != 0 {
                l >>= 1;
                i += 1;
            }
            1 << (i + 1)
        };
        let mut data = vec![(0, 0); len];
        Self::init(&mut data, 0, 0, d.len() - 1, d);
        Self {
            data,
            data_l: d.len(),
        }
    }

    fn query(&self, lower: usize, upper: usize) -> i32 {
        let (mut cand, mut cnt) = (0, 0);
        let mut st = vec![];
        st.push((0, self.data_l - 1, 0));
        let (mut l, mut r, mut idx) = (0, self.data_l - 1, 0);
        loop {
            if l >= lower && r <= upper {
                let (cand1, cnt1) = self.data[idx];
                if cand == cand1 {
                    cnt += cnt1;
                } else if cnt > cnt1 {
                    cnt -= cnt1;
                } else if cnt == cnt1 {
                    cand = -1;
                    cnt = 0;
                } else {
                    cand = cand1;
                    cnt = cnt1 - cnt;
                }
                if let Some(e) = st.pop() {
                    l = e.0;
                    r = e.1;
                    idx = e.2;
                } else {
                    break;
                }
            } else {
                let m = (l + r) >> 1;
                if lower <= m {
                    if upper >= m + 1 {
                        st.push((m + 1, r, (idx << 1) + 2));
                    }
                    r = m;
                    idx = (idx << 1) + 1;
                } else {
                    l = m + 1;
                    idx = (idx << 1) + 2;
                }
            }
        }
        cand
    }
}

struct MajorityChecker {
    tree: SegTree,
    map: HashMap<i32, Vec<usize>>,
}

/**
 * `&self` means the method takes an immutable reference.
 * If you need a mutable reference, change it to `&mut self` instead.
 */
impl MajorityChecker {
    fn new(arr: Vec<i32>) -> Self {
        let tree = SegTree::new(&arr);
        let mut map: HashMap<i32, Vec<usize>> = HashMap::new();
        for (idx, e) in arr.into_iter().enumerate() {
            match map.get_mut(&e) {
                Some(v) => v.push(idx),
                None => {
                    map.insert(e, vec![idx]);
                }
            }
        }
        Self { tree, map }
    }

    fn query(&self, left: i32, right: i32, threshold: i32) -> i32 {
        let (left, right) = (left as usize, right as usize);
        let cand = self.tree.query(left, right);
        if cand == -1 {
            return -1;
        }
        let locs = self.map.get(&cand).unwrap();
        let li = match locs.binary_search(&left) {
            Ok(i) => i,
            Err(i) => i,
        };
        let ri = match locs.binary_search(&right) {
            Ok(i) => i,
            Err(i) => i - 1,
        };
        let num = (ri - li + 1) as i32;
        if num >= threshold {
            cand
        } else {
            -1
        }
    }
}

/**
 * Your MajorityChecker object will be instantiated and called as such:
 * let obj = MajorityChecker::new(arr);
 * let ret_1: i32 = obj.query(left, right, threshold);
 */

fn main() {
    let arr = vec![2, 2, 1, 2, 1, 2, 2, 1, 1, 2];
    let obj = MajorityChecker::new(arr);
    println!("{}", obj.query(2, 5, 4));
    println!("{}", obj.query(0, 5, 63));
    println!("{}", obj.query(0, 1, 2));
    println!("{}", obj.query(2, 3, 2));
    println!("{}", obj.query(6, 6, 1));
    println!("{}", obj.query(0, 3, 3));
    println!("{}", obj.query(4, 9, 6));
    println!("{}", obj.query(4, 8, 4));
    println!("{}", obj.query(5, 9, 5));
    println!("{}", obj.query(0, 1, 2));
}
