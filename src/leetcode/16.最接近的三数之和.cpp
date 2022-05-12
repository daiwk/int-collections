/*
 * @lc app=leetcode.cn id=16 lang=cpp
 *
 * [16] 最接近的三数之和
 */

// @lc code=start
class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int n = nums.size();
        if (n < 3) {
            return -1;
        }
        sort(nums.begin(), nums.end());
        int dist = INT_MAX;
        int res = INT_MIN;
        for (int i = 0; i < n; ++i) {
            int left = i + 1;
            int right = n - 1;
            // 保证和上一次枚举的元素不相等
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }
            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                if (sum < target) {
                    ++left;
                    // 注意，这个和三数之和那题的位置不一样
                    while (left < right && nums[left] == nums[left - 1]) {
                        left++;
                    }
                } else if(sum > target) {
                    --right;
                    // 注意，这个和三数之和那题的位置不一样
                    while (left < right && nums[right] == nums[right + 1]) {
                        --right;
                    }
                } else {
                    return sum;
                }
                if (dist > abs(sum - target)) {
                    res = sum;
                    dist = abs(sum - target);
                }
            }
        }
        return res;
    }
};
// @lc code=end

