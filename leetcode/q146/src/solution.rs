use std::{
    cell::RefCell,
    collections::HashMap,
    rc::{Rc, Weak},
};

type RcNode = Rc<RefCell<LinkNode>>;

type WeakNode = Weak<RefCell<LinkNode>>;

struct LinkNode {
    val: i32,
    next: Option<RcNode>,
    prev: Option<WeakNode>,
}

impl Default for LinkNode {
    fn default() -> Self {
        Self {
            val: 0,
            next: None,
            prev: None,
        }
    }
}

struct LinkList {
    len: usize,
    head: RcNode,
    tail: WeakNode,
}

impl LinkList {
    fn new() -> Self {
        let head = Rc::new(RefCell::new(LinkNode::default()));
        let tail = Rc::new(RefCell::new(LinkNode::default()));
        tail.borrow_mut().prev = Some(Rc::downgrade(&head));
        let weak_tail = Rc::downgrade(&tail);
        head.borrow_mut().next = Some(tail);
        Self {
            len: 0,
            head,
            tail: weak_tail,
        }
    }

    fn push_front(&mut self, item: RcNode) {
        self.len += 1;
        let first = self.head.borrow_mut().next.clone().unwrap();
        first.borrow_mut().prev = Some(Rc::downgrade(&item));
        {
            let mut item = item.borrow_mut();
            item.next = Some(first);
            item.prev = Some(Rc::downgrade(&self.head));
        }
        self.head.borrow_mut().next = Some(item);
    }

    fn remove(&mut self, at: &RcNode) {
        self.len -= 1;
        let after = at.borrow_mut().next.take().unwrap();
        let before = at.borrow_mut().prev.take().unwrap();
        let strong_before = before.upgrade().unwrap();
        after.borrow_mut().prev = Some(before);
        strong_before.borrow_mut().next = Some(after);
    }

    fn pop_back(&mut self) {
        if self.len == 0 {
            return;
        }
        self.len -= 1;
        let tail = self.tail.upgrade().unwrap();
        let last = tail.borrow_mut().prev.as_mut().unwrap().upgrade().unwrap();
        let new_last = last.borrow_mut().prev.as_mut().unwrap().upgrade().unwrap();
        tail.borrow_mut().prev = Some(Rc::downgrade(&new_last));
        new_last.borrow_mut().next = Some(tail);
    }
}

pub struct LRUCache {
    list: LinkList,
    map: HashMap<i32, WeakNode>,
    capacity: usize,
}

/**
 * `&self` means the method takes an immutable reference.
 * If you need a mutable reference, change it to `&mut self` instead.
 */
impl LRUCache {
    pub fn new(capacity: i32) -> Self {
        Self {
            list: LinkList::new(),
            map: HashMap::new(),
            capacity: capacity as usize,
        }
    }

    pub fn get(&mut self, key: i32) -> i32 {
        if let Some(n) = self.map.get(&key) {
            if let Some(n) = n.upgrade() {
                self.list.remove(&n);
                let val = n.borrow().val;
                self.list.push_front(n);
                return val;
            } else {
                self.map.remove(&key);
            }
        }
        -1
    }

    pub fn put(&mut self, key: i32, value: i32) {
        if let Some(n) = self.map.get(&key) {
            if let Some(n) = n.upgrade() {
                n.borrow_mut().val = value;
                self.list.remove(&n);
                self.list.push_front(n);
                return;
            } else {
                self.map.remove(&key);
            }
        }
        if self.list.len == self.capacity {
            self.list.pop_back();
        }
        let n = Rc::new(RefCell::new(LinkNode {
            val: value,
            prev: None,
            next: None,
        }));
        self.map.insert(key, Rc::downgrade(&n));
        self.list.push_front(n);
    }
}
