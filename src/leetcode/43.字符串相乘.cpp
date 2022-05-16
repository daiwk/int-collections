/*
 * @lc app=leetcode.cn id=43 lang=cpp
 *
 * [43] 字符串相乘
 */

// @lc code=start
class Solution {
public:
    string multiply(string num1, string num2) {
        if (num1 == "0" || num2 == "0") {
            return "0";
        }
        string res = "0";
        int m = num1.size(), n = num2.size();
        //遍历num2
        for (int i = n - 1; i >= 0; --i) {
            string cur; // 先都扔原始数字进去，后面一起+'0'
            for (int j = n - 1; j > i; j--) {
                cur.push_back(0); 
            }
            int y = num2.at(i) - '0'; 
            int add = 0; // 进位
            for (int j = m - 1; j >= 0; --j) {
                // 遍历num1
                int x = num1[j] - '0';
                int product = x * y + add;
                cur.push_back(product % 10);
                add = product / 10; //进位
            }
            while (add != 0) {
                // 因为最终可以进好多位，要逐位产出
                cur.push_back(add % 10);
                add /= 10;
            }
            reverse(cur.begin(), cur.end());
            for (auto& i: cur) {
                i += '0';
            }
            res = add_string(res, cur);
        }
        return res;
    }
    string add_string(string num1, string num2) {
        int i = num1.size() - 1, j = num2.size() - 1, add = 0;
        string res;
        while (i >= 0 || j >= 0 || add != 0) {
            int x = i >= 0? num1.at(i) - '0': 0; //防越界
            int y = j >= 0? num2.at(j) - '0': 0; //防越界
            int result = x + y + add;
            res.push_back(result % 10);
            add = result / 10;
            --i;
            --j;
        }
        reverse(res.begin(), res.end());
        for (auto& i: res) {
            i += '0';
        }
        return res;
    }
};
// @lc code=end

