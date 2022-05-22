/*
 * @lc app=leetcode.cn id=76 lang=cpp
 *
 * [76] 最小覆盖子串
 */

// @lc code=start
class Solution {
public:
    bool check(unordered_map<char, int>& t_cnt, 
        unordered_map<char, int>& cur_cnt) {
        for (const auto& i: t_cnt) {
            if (cur_cnt[i.first] < i.second) {
                return false;
            }
            // 等价于如下代码。。。所以这两个map不能是const
            // auto it = cur_cnt.find(i.first);
            // if(it != cur_cnt.end()) {
            //     if (i.second > it->second) {
            //         cout << i.first << " " << i.second << " " << it->second << endl;
            //         return false;
            //     }
            // } else {
            //     cur_cnt[i.first] = 0;
            //     return false;
            // }
        }
        return true;
    }

    string minWindow(string s, string t) {
        unordered_map<char, int> t_cnt, cur_cnt;
        for (const auto& i: t) {
            ++t_cnt[i];
        }
        int left = 0, right = -1;// right初始化为-1
        int len = INT_MAX, res_left = -1;
        cout << "qqq" << endl;
        while (right < int(s.size())) { // 要int，不然-1> t.size()..
            
            if (t_cnt.find(s[++right]) != t_cnt.end()) {
                ++cur_cnt[s[right]];
                cout << "in:" << s[right] << endl;
            }
            while (check(t_cnt, cur_cnt) && left <= right) {
                if (len > right - left + 1) {
                    len = right - left + 1;
                    res_left = left;
                }
                if (t_cnt.find(s[left]) != t_cnt.end()) {
                    --cur_cnt[s[left]]; 
                }
                ++left;// 只缩小左边界
            }
        }
        return res_left == -1? "": s.substr(res_left, len);
    }
};
// @lc code=end

