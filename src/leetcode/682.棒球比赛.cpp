/*
 * @lc app=leetcode.cn id=682 lang=cpp
 *
 * [682] 棒球比赛
 */

// @lc code=start
class Solution {
public:
    int calPoints(vector<string>& ops) {
        
        stack<int> st; 
        for (auto& i: ops) {
            if (i == "+") {
                int top = st.top();
                st.pop();
                int new_top = top + st.top();
                st.push(top);
                st.push(new_top);
            } else if (i == "D") {
                st.push(2 * st.top());
            } else if (i == "C") {
                st.pop();
            } else {
                int tmp = std::stoi(i);
                st.push(tmp);
            }
        }
        int res = 0;
        while (st.size() > 0) {
            res += st.top();
            st.pop();
        }
        return res;
    }
};
// @lc code=end

