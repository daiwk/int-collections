/*
 * @lc app=leetcode.cn id=328 lang=cpp
 *
 * [328] 奇偶链表
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
    ListNode* oddEvenList(ListNode* head) {
        // 先把第一个偶数保存下来，
        // 跳着指(2->4,3->5)，
        // 最后再把奇数的指向第一个偶数，
        // return的应该还是head
        if (head == nullptr) {
            return nullptr;
        }
        ListNode* even_head = head->next; //第一个偶数，存下来
        ListNode* odd = head;
        ListNode* even = even_head;
        while (even != nullptr && even->next != nullptr) {
            odd->next = even->next;
            odd = odd->next;
            even->next = odd->next;
            even = even->next;
        }
        odd->next = even_head;
        return head;
    }
};
// @lc code=end

