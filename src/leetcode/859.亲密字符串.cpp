/*
 * @lc app=leetcode.cn id=859 lang=cpp
 *
 * [859] 亲密字符串
 */

// @lc code=start
class Solution {
public:
    bool buddyStrings(string a, string b) {
        if(a.length()!=b.length())
        return false;
        set<char> s(a.begin(),a.end());
        set<char> s1(b.begin(),b.end());
        if(a==b&&a!=""&&s.size()==s1.size()&&s.size()!=a.length())
        return true;
        vector<int> temp;
        for(int i=0;i<a.length();i++)
        {
            if(a[i]!=b[i])
            temp.push_back(i);
        }
        if(temp.size()!=2)
        return false;
        if(a[temp[0]]==b[temp[1]]&&a[temp[1]]==b[temp[0]])
        return true;
        return false;
    }
};
// @lc code=end

