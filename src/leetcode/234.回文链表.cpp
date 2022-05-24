/*
 * @lc app=leetcode.cn id=234 lang=cpp
 *
 * [234] 回文链表
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
    bool isPalindrome(ListNode* head) {
        vector<int> vec;
        while (head != nullptr) {
            vec.push_back(head->val);
            head = head->next;
        }
        for (int i = 0, j = vec.size() - 1; i <= j; ++i, --j) {
            if (vec[i] != vec[j]) {
                return false;
            }
        }
        return true;
    }
};
// @lc code=end

