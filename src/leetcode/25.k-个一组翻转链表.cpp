/*
 * @lc app=leetcode.cn id=25 lang=cpp
 *
 * [25] K 个一组翻转链表
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
    // 返回的是新的head和tail
    pair<ListNode*, ListNode*> myReverse(ListNode* head, ListNode* tail) {
        ListNode* prev = tail->next;
        ListNode* cur = head;
        while (prev != tail) {
            ListNode* next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        return {tail, head};
    }
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        ListNode* pre = dummy;
        while (head) { // while head
            ListNode* tail = pre;
            for (int i = 0; i < k; ++i) {
                tail = tail->next;
                if (tail == nullptr) {
                    // 因为题目要求的是，如果节点总数不是 k 的整数倍，
                    // 那么请将最后剩余的节点保持原有顺序。
                    return dummy->next; // 直接return了
                }
            }
            ListNode* xx = tail->next;
            pair<ListNode*, ListNode*> res = myReverse(head, tail);
            head = res.first;
            tail = res.second;
            // 把反转后的接到原链表中
            pre->next = head;
            tail->next = xx;
            // 更新pre和head
            pre = tail;
            head = tail->next;
        }
        return dummy->next;
    }
};
// @lc code=end

