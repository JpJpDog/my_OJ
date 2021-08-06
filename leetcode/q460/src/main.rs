use std::{
    cell::RefCell,
    collections::HashMap,
    rc::{Rc, Weak},
};

type RcNode = Rc<RefCell<LinkNode>>;
type WeakNode = Weak<RefCell<LinkNode>>;

struct LinkNode {
    val: (i32, i32, i32),
    next: Option<RcNode>,
    prev: Option<WeakNode>,
}

struct LinkList {
    len: usize,
    head: RcNode,
    tail: WeakNode,
}

impl LinkList {
    fn new() -> Self {
        let head = Rc::new(RefCell::new(LinkNode {
            val: (0, 0, 0),
            next: None,
            prev: None,
        }));
        let tail = Rc::new(RefCell::new(LinkNode {
            val: (0, 0, 0),
            next: None,
            prev: Some(Rc::downgrade(&head)),
        }));
        let weak_tail = Rc::downgrade(&tail);
        head.borrow_mut().next = Some(tail);
        Self {
            len: 0,
            head,
            tail: weak_tail,
        }
    }

    fn remove(&mut self, at: &RcNode) {
        self.len -= 1;
        let mut at_b = at.borrow_mut();
        let after = at_b.next.take().unwrap();
        let before = at_b.prev.take().unwrap();
        drop(at_b);
        let before_strong = before.upgrade().unwrap();
        after.borrow_mut().prev = Some(before);
        before_strong.borrow_mut().next = Some(after);
    }

    fn push_front(&mut self, item: RcNode) {
        self.len += 1;
        let first = self.head.borrow_mut().next.clone().unwrap();
        first.borrow_mut().prev = Some(Rc::downgrade(&item));
        let mut item_b = item.borrow_mut();
        item_b.next = Some(first);
        item_b.prev = Some(Rc::downgrade(&self.head));
        drop(item_b);
        self.head.borrow_mut().next = Some(item);
    }

    fn pop_back(&mut self) -> RcNode {
        self.len -= 1;
        let tail = self.tail.upgrade().unwrap();
        let last = tail.borrow_mut().prev.as_ref().unwrap().upgrade().unwrap();
        let new_last = last.borrow_mut().prev.take().unwrap();
        let strong_new = new_last.upgrade().unwrap();
        tail.borrow_mut().prev = Some(new_last);
        strong_new.borrow_mut().next = Some(tail);
        last
    }
}

struct LFUCache {
    capacity: usize,
    map: HashMap<i32, RcNode>,
    lists: HashMap<i32, LinkList>,
    min_freq: i32,
}

/**
 * `&self` means the method takes an immutable reference.
 * If you need a mutable reference, change it to `&mut self` instead.
 */
impl LFUCache {
    fn remove_node(&mut self, node: &RcNode, old_freq: i32) {
        let list = self.lists.get_mut(&old_freq).unwrap();
        list.remove(&node);
        if list.len == 0 {
            self.lists.remove(&old_freq);
            if old_freq == self.min_freq {
                self.min_freq += 1;
            }
        }
    }

    fn put_node(&mut self, node: RcNode, new_freq: i32) {
        if let Some(new_list) = self.lists.get_mut(&new_freq) {
            new_list.push_front(node);
        } else {
            let mut new_list = LinkList::new();
            new_list.push_front(node);
            self.lists.insert(new_freq, new_list);
        }
    }

    pub fn new(capacity: i32) -> Self {
        Self {
            capacity: capacity as usize,
            map: HashMap::new(),
            lists: HashMap::new(),
            min_freq: 0,
        }
    }

    pub fn get(&mut self, key: i32) -> i32 {
        if let Some(node) = self.map.get(&key).cloned() {
            let (_, val, old_freq) = node.borrow().val;
            self.remove_node(&node, old_freq);
            node.borrow_mut().val.2 += 1;
            self.put_node(node, old_freq + 1);
            val
        } else {
            -1
        }
    }

    pub fn put(&mut self, key: i32, value: i32) {
        if self.capacity == 0 {
            return;
        }
        if let Some(node) = self.map.get(&key).cloned() {
            node.borrow_mut().val.1 = value;
            let old_freq = node.borrow().val.2;
            self.remove_node(&node, old_freq);
            node.borrow_mut().val = (key, value, old_freq + 1);
            self.put_node(node, old_freq + 1);
        } else {
            if self.map.len() == self.capacity {
                let list = self.lists.get_mut(&self.min_freq).unwrap();
                let node = list.pop_back();
                let remove_key = node.borrow().val.0;
                self.map.remove(&remove_key);
                if list.len == 0 {
                    self.lists.remove(&self.min_freq);
                }
            }
            let node = Rc::new(RefCell::new(LinkNode {
                val: (key, value, 1),
                next: None,
                prev: None,
            }));
            self.map.insert(key, node.clone());
            self.put_node(node, 1);
            self.min_freq = 1;
        }
    }
}

/**
 * Your LFUCache object will be instantiated and called as such:
 * let obj = LFUCache::new(capacity);
 * let ret_1: i32 = obj.get(key);
 * obj.put(key, value);
 */

fn main() {
    // cnt(x) = 键 x 的使用计数
    // cache=[] 将显示最后一次使用的顺序（最左边的元素是最近的）
    let mut cache = LFUCache::new(2);
    cache.put(1, 1); // cache=[1,_], cnt(1)=1
    cache.put(2, 2); // cache=[2,1], cnt(2)=1, cnt(1)=1
    assert_eq!(cache.get(1), 1); // 返回 1
                                 // cache=[1,2], cnt(2)=1, cnt(1)=2
    cache.put(3, 3); // 去除键 2 ，因为 cnt(2)=1 ，使用计数最小
                     // cache=[3,1], cnt(3)=1, cnt(1)=2
    assert_eq!(cache.get(2), -1); // 返回 -1（未找到）
    assert_eq!(cache.get(3), 3); // 返回 3
                                 // cache=[3,1], cnt(3)=2, cnt(1)=2
    cache.put(4, 4); // 去除键 1 ，1 和 3 的 cnt 相同，但 1 最久未使用
                     // cache=[4,3], cnt(4)=1, cnt(3)=2
    assert_eq!(cache.get(1), -1); // 返回 -1（未找到）
    assert_eq!(cache.get(3), 3); // 返回 3
                                 // cache=[3,4], cnt(4)=1, cnt(3)=3
    assert_eq!(cache.get(4), 4); // 返回 4
                                 // cache=[3,4], cnt(4)=2, cnt(3)=3
}
