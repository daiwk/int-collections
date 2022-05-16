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
        
        struct MyCmp {
            bool operator()(ListNode* a, ListNode* b) {
                return a->val > b->val;
            }
        };
        // 小顶堆
        priority_queue<ListNode*, vector<ListNode*>, MyCmp> q;

        for (auto &h : lists) {
            if (h != nullptr) {
                q.push(h);
            }
        }
        ListNode* head = new ListNode(0); // dummy head
        ListNode* p = head;
        while (!q.empty()) {
            p->next = q.top();
            p = p->next;
            q.pop();
            if (p->next != nullptr){
                // 用了第xx个链表的节点，那就把它的下一个节点丢进来
                q.push(p->next);
            }
        }
        return head->next;// 因为head是dummy，所以返回next
    }
};
// @lc code=end

