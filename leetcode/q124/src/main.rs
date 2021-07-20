use std::cell::RefCell;
use std::cmp::max;
use std::rc::Rc;

// Definition for a binary tree node.
#[derive(Debug, PartialEq, Eq)]
pub struct TreeNode {
    pub val: i32,
    pub left: Option<Rc<RefCell<TreeNode>>>,
    pub right: Option<Rc<RefCell<TreeNode>>>,
}

impl TreeNode {
    #[inline]
    pub fn new(val: i32) -> Self {
        TreeNode {
            val,
            left: None,
            right: None,
        }
    }
}

struct Solution;

impl Solution {
    fn traverse(root: &Rc<RefCell<TreeNode>>, cur_max: &mut i32) -> i32 {
        let left_sum = if let Some(left) = &root.borrow().left {
            Solution::traverse(left, cur_max)
        } else {
            0
        };
        let right_sum = if let Some(right) = &root.borrow().right {
            Solution::traverse(right, cur_max)
        } else {
            0
        };
        let mut sum = root.borrow().val;
        let s = sum + max(0, left_sum) + max(0, right_sum);
        *cur_max = max(*cur_max, s);
        sum += max(0, max(left_sum, right_sum));
        sum
    }

    pub fn max_path_sum(root: Option<Rc<RefCell<TreeNode>>>) -> i32 {
        if let Some(root) = root {
            let mut cur_max = i32::MIN;
            Solution::traverse(&root, &mut cur_max);
            cur_max
        } else {
            0
        }
    }
}

fn main() {
    // [5, 4, 8, 11, null, 13, 4, 7, 2, null, null, null, 1];
}
