use std::collections::HashSet;

struct Solution;

impl Solution {
    pub fn find_min_height_trees(n: i32, edges: Vec<Vec<i32>>) -> Vec<i32> {
        if edges.is_empty() {
            return vec![1];
        }
        let mut graph = vec![HashSet::new(); n as usize];
        for e in edges {
            graph[e[0] as usize].insert(e[1]);
            graph[e[1] as usize].insert(e[0]);
        }
        let mut outer = vec![];
        for (u, es) in graph.iter().enumerate() {
            if es.len() == 1 {
                let v = *es.iter().next().unwrap();
                outer.push((u as i32, v as usize))
            }
        }
        let mut result = vec![];
        loop {
            let mut new_outer = vec![];
            let mut flag = false;
            for (u, v) in outer {
                let es = &mut graph[v];
                es.remove(&u);
                if es.len() == 0 {
                    result.push(v as i32);
                    flag = true;
                } else if es.len() == 1 {
                    let w = *es.iter().next().unwrap();
                    new_outer.push((v as i32, w as usize));
                }
            }
            if flag {
                return result;
            }
            outer = new_outer;
        }
    }
}

fn main() {
    // let n = 4;
    // let edges = vec![vec![1, 2], vec![2, 3], vec![3, 4]];
    // let n = 1;
    // let edges = vec![];
    let n = 2;
    let edges = vec![vec![0, 1]];
    println!("{:?}", Solution::find_min_height_trees(n, edges));
}
