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
    pub fn swap_pairs(head: Option<Box<ListNode>>) -> Option<Box<ListNode>> {
        let mut remain = head;
        let mut result = ListNode::new(0);
        let mut tail = &mut result;
        while let Some(mut n1) = remain {
            remain = n1.next.take();
            if let Some(mut n2) = remain {
                remain = n2.next.take();
                n2.next = Some(n1);
                tail.next = Some(n2);
                tail = tail.next.as_mut().unwrap().next.as_mut().unwrap();
            } else {
                tail.next = Some(n1);
                break;
            }
        }
        result.next
    }
}

fn main() {
    println!("Hello, world!");
}
