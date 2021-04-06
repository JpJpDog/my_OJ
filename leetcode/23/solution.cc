//  Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

#include <assert.h>

#include <cstdlib>
#include <vector>
using namespace std;

class Solution {
  ListNode* mergeTwoLists(ListNode* p1, ListNode* p2) {
    if (!p1 || !p2) {
      p1 = nullptr;
    }
    assert(p1 && p2);
    ListNode *null_head = new ListNode(), *p = null_head;
    while (p1 && p2) {
      if (p1->val < p2->val) {
        p = p->next = p1;
        p1 = p1->next;
      } else if (p1->val > p2->val) {
        p = p->next = p2;
        p2 = p2->next;
      } else {
        p = p->next = p1;
        p1 = p1->next;
        p = p->next = p2;
        p2 = p2->next;
      }
    }
    if (p1) {
      p->next = p1;
    } else if (p2) {
      p->next = p2;
    }
    p = null_head->next;
    delete null_head;
    return p;
  }

 public:
  ListNode* mergeKLists(vector<ListNode*>& with_null_lists) {
    if (with_null_lists.empty()) return nullptr;
    if (with_null_lists.size() == 1) return with_null_lists[0];
    vector<ListNode*> lists;
    lists.reserve(with_null_lists.size());
    for (auto l : with_null_lists) {
      if (l) lists.push_back(l);
    }
    int l_size = lists.size();
    if (!l_size) return nullptr;
    for (int step = 2; step <= l_size; step <<= 1) {
      int i;
      for (i = 0; i + step <= l_size; i += step) {
        lists[i] = mergeTwoLists(lists[i], lists[i + step / 2]);
        lists[i + step / 2] = nullptr;
      }
      if (i + step / 2 <= l_size) {
        int m_i = rand() % (l_size / step) * step;
        lists[m_i] = mergeTwoLists(lists[m_i], lists[i]);
        lists[i] = nullptr;
      }
    }
    return lists[0];
  }
};

// [[-6,-3,-1,1,2,2,2],[-10,-8,-6,-2,4],[-2],[-8,-4,-3,-3,-2,-1,1,2,3],[-8,-6,-5,-4,-2,-2,2,4]]
// [[-8,2,4],[-9,-9,-9,-9,-8,-5,-3,-2,1],[-9,-7,-5,-3,-3,-1,0,3,4],[-9,-7,-6,-4,-2,-1,3,4],[-10,-3,0],[-9,0,4],[-8,-8]]
#include <cstdio>

ListNode* get_list(vector<int> vec) {
  ListNode *p = new ListNode, *q = p;
  for (auto n : vec) {
    p = p->next = new ListNode(n);
  }
  return q->next;
}

void print_list(ListNode* l) {
  for (ListNode* p = l; p; p = p->next) {
    printf("%d ", p->val);
  }
  printf("\n");
}
int main() {
  Solution sol;
  vector<ListNode*> vec = {get_list({1, 4, 5}), get_list({1, 3, 4}),
                           get_list({2, 6})};
  // vector<ListNode*> vec = {get_list({-6, -3, -1, 1, 2, 2, 2}),
  //                          get_list({-10, -8, -6, -2, 4}), get_list({-2}),
  //                          get_list({-8, -4, -3, -3, -2, -1, 1, 2, 3}),
  //                          get_list({-8, -6, -5, -4, -2, -2, 2, 4})};
  // vector<ListNode*> vec = {get_list({-8, 2, 4}),
  //                          get_list({-9, -9, -9, -9, -8, -5, -3, -2, 1}),
  //                          get_list({-9, -7, -5, -3, -3, -1, 0, 3, 4}),
  //                          get_list({-9, -7, -6, -4, -2, -1, 3, 4}),
  //                          get_list({-10, -3, 0}),
  //                          get_list({-9, 0, 4}),
  //                          get_list({-8, -8})};
  // vector<ListNode*> vec = {get_list({-8, -8, -3, -2, 0, 2, 2, 3, 3}),
  //                          get_list({-5, -3, 1}),
  //                          get_list({-9, -7, -1, 4}),
  //                          get_list({-10, -4, -4, -4, 0, 3}),
  //                          get_list({-2, 4}),
  //                          get_list({-9, -6, -5, -5, -3, -3, -2, 2}),
  //                          get_list({1, 3}),
  //                          get_list({-8, -3, -2, 1, 3})};
  // vector<ListNode*> vec;
  // for (int i = 1; i < 23; i++) {
  //   vector<ListNode*> v = {
  //       get_list({rand(), rand(), rand()}), get_list({rand(), rand(),
  //       rand()}), get_list({rand(), rand()}), get_list({rand(), rand()})};
  //   for (int i = 0; i < 4; i++) {
  //     vec.push_back(v[i]);
  //   }
  // }
  // for (auto l : vec) {
  //   print_list(l);
  // }
  ListNode* l = sol.mergeKLists(vec);
  print_list(l);
  return 0;
}