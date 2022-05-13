/*
 * @lc app=leetcode.cn id=21 lang=cpp
 *
 * [21] 合并两个有序链表
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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        // dummy head也得有个值，不能是个空的。。
        ListNode* pre_head = new ListNode(-1);
        ListNode* prev = pre_head;
        // 用&&，因为只要有一个到头了，其实就可以结束了
        while (list1 != nullptr && list2 != nullptr) {
            if (list1->val < list2->val) {
                prev->next = list1;
                list1 = list1->next;
            } else {
                prev->next = list2;
                list2 = list2->next;
            }
            prev = prev->next;
        }
        //如果l1到头了，那就指向l2剩下的元素
        prev->next = (list1 == nullptr? list2: list1);
        return pre_head->next;
    }
};
// @lc code=end

