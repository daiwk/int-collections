/*
 * @lc app=leetcode.cn id=141 lang=cpp
 *
 * [141] 环形链表
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
    bool hasCycle(ListNode *head) {
        if (head == NULL || head->next == NULL) {
            return false;
        }
        ListNode* fast = head->next;// fast初始化为next，起点就比slow快了
        ListNode* slow = head;
        while(fast != slow) {
            if (fast == NULL || fast->next == NULL) {
                // 如果fast到终点了，或者fast的下一个节点是终点，说明slow肯定追不上来了
                return false;
            }
            slow = slow->next;
            fast = fast->next->next;
        }
        return true;
    }
};
// @lc code=end

