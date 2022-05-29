/*
 * @lc app=leetcode.cn id=287 lang=cpp
 *
 * [287] 寻找重复数
 */

// @lc code=start
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int fast = 0, slow = 0;
        // 把链表的那个xxx!=nullptr改成true
        while (true) {
            fast = nums[nums[fast]];
            slow = nums[slow];
            if (fast == slow) {
                int third = 0;
                // 把链表的那个xxx!=nullptr改成true
                while (true) {
                    if (third == slow) {
                        return third;
                    }
                    third = nums[third];
                    slow = nums[slow];
                }
            }
        }
    }
};
// @lc code=end

