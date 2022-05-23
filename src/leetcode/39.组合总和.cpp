/*
 * @lc app=leetcode.cn id=39 lang=cpp
 *
 * [39] 组合总和
 */

// @lc code=start
class Solution {
public:
    void dfs(vector<int>& candidates, int target, 
        vector<vector<int> > & res, vector<int>& cur_combine, int idx) {
        if (idx == candidates.size()) {
            return;
        }
        if (target == 0) { // 刚好这个数是需要的
            res.emplace_back(cur_combine);
            return;
        }
        // 这里强制idx+1。。
        dfs(candidates, target, res, cur_combine, idx + 1);
        // 尝试选择当前数
        if (target - candidates[idx] >= 0) { 
            //因为题目限制了candidates[i] >=1，所以只要有缺口，那就还要继续找
            cur_combine.push_back(candidates[idx]);
            // 这边不要idx+1...，而是传target-candidates[idx]进去
            // 因为每个数可以重复选。。。。
            dfs(candidates, target - candidates[idx], res, cur_combine, idx);
            cur_combine.pop_back();
        }
        return;
    }
    
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int> > res;
        vector<int> cur_combine;
        dfs(candidates, target, res, cur_combine, 0);
        return res;
    }
};
// @lc code=end

