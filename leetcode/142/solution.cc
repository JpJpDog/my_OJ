
#include <cstdlib>

//   Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
 public:
  ListNode *detectCycle(ListNode *head) {
    if (!head) return NULL;
    ListNode *h1 = head, *h2 = head, *h3 = head;
    do {
      if (!h1) return NULL;
      h1 = h1->next;
      if (!h1) return NULL;
      h1 = h1->next;
      h2 = h2->next;
    } while (h1 != h2);
    while (h3 != h2) {
      h2 = h2->next;
      h3 = h3->next;
    }
    return h2;
  }
};