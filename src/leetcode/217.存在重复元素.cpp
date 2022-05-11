/*
 * @lc app=leetcode.cn id=217 lang=cpp
 *
 * [217] 存在重复元素
 */

// @lc code=start
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> xset;
        for(auto& i: nums) {
            if (xset.count(i)) {
                return true;
            }
            xset.emplace(i);
        }
        return false;
    }
};
// @lc code=end

