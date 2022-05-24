/*
 * @lc app=leetcode.cn id=739 lang=cpp
 *
 * [739] 每日温度
 */

// @lc code=start
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> res(n, 0);
        stack<int> s;
        for (int i = n - 1; i >= 0; --i) {
            // 这里s改成存下标
            while (!s.empty() && temperatures[s.top()] <= temperatures[i]) {
                s.pop();
            }
            // 这里是距离：s.top() - i
            res[i] = s.empty()? 0: s.top() - i;
            s.push(i);
        }
        return res;
    }
};
// @lc code=end

