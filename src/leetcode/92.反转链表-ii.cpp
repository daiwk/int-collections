/*
 * @lc app=leetcode.cn id=92 lang=cpp
 *
 * [92] 反转链表 II
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
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        
        ListNode* dummy = new ListNode(-1);
        dummy->next = head;
        ListNode* prev = dummy; // 不能prev=nullptr了
        ListNode* cur = head;
        if (left == right || head->next == nullptr) {
            return head;
        }
        for(int i = 1; i <= left - 1; ++i) {
            // 如果prev初始化为nullptr，这里就崩了
            prev = cur;
            cur = cur->next;
        }
        ListNode* x_start = prev;
        ListNode* x_start2 = cur;

        for (int j = 0; j < right - left; ++j) {
            ListNode* next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        // 挂回去
        ListNode* x = cur->next;
        x_start->next = cur;
        x_start2->next = x;
        cur->next = prev;
        return dummy->next;
    }
};
// @lc code=end

