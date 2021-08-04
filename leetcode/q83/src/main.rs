// Definition for singly-linked list.
#[derive(PartialEq, Eq, Clone, Debug)]
pub struct ListNode {
    pub val: i32,
    pub next: Option<Box<ListNode>>,
}

impl ListNode {
    #[inline]
    fn new(val: i32) -> Self {
        ListNode { next: None, val }
    }
}

struct Solution;

impl Solution {
    pub fn delete_duplicates(mut head: Option<Box<ListNode>>) -> Option<Box<ListNode>> {
        if head.is_none() {
            return None;
        }
        let mut slow = head.as_mut().unwrap();
        while let Some(mut fast) = slow.next.take() {
            let next = loop {
                if fast.val != slow.val {
                    break Some(fast);
                }
                if let Some(f) = fast.next {
                    fast = f;
                } else {
                    break None;
                }
            };
            slow.next = next;
            if let Some(new_slow) = slow.next.as_mut() {
                slow = new_slow;
            } else {
                break;
            }
        }
        head
    }
}

fn main() {
    println!("Hello, world!");
}
