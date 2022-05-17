/*
 * @lc app=leetcode.cn id=128 lang=cpp
 *
 * [128] 最长连续序列
 */

// @lc code=start
class Solution {
public:
    int longestConsecutive(vector<int>& vec) {
        unordered_set<int> xset;
        for (auto& i: vec) {
            xset.emplace(i);
        }
        int max_len = 0;
        vector<int> res_vec;
        for (auto& item: xset) {
            vector<int> tmp_vec;
            int tmp_len = 0;
            int i = 0;
            // while (xset.count(item - i)) {
            //     // cout << "aa1 " << i << " " << item-i << endl;
            //     tmp_vec.emplace_back(item - i);
            //     i++;
            // }
            // tmp_len += i;
            
            // i = 1;
            while (xset.count(item + i)) {
                // cout << "aa2 " << i << " " << item-i << endl;
                tmp_vec.emplace_back(item + i);
                i++;
            }
            tmp_len += i;
            if (tmp_len > max_len) {
                res_vec.swap(tmp_vec);
            }
            max_len = max(max_len, tmp_len);
        }
        return max_len;
    }
};
// @lc code=end

