use std::{
    cmp::min,
    collections::{HashSet, VecDeque},
};

struct Solution;

impl Solution {
    #[inline]
    fn change_state(cur: i32, mut state: i32) -> i32 {
        state |= 1 << cur;
        state
    }

    #[inline]
    fn compress(cur: i32, state: i32) -> i32 {
        (cur << 12) | state
    }

    pub fn shortest_path_length(graph: Vec<Vec<i32>>) -> i32 {
        let mut qu = VecDeque::new();
        let mut visited = HashSet::new();
        let final_state = !(-1 << graph.len());
        let mut min_cost = i32::MAX;
        for start in 0..graph.len() as i32 {
            let init_state = Self::change_state(start, 0);
            qu.push_back((start, init_state, 0));
            visited.insert(Self::compress(start, init_state));
        }
        while let Some((cur, state, dist)) = qu.pop_front() {
            if state == final_state {
                min_cost = min(min_cost, dist);
                continue;
            }
            let vs = &graph[cur as usize];
            for v in vs.iter().cloned() {
                let new_state = Self::change_state(v, state);
                let comp = Self::compress(v, new_state);
                if visited.get(&comp).is_none() {
                    visited.insert(comp);
                    qu.push_back((v, new_state, dist + 1));
                }
            }
        }
        min_cost
    }
}

fn main() {
    let graph = vec![vec![1], vec![0, 2, 4], vec![1, 3, 4], vec![2], vec![1, 2]];
    // let graph = vec![vec![1, 2, 3], vec![0], vec![0], vec![0]];
    let result = Solution::shortest_path_length(graph);
    println!("{}", result);
}
