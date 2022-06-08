/*
 * @lc app=leetcode.cn id=273 lang=cpp
 *
 * [273] 整数转换英文表示
 */

// @lc code=start
class Solution {
public:
    vector<string> singles = {"", "One", "Two", 
        "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
    vector<string> teens = {"Ten", "Eleven", "Twelve", "Thirteen", 
        "Fourteen", "Fifteen", "Sixteen", "Seventeen", 
        "Eighteen", "Nineteen"};
    // 这里要有Ten，要不输入是10就gg了
    vector<string> tens = {"", "Ten", "Twenty", "Thirty", 
        "Forty", "Fifty", "Sixty", "Seventy",
        "Eighty", "Ninety"};
    vector<string> thousands = {"", "Thousand", "Million", "Billion"};
    string numberToWords(int num) {
        if (num == 0) {
            return "Zero";
        }
        string res;
        // 从高到低，每次取3位
        for (int i = 3, mod = 1000000000; i >= 0; i--, mod /= 1000) {
            int x = num / mod;
            if (x != 0) { //不等于0才继续
                num %= mod;
                res = res + to_eng(x) + thousands[i] + " ";
            }
        }
        // 用while，把结尾的空格全删了
        while (res.back() == ' ') {
            res.pop_back();
        }
        return res;
    }
    string to_eng(int x) {
        string cur;
        int hundred = x / 100;
        x %= 100;
        if (hundred != 0) {
            cur += singles[hundred] + " Hundred ";
        }
        int ten = x / 10;
        if (ten >= 2) {
            cur += tens[ten] + " ";
            x %= 10;
        }
        cout << x << "xxx" << endl;
        if (x >0 && x < 10) {
            cur += singles[x] + " ";   
        } else if (x >= 10) { // 有个等号，为了处理输入10
            cout << cur << endl;
            // 注意 这里是x-10
            cur += teens[x - 10] + " ";
        }
        return cur;
    }
};
// @lc code=end

