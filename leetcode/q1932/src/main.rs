use std::cell::RefCell;
use std::collections::{HashMap, HashSet};
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

    pub fn new_tree(data: &[i32]) -> Option<Rc<RefCell<Self>>> {
        match data.len() {
            0 => None,
            1 => Some(Rc::new(RefCell::new(TreeNode::new(data[0])))),
            2 => {
                let mut root = TreeNode::new(data[0]);
                let left = TreeNode::new(data[1]);
                root.left = Some(Rc::new(RefCell::new(left)));
                Some(Rc::new(RefCell::new(root)))
            }
            3 => {
                let mut root = TreeNode::new(data[0]);
                let left = TreeNode::new(data[1]);
                root.left = Some(Rc::new(RefCell::new(left)));
                let right = TreeNode::new(data[2]);
                root.right = Some(Rc::new(RefCell::new(right)));
                Some(Rc::new(RefCell::new(root)))
            }
            _ => panic!(),
        }
    }
}

struct Solution;

impl Solution {
    fn traverse(
        tree_map: &mut HashMap<i32, Rc<RefCell<TreeNode>>>,
        root: &mut Rc<RefCell<TreeNode>>,
        bound: &mut i32,
    ) -> bool {
        if let Some(left) = &mut root.borrow_mut().left {
            let l_val = left.borrow().val;
            if let Some(l_child) = tree_map.remove(&l_val) {
                *left = l_child;
                if !Solution::traverse(tree_map, left, bound) {
                    return false;
                }
            } else {
                if l_val <= *bound {
                    return false;
                }
                *bound = l_val;
            }
        }
        let val = root.borrow().val;
        if val <= *bound {
            return false;
        }
        *bound = val;
        if let Some(right) = &mut root.borrow_mut().right {
            let r_val = right.borrow().val;
            if let Some(r_child) = tree_map.remove(&r_val) {
                *right = r_child;
                if !Solution::traverse(tree_map, right, bound) {
                    return false;
                }
            } else {
                if r_val <= *bound {
                    return false;
                }
                *bound = r_val;
            }
        }
        true
    }

    pub fn can_merge(trees: Vec<Option<Rc<RefCell<TreeNode>>>>) -> Option<Rc<RefCell<TreeNode>>> {
        let mut leaves = HashSet::new();
        let mut tree_map = HashMap::new();
        for tree in trees {
            if let Some(tree) = tree {
                if let Some(left) = &tree.borrow().left {
                    leaves.insert(left.borrow().val);
                }
                if let Some(right) = &tree.borrow().right {
                    leaves.insert(right.borrow().val);
                }
                let val = tree.borrow().val;
                tree_map.insert(val, tree);
            }
        }
        let mut root_val = None;
        for val in tree_map.keys() {
            if let None = leaves.get(val) {
                root_val = Some(*val);
                break;
            }
        }
        if root_val.is_none() {
            return None;
        }
        let mut root = tree_map.remove(&root_val.unwrap()).unwrap();
        let mut bound = i32::MIN;
        if Solution::traverse(&mut tree_map, &mut root, &mut bound) && tree_map.is_empty() {
            Some(root)
        } else {
            None
        }
    }
}

fn main() {
    let trees = [vec![2, 1, 3]];
    let trees = trees
        .iter()
        .map(|tree| TreeNode::new_tree(tree))
        .collect::<Vec<_>>();
    let root = Solution::can_merge(trees);
    println!("{:?}", root);
}
