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
    pub fn merge_two_lists(
        l1: Option<Box<ListNode>>,
        l2: Option<Box<ListNode>>,
    ) -> Option<Box<ListNode>> {
        if l1.is_none() {
            return l2;
        }
        if l2.is_none() {
            return l1;
        }
        let mut n1 = l1.unwrap();
        let mut n2 = l2.unwrap();
        let mut head = ListNode::new(0);
        let mut tail = &mut head;
        loop {
            if n1.val < n2.val {
                let next_n1 = n1.next.take();
                tail.next = Some(n1);
                if let Some(next_n1) = next_n1 {
                    tail = tail.next.as_mut().unwrap();
                    n1 = next_n1;
                } else {
                    tail.next.as_mut().unwrap().next = Some(n2);
                    break;
                }
            } else {
                let next_n2 = n2.next.take();
                tail.next = Some(n2);
                if let Some(next_n2) = next_n2 {
                    tail = tail.next.as_mut().unwrap();
                    n2 = next_n2;
                } else {
                    tail.next.as_mut().unwrap().next = Some(n1);
                    break;
                }
            }
        }
        head.next
    }
}

fn main() {
    println!("Hello, world!");
}
