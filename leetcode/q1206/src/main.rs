use rand::prelude::*;
use std::{
    cell::RefCell,
    cmp::Ordering,
    rc::{Rc, Weak},
};

type RcNode<K, V> = Rc<RefCell<SkipNode<K, V>>>;
type WeakNode<K, V> = Weak<RefCell<SkipNode<K, V>>>;

pub struct SkipNode<K: Ord + Clone, V> {
    pub data: Option<(K, Rc<RefCell<V>>)>,
    next: Option<RcNode<K, V>>,
    prev: Option<WeakNode<K, V>>,
    below: Option<RcNode<K, V>>,
    above: Option<WeakNode<K, V>>,
}

impl<K: Ord + Clone, V> SkipNode<K, V> {
    fn new(key: K, val: V) -> Self {
        let mut node = Self::default();
        node.data = Some((key, Rc::new(RefCell::new(val))));
        node
    }

    fn new_ref(&self) -> Self {
        let mut node = Self::default();
        let from_val = self.data.as_ref().unwrap();
        node.data = Some(from_val.clone());
        node
    }
}

impl<K: Ord + Clone, V> Default for SkipNode<K, V> {
    fn default() -> Self {
        Self {
            data: None,
            next: None,
            prev: None,
            below: None,
            above: None,
        }
    }
}

pub struct SkipList<K: Ord + Clone, V> {
    head: RcNode<K, V>,
    rng: ThreadRng,
    len: usize,
}

impl<K: Ord + Clone, V> SkipList<K, V> {
    fn find(&self, key: &K) -> Option<RcNode<K, V>> {
        let mut cur = self.head.clone();
        loop {
            let curb = cur.borrow();
            if let Some(next) = curb.next.clone() {
                let nextb = next.borrow();
                match nextb.data.as_ref().unwrap().0.cmp(key) {
                    Ordering::Less => {
                        drop(nextb);
                        drop(curb);
                        cur = next;
                        continue;
                    }
                    Ordering::Equal => {
                        drop(nextb);
                        return Some(next);
                    }
                    _ => (),
                }
            }
            if let Some(below) = curb.below.clone() {
                drop(curb);
                cur = below;
            } else {
                return None;
            }
        }
    }

    fn insert_after_above(prev: RcNode<K, V>, below: Option<RcNode<K, V>>, item: RcNode<K, V>) {
        if let Some(below) = below {
            below.borrow_mut().above = Some(Rc::downgrade(&item));
            item.borrow_mut().below = Some(below);
        }
        if let Some(next) = prev.borrow().next.clone() {
            next.borrow_mut().prev = Some(Rc::downgrade(&item));
            item.borrow_mut().next = Some(next);
        }
        item.borrow_mut().prev = Some(Rc::downgrade(&prev));
        prev.borrow_mut().next = Some(item);
    }

    fn remove_node(&mut self, at: RcNode<K, V>) -> Option<RcNode<K, V>> {
        let prev = at.borrow().prev.as_ref().unwrap().upgrade().unwrap();
        if let Some(next) = at.borrow().next.clone() {
            next.borrow_mut().prev = Some(Rc::downgrade(&prev));
            prev.borrow_mut().next = Some(next);
        } else if prev.borrow().data.is_none() {
            if let Some(below) = prev.borrow().below.clone() {
                self.head = below;
            } else {
                prev.borrow_mut().next = None;
            }
        } else {
            prev.borrow_mut().next = None;
        }
        at.borrow().below.clone()
    }
}

impl<K: Ord + Clone, V> SkipList<K, V> {
    pub fn new() -> Self {
        let rng = rand::thread_rng();
        let head = Rc::new(RefCell::new(SkipNode::default()));
        Self { rng, head, len: 0 }
    }

    pub fn get(&self, key: &K) -> Option<Rc<RefCell<V>>> {
        if let Some(node) = self.find(key) {
            Some(node.borrow().data.as_ref().unwrap().1.clone())
        } else {
            None
        }
    }

    pub fn insert(&mut self, key: K, val: V) {
        let mut route = vec![];
        let mut cur = self.head.clone();
        loop {
            let curb = cur.borrow();
            if let Some(next) = curb.next.clone() {
                if &next.borrow().data.as_ref().unwrap().0 < &key {
                    drop(curb);
                    cur = next;
                    continue;
                }
            }
            if let Some(below) = curb.below.clone() {
                drop(curb);
                route.push(cur);
                cur = below;
            } else {
                break;
            }
        }
        let prev = cur;
        let node = Rc::new(RefCell::new(SkipNode::new(key, val)));
        Self::insert_after_above(prev, None, node.clone());
        let mut below = node.clone();
        while self.rng.gen() {
            let ref_node = Rc::new(RefCell::new(node.borrow().new_ref()));
            let prev = if let Some(prev) = route.pop() {
                prev
            } else {
                let head = Rc::new(RefCell::new(SkipNode::default()));
                self.head.borrow_mut().above = Some(Rc::downgrade(&head));
                head.borrow_mut().below = Some(self.head.clone());
                self.head = head.clone();
                head
            };
            Self::insert_after_above(prev, Some(below), ref_node.clone());
            below = ref_node;
        }
        self.len += 1;
    }

    pub fn remove(&mut self, key: &K) -> bool {
        let node = self.find(key);
        if let Some(mut node) = node {
            while let Some(below) = self.remove_node(node) {
                node = below;
            }
            self.len -= 1;
            true
        } else {
            false
        }
    }
}

struct Skiplist {
    list: SkipList<i32, ()>,
}

impl Skiplist {
    fn new() -> Self {
        Self {
            list: SkipList::new(),
        }
    }

    fn search(&self, target: i32) -> bool {
        self.list.get(&target).is_some()
    }

    fn add(&mut self, num: i32) {
        self.list.insert(num, ());
    }

    fn erase(&mut self, num: i32) -> bool {
        self.list.remove(&num)
    }
}

fn main() {
    println!("Hello, world!");
}
