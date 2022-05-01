/*
 * @lc app=leetcode.cn id=334 lang=cpp
 *
 * [334] 递增的三元子序列
 */

// @lc code=start
class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        // first < second,且second肯定大于first，那么如果second右边的比second大，就是找到了
        int n = nums.size();
        //if (n < 3) {
        //    return false;
        //}
        int first = INT_MAX, second = INT_MAX;
        for (int i = 0; i < n; ++i) {
            int num = nums[i];
            if (num <= first) {
                first = num; // 更新第一个数
            } else if (num <= second) {
                second = num; // 这个数比first大，那就是second
            } else {
                // 如果这个数比两个数都大，那return
                return true; 
            }
        }
        return false;
    }
};
// @lc code=end

