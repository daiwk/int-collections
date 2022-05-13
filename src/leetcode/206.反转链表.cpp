/*
 * @lc app=leetcode.cn id=206 lang=cpp
 *
 * [206] 反转链表
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
    ListNode* reverseList(ListNode* head) {
        //prev cur next三个指针
        ListNode* prev = nullptr;
        ListNode* cur = head;
        while (cur) {
            // 记录下一个节点next
            ListNode* next = cur->next;
            // 往回指
            cur->next = prev;
            // 更新prev
            prev = cur;
            // 更新cur
            cur = next;
        }
        return prev;
    }
};
// @lc code=end

