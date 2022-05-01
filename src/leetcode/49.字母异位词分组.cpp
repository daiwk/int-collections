/*
 * @lc app=leetcode.cn id=49 lang=cpp
 *
 * [49] 字母异位词分组
 */

// @lc code=start
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string> > xmap;
        for (auto& it: strs) {
            string xit = it;
            sort(xit.begin(), xit.end());
            xmap[xit].emplace_back(it);
        }
        vector<vector<string>> res;
        for (auto& it: xmap) {
            res.emplace_back(it.second);
        }
        return res;
    }
};
// @lc code=end

