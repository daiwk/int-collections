/*
 * @lc app=leetcode.cn id=148 lang=cpp
 *
 * [148] 排序链表
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* middle_node(ListNode* head, ListNode* tail) {
        ListNode* fast = head;
        ListNode* slow = head;
        while (fast != tail && fast->next != tail) {
            fast = fast->next->next;
            slow = slow->next;
        }
        return slow;
    }
    ListNode* sort_list(ListNode* head, ListNode* tail) {
        if (head == nullptr) {
            return head;
        }
        //必须要有这段。。
        if (head->next == tail) {
            head->next = nullptr;
            return head;
        }
        ListNode* mid = middle_node(head, tail);
        ListNode* l1 = sort_list(head, mid);
        ListNode* l2 = sort_list(mid, tail);
        return merge(l1, l2);
    }
    ListNode* merge(ListNode* l1, ListNode* l2) {
        // 链表版的归并，加个dummy简单点。。
        ListNode* dummy = new ListNode(0);
        ListNode* cur = dummy;
        ListNode* tmp1 = l1;
        ListNode* tmp2 = l2;
        while (tmp1 != nullptr && tmp2 != nullptr) {
            if (tmp1->val <= tmp2->val) {
                cur->next = tmp1;
                tmp1 = tmp1->next;
            } else {
                cur->next = tmp2;
                tmp2 = tmp2->next;
            }
            cur = cur->next;//别漏了这个。。
        }
        if (tmp1 != nullptr) {
            cur->next = tmp1;
        } else if (tmp2 != nullptr) {
            cur->next = tmp2;
        }
        return dummy->next;
    }
    ListNode* sortList(ListNode* head) {
        return sort_list(head, nullptr);
    }
};
// @lc code=end

