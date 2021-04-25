class Solution {
public:
    int FindGreatestSumOfSubArray(vector<int> array) {
        size_t len = array.size();
        vector<int> dp;
        dp.resize(len);
        dp[0] = array[0];
        int res = dp[0];// 不能=0，因为可能整个数组都是负的
        for (int i = 1; i < len; i++) {
            dp[i] = max(dp[i - 1] + array[i], array[i]);
            res = max(dp[i], res);
        }
        return res;
    }
};
