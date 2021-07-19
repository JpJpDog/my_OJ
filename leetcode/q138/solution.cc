#include <cstdlib>
// Definition for a Node.
class Node {
 public:
  int val;
  Node* next;
  Node* random;

  Node(int _val) {
    val = _val;
    next = NULL;
    random = NULL;
  }
};

class Solution {
 public:
  Node* copyRandomList(Node* head) {
    if (!head) return NULL;
    Node *p = head, *p1, *new_head;
    do {
      p1 = new Node(p->val);
      p1->next = p->next;
      p->next = p1;
      p = p1->next;
    } while (p);
    p = head;
    do {
      if (p->random)
        p->next->random = p->random->next;
      else
        p->next->random = NULL;
      p = p->next->next;
    } while (p);
    p1 = new_head = head->next;
    p = head;
    p = p->next = p1->next;
    while (p) {
      p1 = p1->next = p->next;
      p = p->next = p1->next;
    }
    p1->next = NULL;
    return new_head;
  }
};
