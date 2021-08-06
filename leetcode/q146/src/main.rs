use crate::solution::LRUCache;

mod solution;

fn main() {
    let capacity = 3;
    let mut obj = LRUCache::new(capacity);
    assert_eq!(obj.get(1), -1);
    obj.put(1, 100);
    assert_eq!(obj.get(1), 100);
    obj.put(2, 200);
    obj.put(3, 300);
    assert_eq!(obj.get(2), 200);
    assert_eq!(obj.get(3), 300);
    obj.put(1, 1000);
    assert_eq!(obj.get(1), 1000);
    obj.put(4, 400);
    assert_eq!(obj.get(2), -1);
    obj.put(5, 500);
    obj.put(3, 3000);
    obj.put(6, 600);
    assert_eq!(obj.get(2), -1);
    assert_eq!(obj.get(4), -1);
    assert_eq!(obj.get(5), 500);
    assert_eq!(obj.get(3), 3000);
    assert_eq!(obj.get(6), 600);
}
