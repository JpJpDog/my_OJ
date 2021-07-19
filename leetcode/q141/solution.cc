
//   Definition for singly-linked list.

#include <cstdlib>

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
 public:
  bool hasCycle(ListNode *head) {
    if (!head) return false;
    ListNode *h1 = head->next;
    while (true) {
      if (!h1) return false;
      if (h1 == head) return true;
      h1 = h1->next;
      if (!h1) return false;
      h1 = h1->next;
      head = head->next;
    }
  }
};
