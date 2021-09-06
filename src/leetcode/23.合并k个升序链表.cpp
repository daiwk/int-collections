/*
 * @lc app=leetcode.cn id=23 lang=cpp
 *
 * [23] 合并K个升序链表
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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        auto head = ListNode(0);
        auto comp = [](ListNode* const &a, ListNode* const &b){return a->val > b->val;}; // 数值越大，优先级越低，也就是每次取出来的是最小的那个
        priority_queue<ListNode*, vector<ListNode*>, decltype(comp)> q(comp);
        for (auto &h : lists) if (h != nullptr) q.push(h);
        auto p = &head;
        while (!q.empty()) {
            p->next = q.top();
            p = p->next;
            q.pop();
            if (p->next != nullptr) q.push(p->next);
        }
        return head.next;
    }
};
// @lc code=end

