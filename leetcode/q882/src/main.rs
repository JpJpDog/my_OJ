use std::{
    cmp::{max, min, Ordering},
    collections::BinaryHeap,
};

#[derive(PartialEq, Eq)]
struct DijInfo {
    dist: i32,
    v: i32,
}

impl DijInfo {
    fn new(dist: i32, v: i32) -> Self {
        Self { dist, v }
    }
}

impl Ord for DijInfo {
    fn cmp(&self, other: &Self) -> Ordering {
        other.dist.cmp(&self.dist)
    }
}

impl PartialOrd for DijInfo {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

struct Solution;

impl Solution {
    pub fn reachable_nodes(edges: Vec<Vec<i32>>, max_moves: i32, n: i32) -> i32 {
        let mut cnt = 0;
        let mut graph = vec![vec![]; n as usize];
        for e in edges.iter() {
            let (u, v, cnt) = (e[0], e[1], e[2]);
            graph[u as usize].push((v, cnt));
            graph[v as usize].push((u, cnt));
        }
        let mut dist = vec![None; n as usize];
        let mut heap = BinaryHeap::new();
        heap.push(DijInfo::new(0, 0));
        while let Some(top) = heap.pop() {
            if let None = dist[top.v as usize] {
                if top.dist <= max_moves {
                    cnt += 1;
                }
                dist[top.v as usize] = Some(top.dist);
                for (v, cnt) in &graph[top.v as usize] {
                    if let None = dist[*v as usize] {
                        heap.push(DijInfo::new(top.dist + cnt + 1, *v));
                    }
                }
            }
        }
        for e in edges {
            let (u, v, w) = (e[0], e[1], e[2]);
            if let Some(du) = dist[u as usize] {
                let dv = dist[v as usize].unwrap();
                let n1 = max(0, max_moves - du);
                let n2 = max(0, max_moves - dv);
                cnt += min(w, n1 + n2);
            } else {
                continue;
            }
        }
        cnt
    }
}

fn main() {
    println!("Hello, world!");
    let r = Solution::reachable_nodes(vec![vec![0, 1, 10], vec![0, 2, 1], vec![1, 2, 2]], 6, 3);
    println!("{}", r);
}
