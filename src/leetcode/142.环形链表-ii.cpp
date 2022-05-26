/*
 * @lc app=leetcode.cn id=142 lang=cpp
 *
 * [142] 环形链表 II
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode* fast = head;
        ListNode* slow = head;
        while (fast != nullptr && fast->next != nullptr) {      
            fast = fast->next->next;
            slow = slow->next;
            // 就这里和判断是否有环有点diff
            if (slow == fast) {
                ListNode* third = head;
                while (third != slow) {
                    third = third->next;
                    slow = slow->next;
                }
                return third;
            }
        } 
        return nullptr;
    }
};
// @lc code=end

