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
    pub fn remove_nth_from_end(mut head: Option<Box<ListNode>>, n: i32) -> Option<Box<ListNode>> {
        let mut fast: *const _ = &head;
        let mut slow = head.as_mut().unwrap();
        let mut cnt = 0;
        while let Some(f) = unsafe { &*fast } {
            fast = &f.next;
            if cnt > n {
                slow = slow.next.as_mut().unwrap();
            }
            cnt += 1;
        }
        if cnt == n {
            return head.unwrap().next;
        }
        slow.next = slow.next.take().unwrap().next;
        head
    }
}

fn main() {
    println!("Hello, world!");
    let head = Some(Box::new(ListNode {
        val: 1,
        next: Some(Box::new(ListNode {
            val: 2,
            next: Some(Box::new(ListNode {
                val: 3,
                next: Some(Box::new(ListNode {
                    val: 4,
                    next: Some(Box::new(ListNode { val: 5, next: None })),
                })),
            })),
        })),
    }));
    let head = Solution::remove_nth_from_end(head, 2);
}
