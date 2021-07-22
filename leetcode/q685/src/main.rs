use std::collections::HashMap;

#[derive(Debug)]
struct DisjointSet {
    parent: Vec<usize>,
    rank: Vec<u32>,
}

impl DisjointSet {
    fn new(n: usize) -> Self {
        let mut parent = vec![0; n];
        for i in 0..n {
            parent[i] = i;
        }
        Self {
            parent,
            rank: vec![1; n as usize],
        }
    }

    fn find(&mut self, i: usize) -> usize {
        if self.parent[i] != i {
            let result = self.find(self.parent[i]);
            self.parent[i] = result;
            result
        } else {
            i
        }
    }

    fn merge(&mut self, i: usize, j: usize) {
        let i = self.find(i);
        let j = self.find(j);
        if i == j {
            return;
        }
        if self.rank[i] > self.rank[j] {
            self.parent[j] = i;
        } else {
            if self.rank[i] == self.rank[j] {
                self.rank[j] += 1;
            }
            self.parent[i] = j;
        }
    }
}

struct Solution;

impl Solution {
    pub fn find_redundant_directed_connection(edges: Vec<Vec<i32>>) -> Vec<i32> {
        let mut set = DisjointSet::new(edges.len() + 1);
        let mut parent = HashMap::new();
        let mut conflict_edges = None;
        let mut loop_edge = None;
        for e in edges {
            if let Some(prev) = parent.get(&e[1]) {
                conflict_edges = Some((vec![*prev, e[1]], e.clone()));
            } else {
                parent.insert(e[1], e[0]);
                let (i, j) = (set.find(e[0] as usize), set.find(e[1] as usize));
                if i != j {
                    set.merge(i, j);
                } else {
                    loop_edge = Some(e);
                }
            }
        }
        if let Some((e1, e2)) = conflict_edges {
            if let Some(_) = loop_edge {
                e1
            } else {
                e2
            }
        } else {
            loop_edge.unwrap()
        }
    }
}

fn main() {
    let edges = vec![vec![1, 2], vec![1, 3], vec![2, 3]];
    println!("{:?}", Solution::find_redundant_directed_connection(edges));
}
