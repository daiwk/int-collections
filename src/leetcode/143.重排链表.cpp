/*
 * @lc app=leetcode.cn id=143 lang=cpp
 *
 * [143] 重排链表
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
    void reorderList(ListNode* head) {
        ListNode* mid = middle_node(head);
        ListNode* l1 = head;
        // 搞出一个mid来
        ListNode* l2 = mid->next;
        l2 = reverse_list(l2);
        // 把l1变短
        mid->next = nullptr;
        merge_list(l1, l2);
    }

    ListNode* middle_node(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }
    ListNode* reverse_list(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* cur = head;
        while (cur) {
            ListNode* next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        return prev;
    }
    void merge_list(ListNode* l1, ListNode* l2) {
        ListNode* l1_p;
        ListNode* l2_p;
        while (l1 != nullptr && l2 != nullptr) {
            // 先记录当前的next
            l1_p = l1->next;
            l2_p = l2->next;
            l1->next = l2;
            l2->next = l1_p;
            l1 = l1_p;
            l2 = l2_p;
        }
    }
};
// @lc code=end

