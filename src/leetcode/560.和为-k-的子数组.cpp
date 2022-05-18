/*
 * @lc app=leetcode.cn id=560 lang=cpp
 *
 * [560] 和为 K 的子数组
 */

// @lc code=start
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> xmap;
        int count = 0;
        int pre = 0;
        xmap[pre] = 1; // 这里要加上，要不0会漏掉。。
        for (int i = 0; i < nums.size(); ++i) {
            pre += nums[i];
            if (xmap.find(pre - k) != xmap.end()) {
                count += xmap[pre - k];
            }
            xmap[pre]++;
        }
        return count;
    }
};
// @lc code=end

