/*
 * @lc app=leetcode.cn id=19 lang=cpp
 *
 * [19] 删除链表的倒数第 N 个结点
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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // 搞个dummy解决边界问题。。
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        ListNode* fast = head;
        for (int i = 0; i < n && fast != nullptr; ++i) {
            fast = fast->next;
        }
        // slow从dummy开始！！
        ListNode* slow = dummy;
        while (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
        slow->next = slow->next->next;
        return dummy->next;
    }
};
// @lc code=end

