// Definition for singly-linked list.

struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
 public:
  ListNode* reverseKGroup(ListNode* head, int k) {
    if (k == 1) {
      return head;
    }
    auto result = ListNode(0, nullptr);
    auto cur = head, p_tail = &result;
    while (cur) {
      int i;
      auto tail = cur;
      for (i = 0; i < k && cur; i++) {
        auto tmp = cur->next;
        cur->next = p_tail->next;
        p_tail->next = cur;
        cur = tmp;
      }
      if (i < k) {
        cur = p_tail->next;
        p_tail->next = nullptr;
        while (cur) {
          auto tmp = cur->next;
          cur->next = p_tail->next;
          p_tail->next = cur;
          cur = tmp;
        }
        break;
      }
      p_tail = tail;
    }
    return result.next;
  }
};
#include <cstdio>
int main() {
  ListNode* head = new ListNode(
      0,
      new ListNode(
          1, new ListNode(
                 2, new ListNode(
                        3, new ListNode(
                               4, new ListNode(
                                      5, new ListNode(
                                             6, new ListNode(
                                                    7, new ListNode(
                                                           8, nullptr)))))))));
  Solution sol;
  ListNode* new_head = sol.reverseKGroup(head, 5);
  ListNode* p = new_head;
  while (p) {
    printf("%d\n", p->val);
    p = p->next;
  }
}