/*
 * @lc app=leetcode.cn id=406 lang=cpp
 *
 * [406] 根据身高重建队列
 */

// @lc code=start
class Solution {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        vector<vector<int> > res;
        sort(people.begin(), people.end(), [](const vector<int>& a, const vector<int>&b) {
            if (a[0] > b[0]) {
                return true;
            } else if (a[0] == b[0] ){
                if (a[1] < b[1]) {
                    return true;
                }
                else { //相等
                    return false;
                }
            } else {
                return false;
            }
        });
        for (auto& person: people) {
           res.insert(res.begin() + person[1], person);
        }
        return res;
    }
};
// @lc code=end

