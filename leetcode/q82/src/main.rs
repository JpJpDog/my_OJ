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
    pub fn delete_duplicates(head: Option<Box<ListNode>>) -> Option<Box<ListNode>> {
        let mut null = ListNode { val: 0, next: head };
        let mut n1 = &mut null;
        while let Some(n2) = n1.next.as_mut() {
            if let Some(n3) = n2.next.as_mut() {
                if n2.val == n3.val {
                    let mut drop = n1.next.take().unwrap().next.unwrap();
                    n1.next = loop {
                        if let Some(end) = drop.next {
                            if end.val != drop.val {
                                break Some(end);
                            }
                            drop = end;
                        } else {
                            break None;
                        }
                    }
                } else {
                    n1 = n1.next.as_mut().unwrap();
                }
            } else {
                break;
            }
        }
        null.next
    }
}

fn main() {
    println!("Hello, world!");
}
