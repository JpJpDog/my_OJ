use std::{borrow::Borrow, cell::RefCell, cmp::Ordering, rc::Rc};

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
    fn parse(s: &mut &[u8]) -> (u32, i32) {
        let mut d = 0;
        let mut v = 0;
        let mut idx = 0;
        let mut flag = false;
        for (i, ch) in s.iter().enumerate() {
            if !ch.is_ascii_digit() {
                if flag {
                    idx = i;
                    break;
                }
                d += 1;
            } else {
                flag = true;
                let off = (ch - ('0' as u8)) as i32;
                v = v * 10 + off;
            }
        }
        if idx == 0 {
            idx = s.len();
        }
        *s = &s[idx..];
        (d, v)
    }

    pub fn recover_from_preorder(traversal: String) -> Option<Rc<RefCell<TreeNode>>> {
        if traversal.is_empty() {
            return None;
        }
        let mut s = traversal.as_bytes();
        let (d, v) = Solution::parse(&mut s);
        assert!(d == 0);
        let mut cur_route = vec![Rc::new(RefCell::new(TreeNode::new(v)))];
        while s.len() > 0 {
            let (d, v) = Solution::parse(&mut s);
            let new = Rc::new(RefCell::new(TreeNode::new(v)));
            let cur_d = cur_route.len() as u32;
            if cur_d == d {
                cur_route.last().unwrap().borrow_mut().left = Some(new.clone());
                cur_route.push(new.clone());
            } else if cur_d > d {
                while cur_route.len() as u32 > d {
                    cur_route.pop();
                }
                cur_route.last().unwrap().borrow_mut().right = Some(new.clone());
                cur_route.push(new.clone());
            } else {
                panic!();
            }
        }
        Some(cur_route.first().unwrap().to_owned())
    }
}

fn print_tree(tree: Rc<RefCell<TreeNode>>) {
    let tree = (*tree).borrow();
    println!("{}", tree.val);
    if let Some(l) = tree.left.to_owned() {
        print_tree(l);
    }
    if let Some(r) = tree.right.to_owned() {
        print_tree(r);
    }
}

fn main() {
    let s = "1-401--349---90--88".to_string();
    let root = Solution::recover_from_preorder(s);
    print_tree(root.unwrap());
}
