/*
 * @lc app=leetcode.cn id=160 lang=cpp
 *
 * [160] 相交链表
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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        // a b一直走，判断是否相等，假设b比a长
        // a到null的时候，a从b的头开始，这样和b一起走b-a的长度；
        // b到null的时候，二者都走了b-a，b从a的头开始，就能和a相遇了
        // 假设没交点，那最后两个都会指向null
        if (headA == nullptr || headB == nullptr) {
            return nullptr;
        }
        ListNode* p1 = headA;
        ListNode* p2 = headB;
        while (p1 != p2) {
            p1 = (p1 == nullptr? headB: p1->next);
            p2 = (p2 == nullptr? headA: p2->next);
        }
        return p1;
    }
};
// @lc code=end

