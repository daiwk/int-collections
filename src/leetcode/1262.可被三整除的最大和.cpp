/*
 * @lc app=leetcode.cn id=1262 lang=cpp
 *
 * [1262] 可被三整除的最大和
 */

// @lc code=start
class Solution {
public:
    int maxSumDivThree(vector<int>& nums) {
        vector<int> ones, twos;
        int res = 0;
        for (auto& i: nums) {
            if (i % 3 == 1) {
                ones.push_back(i);
            } else if (i % 3 == 2) {
                twos.push_back(i);
            }
            res += i;
        }
        sort(ones.begin(), ones.end());
        sort(twos.begin(), twos.end());
        int ans = 0;
        if (res % 3 == 0) {
            return res;
        } else if (res % 3 == 1) {
            if (ones.size() > 0) {
                ans = max(ans, res - ones[0]);
            }
            if (twos.size() >= 2) {
                ans = max(ans, res - twos[0] - twos[1]);
            }
        } else if (res % 3 == 2) {
            if (twos.size() > 0) {
                ans = max(ans, res - twos[0]);
            }
            if (ones.size() >= 2) {
                ans = max(ans, res - ones[0] - ones[1]);
            }
        }
        return ans;
    }
};
// @lc code=end

