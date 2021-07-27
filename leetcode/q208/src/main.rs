use std::{cell::RefCell, collections::HashMap, rc::Rc};

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

struct Trie {
    root: Rc<RefCell<TrieNode>>,
}

/**
 * `&self` means the method takes an immutable reference.
 * If you need a mutable reference, change it to `&mut self` instead.
 */
impl Trie {
    /** Initialize your data structure here. */
    fn new() -> Self {
        Self {
            root: Rc::new(RefCell::new(TrieNode::new(true))),
        }
    }

    fn traverse(&self, word: &[u8]) -> (Rc<RefCell<TrieNode>>, usize) {
        let mut idx = word.len();
        let mut node = self.root.to_owned();
        for (i, ch) in word.iter().enumerate() {
            let new = match node.borrow().next.get(ch) {
                Some(n1) => n1.to_owned(),
                None => {
                    idx = i;
                    break;
                }
            };
            node = new;
        }
        (node, idx)
    }

    /** Inserts a word into the trie. */
    fn insert(&self, word: String) {
        let word = word.as_bytes();
        let (mut node, mut i) = self.traverse(word);
        if i == word.len() {
            node.borrow_mut().exact = true;
            return;
        }
        while i < word.len() {
            let mut n = (*node).borrow_mut();
            let new = Rc::new(RefCell::new(TrieNode::new(i == word.len() - 1)));
            n.next.insert(word[i], new.clone());
            drop(n);
            node = new;
            i += 1;
        }
    }

    /** Returns if the word is in the trie. */
    fn search(&self, word: String) -> bool {
        let (node, idx) = self.traverse(word.as_bytes());
        idx == word.len() && node.borrow().exact
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    fn starts_with(&self, prefix: String) -> bool {
        let (_node, idx) = self.traverse(prefix.as_bytes());
        idx == prefix.len()
    }
}

/**
 * Your Trie object will be instantiated and called as such:
 * let obj = Trie::new();
 * obj.insert(word);
 * let ret_2: bool = obj.search(word);
 * let ret_3: bool = obj.starts_with(prefix);
 */

fn main() {
    let obj = Trie::new();
    obj.insert("word".to_string());
    println!("{}", obj.search("word".to_string()));
    println!("{}", obj.search("wor".to_string()));
    println!("{}", obj.starts_with("wor".to_string()));
    obj.insert("wor".to_string());
    println!("{}", obj.search("wor".to_string()));
}
