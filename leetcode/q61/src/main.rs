// Definition for singly-linked list.
#[derive(PartialEq, Eq, Clone, Debug)]
pub struct ListNode {
    pub val: i32,
    pub next: Option<Box<ListNode>>,
}

// impl ListNode {
//     #[inline]
//     fn new(val: i32) -> Self {
//         ListNode { next: None, val }
//     }
// }

struct Solution;

impl Solution {
    pub fn rotate_right(head: Option<Box<ListNode>>, k: i32) -> Option<Box<ListNode>> {
        if head.is_none() {
            return None;
        }
        let mut head = head.unwrap();
        let mut len = 1;
        let mut tail: *mut _ = &mut *head;
        while let Some(t) = unsafe { &mut (*tail).next } {
            len += 1;
            tail = &mut **t;
        }
        let k = k % len;
        if k == 0 {
            return Some(head);
        }
        let mut prev_new: *mut _ = &mut head;
        for _i in 0..len - k - 1 {
            prev_new = &mut *unsafe { &mut *prev_new }.next.as_mut().unwrap();
        }
        let new_head = unsafe { &mut *prev_new }.next.take();
        unsafe { &mut *tail }.next = Some(head);
        new_head
    }
}

fn print_list(mut head: &Option<Box<ListNode>>) {
    while let Some(h) = head.as_ref() {
        print!("{} ", h.val);
        head = &h.next;
    }
    println!("");
}

fn main() {
    let head = Some(Box::new(ListNode {
        val: 0,
        next: Some(Box::new(ListNode {
            val: 1,
            next: Some(Box::new(ListNode { val: 2, next: None })),
        })),
    }));
    let new_head = Solution::rotate_right(head, 4);
    print_list(&new_head);
}
