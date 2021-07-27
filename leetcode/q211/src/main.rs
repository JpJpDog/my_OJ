use core::borrow;
use std::{cell::RefCell, collections::HashMap, rc::Rc};

const DOT: u8 = '.' as u8;

struct TrieNode {
    exact: bool,
    next: HashMap<u8, Rc<RefCell<TrieNode>>>,
}

impl TrieNode {
    fn new(exact: bool) -> Self {
        Self {
            exact,
            next: HashMap::new(),
        }
    }
}

struct WordDictionary {
    root: Rc<RefCell<TrieNode>>,
}

/**
 * `&self` means the method takes an immutable reference.
 * If you need a mutable reference, change it to `&mut self` instead.
 */
impl WordDictionary {
    fn traverse(
        &self,
        mut node: Rc<RefCell<TrieNode>>,
        word: &[u8],
    ) -> (usize, Rc<RefCell<TrieNode>>) {
        let mut i = word.len();
        for (idx, ch) in word.iter().enumerate() {
            let new = match node.borrow().next.get(ch) {
                Some(n1) => n1.to_owned(),
                None => {
                    i = idx;
                    break;
                }
            };
            node = new;
        }
        (i, node)
    }

    /** Initialize your data structure here. */
    fn new() -> Self {
        Self {
            root: Rc::new(RefCell::new(TrieNode::new(true))),
        }
    }

    fn add_word(&self, word: String) {
        let word = word.as_bytes();
        let (mut i, mut node) = self.traverse(self.root.to_owned(), word);
        while i < word.len() {
            let new = Rc::new(RefCell::new(TrieNode::new(i == word.len() - 1)));
            (*node).borrow_mut().next.insert(word[i], new.clone());
            node = new;
            i += 1;
        }
        node.borrow_mut().exact = true;
    }

    fn search_r(&self, node: Rc<RefCell<TrieNode>>, word: &[u8]) -> bool {
        let (end, node) = self.traverse(node, word);
        if end == word.len() {
            return node.borrow().exact;
        } else if word[end] != DOT {
            return false;
        }
        let word = &word[end + 1..];
        let next = &node.borrow().next;
        for (_k, n) in next {
            if self.search_r(n.clone(), word) {
                return true;
            }
        }
        false
    }

    fn search(&self, word: String) -> bool {
        self.search_r(self.root.to_owned(), word.as_bytes())
    }
}

/**
 * Your WordDictionary object will be instantiated and called as such:
 * let obj = WordDictionary::new();
 * obj.add_word(word);
 * let ret_2: bool = obj.search(word);
 */

fn main() {
    let d = WordDictionary::new();
    d.add_word("word".to_string());
    println!("{}", d.search("word".to_string()));
    println!("{}", d.search("wor.".to_string()));
    println!("{}", d.search("wo.d".to_string()));
    println!("{}", d.search("words".to_string()));
    d.add_word("words".to_string());
    println!("{}", d.search("words".to_string()));
    println!("{}", d.search("wor".to_string()));
    d.add_word("wor".to_string());
    println!("{}", d.search("wor".to_string()));
}
