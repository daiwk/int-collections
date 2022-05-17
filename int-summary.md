# int-summary

## 概述

主要是leetcode相关的题

参考1：[https://leetcode-cn.com/leetbook/detail/top-interview-questions-medium/](https://leetcode-cn.com/leetbook/detail/top-interview-questions-medium/)

## 数组和字符串

### 罗马数字转整数

罗马数字包含以下七种字符: I， V， X， L，C，D 和 M。

```
字符          数值
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
```

例如， 罗马数字 2 写做 II ，即为两个并列的 1。12 写做 XII ，即为 X + II 。 27 写做  XXVII, 即为 XX + V + II 。

通常情况下，罗马数字中小的数字在大的数字的右边。但也存在特例，例如 4 不写做 IIII，而是 IV。数字 1 在数字 5 的左边，所表示的数等于大数 5 减小数 1 得到的数值 4 。同样地，数字 9 表示为 IX。这个特殊的规则只适用于以下六种情况：

+ I 可以放在 V (5) 和 X (10) 的左边，来表示 4 和 9。
+ X 可以放在 L (50) 和 C (100) 的左边，来表示 40 和 90。 
+ C 可以放在 D (500) 和 M (1000) 的左边，来表示 400 和 900。

给定一个罗马数字，将其转换成整数。输入确保在 1 到 3999 的范围内。

```
示例 1:

输入: "III"
输出: 3
示例 2:

输入: "IV"
输出: 4
示例 3:

输入: "IX"
输出: 9
示例 4:

输入: "LVIII"
输出: 58
解释: L = 50, V= 5, III = 3.
示例 5:

输入: "MCMXCIV"
输出: 1994
解释: M = 1000, CM = 900, XC = 90, IV = 4.

```

**解答：**

+ 第一，如果当前数字是**最后一个数字**，或者**之后的数字比它小**的话，则加上当前数字
+ 第二，其他情况则减去这个数字(例如，IV，看到I的时候就是减去I，然后到V就是加V; XL，看到X的时候就是-X，然后到L就是加L)

```cpp
class Solution {
public:
    int romanToInt(string s) {
        unordered_map<char, int> x_map;
        x_map.insert(std::make_pair('I', 1));
        x_map.insert(std::make_pair('V', 5));
        x_map.insert(std::make_pair('X', 10));
        x_map.insert(std::make_pair('L', 50));
        x_map.insert(std::make_pair('C', 100));
        x_map.insert(std::make_pair('D', 500));
        x_map.insert(std::make_pair('M', 1000));
        int res = 0;
        for (int i = 0; i < s.size(); ++i) {
            cout << i << s[i] << endl;
            int val = x_map[s[i]];
            if (i == s.size() - 1 || x_map[s[i+1]] <= x_map[s[i]]) {
                res += val;
            } else {
                res -= val;
            }
        }
        return res;
    }
};
```

### 两数之和

给定一个整数数组和一个目标值，找出数组中和为目标值的两个数。

你可以假设每个输入只对应一种答案，且同样的元素不能被重复利用。

**示例:**

给定 nums = [2, 7, 11, 15], target = 9

因为 nums[0] + nums[1] = 2 + 7 = 9 所以返回 [0, 1]

**解法：**

用一个map，key是元素值，value是idx 看新来的这个元素的目标值（tgt - nums[i]）在不在map里，在的话把它的value拿出来就行了。。

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> res;
        unordered_map<int, int> map;
        for (int i = 0; i < nums.size(); ++i) {
            const int& tgt_val = target - nums[i];
            if (map.find(tgt_val) != map.end()) {   
                res.push_back(map[tgt_val]);
                res.push_back(i);
                return res;
            } else {
                map.insert(std::make_pair(nums[i], i));
            }
        }
    }
};
```


### 三数之和

给你一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，使得 a + b + c = 0 ？请你找出所有和为 0 且不重复的三元组。

注意：答案中不可以包含重复的三元组。

```cpp
    vector<vector<int>> threeSum(vector<int>& nums) 
    {
        int size = nums.size();
        vector<vector<int> >res;            // 保存结果（所有不重复的三元组）
        if (size < 3) {
            return res;          // 特判
        }
        std::sort(nums.begin(), nums.end());// 排序（默认递增）
        for (int i = 0; i < size; i++)      // 固定第一个数，转化为求两数之和
        {
            if (nums[i] > 0) { // ！！！容易漏掉
                return res; // 第一个数大于 0，后面都是递增正数，不可能相加为零了
            }
            // 去重：如果此数已经选取过，跳过
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }
            // 双指针在nums[i]后面的区间中寻找和为0-nums[i]的另外两个数
            int left = i + 1;
            int right = size - 1;
            while (left < right)
            {
                if (nums[left] + nums[right] > -nums[i]) {
                    right--;    // 两数之和太大，右指针左移
                } else if (nums[left] + nums[right] < -nums[i]) {
                    left++;     // 两数之和太小，左指针右移
                } else {
                    // 找到一个和为零的三元组，添加到结果中，左右指针内缩，继续寻找
                    vector<int> tmp {nums[i], nums[left], nums[right]};
                    res.push_back(tmp);
                    left++;
                    right--;
                    // 去重：第二个数和第三个数也不重复选取 ！！！容易漏掉
                    // 例如：[-4,1,1,1,2,3,3,3], i=0, left=1, right=5
                    while (left < right && nums[left] == nums[left-1]) {
                        left++;
                    }
                    while (left < right && nums[right] == nums[right+1]) {
                        right--;
                    }
                }
            }
        }
        return res;
    }
```

### 矩阵置零

给定一个 m x n 的矩阵，如果一个元素为 0 ，则将其所在行和列的所有元素都设为 0 。请使用 原地 算法。

```cpp
    void setZeroes(vector<vector<int>>& matrix) {
        int row = matrix.size();
        int col = matrix[0].size();
        // 用两个辅助数组，存这行和这列是否要变成0，
        // 然后再遍历原矩阵，如果二者有一个要变0，那就变成0
        vector<bool> rows(row, false);
        vector<bool> cols(col, false);
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                if (matrix[i][j] == 0) {
                    rows[i] = true;
                    cols[j] = true;
                }    
            }
        }
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                if (rows[i] || cols[j]) {
                    matrix[i][j] = 0;
                }    
            }
        }
    }
```

### 字母异位词分组

给你一个字符串数组，请你将 字母异位词 组合在一起。可以按任意顺序返回结果列表。

字母异位词 是由重新排列源单词的字母得到的一个新单词，所有源单词中的字母通常恰好只用一次。

其实就是个倒排

```cpp
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string> > xmap;
        for (auto& it: strs) {
            string xit = it;
            // 对string进行sort，搞成一个词，扔进map
            sort(xit.begin(), xit.end());
            xmap[xit].emplace_back(it);
        }
        vector<vector<string>> res;
        for (auto& it: xmap) {
            res.emplace_back(it.second);
        }
        return res;
    }
```

### 无重复字符的最长子串

给定一个字符串，请你找出其中不含有重复字符的 最长子串 的长度。

```
输入: s = "pwwkew"
输出: 3
解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
     请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。
```

双指针

```cpp
   int lengthOfLongestSubstring(string s) {
        set<char> set_char;
        int res = 0;
        // 双指针，两个指针都从头开始
        for (int i = 0, j = 0; i < s.size() && j < s.size(); ) {
            if (set_char.find(s[j]) != set_char.end()) {
                //找到重复了，那就把起始的扔了
                set_char.erase(s[i]);
                ++i;
            } else {
                if (j - i + 1 > res) {
                    res = j - i + 1;
                }
                set_char.insert(s[j]);
                //没重复的，右指针继续往前找
                ++j;
            }
        }
        
        return res;
    }
```

### 寻找两个正序数组的中位数

给定两个大小为 m 和 n 的有序数组 nums1 和 nums2 。

请找出这两个有序数组的中位数。要求算法的时间复杂度为 O(log (m+n)) 。

你可以假设 nums1 和 nums2 不同时为空。

```
示例 1:

nums1 = [1, 3]
nums2 = [2]

中位数是 2.0

示例 2:

nums1 = [1, 2]
nums2 = [3, 4]

中位数是 (2 + 3)/2 = 2.5
```

**解答：**

方法1(复杂度O(m+n))：

先归并两个数组，再取中点，归并的复杂度是O(m+n)，参考第88题[https://leetcode-cn.com/problems/merge-sorted-array/description/](https://leetcode-cn.com/problems/merge-sorted-array/description/)

```cpp
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        vector<int> tmp;
        int m = nums1.size();
        int n = nums2.size();
        int total_size = n + m;
        tmp.resize(total_size);
        // 倒着来
        int i = m - 1;
        int j = n - 1;
        // 如果有重复的，也要复制两遍
        while (j >= 0) {
            if (i < 0) {
                // 如果i数组遍历完了，要把j数据剩下的全部拷过来,记住是<j+1
                for(int k = 0; k < j + 1; ++k) {
                    tmp[k] = nums2[k];
                }
                break;
            }
            if (nums2[j] > nums1[i]) {
                // 留大的下来，留谁的就谁的指针--
                // 注意是i + j + 1
                tmp[i + j + 1] = nums2[j];
                j--;
            } else {
                tmp[i + j + 1] = nums1[i];
                i--;
            }
        }
        if (j < 0) {
            // 同理，j遍历完了就把i剩下的搞过来
            for(int k = 0; k < i + 1; ++k) {
                tmp[k] = nums1[k];
            }
        }
        // 以上是归并两个数组的方法
        if (total_size % 2 != 0) {
            return tmp[total_size / 2];
        } else {
            return (tmp[total_size / 2 - 1] + tmp[total_size / 2]) *1.0 / 2;
        }
    }
```

方法2：二分查找

[https://leetcode-cn.com/problems/median-of-two-sorted-arrays/solution/xun-zhao-liang-ge-you-xu-shu-zu-de-zhong-wei-s-114/](https://leetcode-cn.com/problems/median-of-two-sorted-arrays/solution/xun-zhao-liang-ge-you-xu-shu-zu-de-zhong-wei-s-114/)

### 最长公共前缀

编写一个函数来查找字符串数组中的最长公共前缀。

如果不存在公共前缀，返回空字符串 ""。

```
示例 1：

输入：strs = ["flower","flow","flight"]
输出："fl"
示例 2：

输入：strs = ["dog","racecar","car"]
输出：""
解释：输入不存在公共前缀。
```

注意这里说的是前缀，不是子序列，所以两个str都从0开始，同一个指针一起移动就行。。可以只遍历短的长度

另外，随着遍历的字符串变多，公共前缀是会变短的，变成0就可以return，如果完了还不是0，那就是要的了

另外，不用str[i]和str[i+1]比较再和prefix，直接str[i]和prefix比较就行，这样循环简单点

```cpp
    string longestCommonPrefix(vector<string>& strs) {
        string comm_prefix = strs[0];
        for (int i = 0; i < strs.size(); ++i) {
            lcp_sub(strs[i], comm_prefix);
            if (comm_prefix == "") {
                return comm_prefix;
            }
        }
        return comm_prefix;
    }
    void lcp_sub(const string &a, string& b) {
        int len = min(a.length(), b.length());
        int i = 0;
        while(i < len) {
            if (a[i] != b[i]) {
                break;
            }
            ++i;
        }
        if (a[i] != b[i]) {
            b = b.substr(0, i);
        } else {
            b = b.substr(0, i + 1);
        }
    }
```

有点绕，还是抄答案吧：

```cpp
    string longestCommonPrefix(vector<string>& strs) {
        string comm_prefix = strs[0];
        for (int i = 0; i < strs.size(); ++i) {
            lcp_sub(strs[i], comm_prefix);
            if (comm_prefix == "") {
                return comm_prefix;
            }
        }
        return comm_prefix;
    }
    void lcp_sub(const string &a, string& b) {
        int len = min(a.length(), b.length());
        int i = 0;
        // while一起判断了，就不用再对i i+1处理了。。
        while (i < len && a[i] == b[i]) {
            ++i;
        }
        b = b.substr(0, i);
    }
```

### 存在重复元素

给你一个整数数组 nums 。如果任一值在数组中出现 至少两次 ，返回 true ；如果数组中每个元素互不相同，返回 false 。

```cpp
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> xset;
        for(auto& i: nums) {
            if (xset.count(i)) {
                return true;
            }
            xset.emplace(i);
        }
        return false;
    }
```

### 整数反转

给定一个 32 位有符号整数，将整数中的数字进行反转。

**示例：**

```
示例 1:
输入: 123
输出: 321

示例 2:
输入: -123
输出: -321

示例 3:
输入: 120
输出: 21
```

注意:

假设我们的环境只能存储 32 位有符号整数，其数值范围是 [−2^31,  2^31 − 1]。根据这个假设，如果反转后的整数溢出，则返回 0。

**解答**

写一个valid函数，记得参数变成long，然后去看这个long是不是在int32的范围里

```cpp
class Solution {
public:
    bool valid(long x) { // 注意，这里要是long
        if (x > 0) {
            if (x >= pow(2, 31) -1)
                return false;
        }
        if (x < 0) {
            if (x <= -pow(2, 31)) {
                return false;
            }
        }
        return true;
    }

    int reverse(int x) {
        long tmp = 0;
        // 开始判断一下范围
        if (!valid(x)) {
            return 0;
        }
        bool flag = true;
        // 统一变成正数，处理完如果原来是负的再变回去
        if (x < 0) {
            x = -x;
            flag = false;
        }
        while (x != 0) {
            tmp *= 10; // tmp向左移一位
            tmp += x % 10; // 取出x的最低位
            x /= 10; // x往右移一位
        }
        if (flag == false) {
            tmp = -tmp;
        }
        // 结束再判断一下范围
        if (valid(tmp)) {
            return tmp;
        }
        return 0; 
};
```

### 只出现一次的数字

给定一个非空整数数组，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素。

异或：

+ 任何数和 0 做异或运算，结果仍然是原来的数
+ 任何数和其自身做异或运算，结果是 0
+ 异或运算满足交换律和结合律

所以

a^b^a=a^a^b=(a^a)^b=0^b=b

所以把所有数异或一遍就是那个只出现一次的数了。。

```cpp
    int singleNumber(vector<int>& nums) {
        int res = 0; // 初始化为0
        for (auto& i: nums) {
            res ^= i;
        }
        return res;
    }
```

### 有效的括号

给定一个只包括``` '('，')'，'{'，'}'，'['，']' ```的字符串，判断字符串是否有效。

有效字符串需满足：

+ 左括号必须用相同类型的右括号闭合。
+ 左括号必须以正确的顺序闭合。
+ 注意空字符串可被认为是有效字符串。

```
示例 1:

输入: "()"
输出: true
示例 2:

输入: "()[]{}"
输出: true
示例 3:

输入: "(]"
输出: false
示例 4:

输入: "([)]"
输出: false
示例 5:

输入: "{[]}"
输出: true
```

**解答：**

注意一定要**先判断st.size()>0再取top**，不然会出错

```cpp
class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        unordered_map<char, char> mp;
        // 先用map存一下左右括号的映射关系，
        // 因为是栈，遇到右括号才想着pop，所以key是右括号！！
        mp.insert(std::make_pair('}', '{'));
        mp.insert(std::make_pair(']', '['));
        mp.insert(std::make_pair(')', '('));
        for (int i = 0; i < s.size(); i++) {
            if (mp.find(s[i]) != mp.end() && 
                st.size() > 0 && 
                mp[s[i]] == st.top()) {
                st.pop();
            } else {
                st.push(s[i]);
            }
        }
        if (st.size() == 0) return true;
        return false;
    }
};
```

#### 基础的括号匹配

[https://www.luogu.com.cn/problem/P1739](https://www.luogu.com.cn/problem/P1739)

```
假设一个表达式有英文字母（小写）、运算符（+，—，*，/）和左右小（圆）括号构成，以“@”作为表达式的结束符。请编写一个程序检查表达式中的左右圆括号是否匹配，若匹配，则返回“YES”；否则返回“NO”。表达式长度小于255，左圆括号少于20个。

输入格式
一行：表达式

输出格式
一行：“YES” 或“NO”
```

解答：

栈的思想，可以不用栈，用一个变量top，遇到左括号++,右括号--，看最后是不是0

注意：

**如果先出现了右括号，前面没有左括号的时候（top=0时出现了右括号），直接是NO**

```cpp
#include<iostream>
#include<cstdio>
#include<string>
using namespace std;
char c;
int top = 0;
int main()
{
    for(; ; )
    {
        cin >> c;
        if (c == '@') break;
        if (c == '(') top++;
        else if( c==')' && top > 0) {
            top--;
        } else if(c==')') {
            cout << "NO";
            return 0;
        }
    }
    if(top == 0) {
        cout<<"YES";
    } else {
        cout<<"NO";
    }
    return 0;
}
```

### 回文数

判断一个整数是否是回文数。回文数是指正序（从左向右）和倒序（从右向左）读都是一样的整数。

```
示例 1:

输入: 121
输出: true
示例 2:

输入: -121
输出: false
解释: 从左向右读, 为 -121 。 从右向左读, 为 121- 。因此它不是一个回文数。
示例 3:

输入: 10
输出: false
解释: 从右向左读, 为 01 。因此它不是一个回文数。
```

**解答**

为了避免数字反转可能导致的溢出问题，为什么不考虑只反转 数字的一半？毕竟，如果该数字是回文，**其后半部分反转后应该与原始数字的前半部分相同。**

例如，输入 1221，我们可以将数字“1221”的后半部分从“21”反转为“12”，并将其与前半部分“12”进行比较，因为二者相同，我们得知数字 1221 是回文。

* 特判

**所有负数都不可能是回文，例如：-123 不是回文，因为 - 不等于 3**

**!!!!尾数能被10整除，即尾数是0的也不行，因为首位不是0**

* 反转

对于数字 1221，如果执行 1221 % 10，我们将得到最后一位数字 1，要得到倒数第二位数字，我们可以先通过除以 10 把最后一位数字从 1221 中移除，1221 / 10 = 122，再求出上一步结果除以10的余数，122 % 10 = 2，就可以得到倒数第二位数字。如果我们把**最后一位数字乘以10**，再**加上倒数第二位数字**，1 * 10 + 2 = 12，就得到了我们想要的反转后的数字。 如果继续这个过程，我们将得到更多位数的反转数字。

所以，每次把**上一次的数字\*10**，**加上这一次的最后一位数字**，然后**x/=10**，**把这次的尾数扔掉**

现在的问题是，我们如何知道反转数字的位数已经达到原始数字位数的一半？

* 终止

我们将原始数字除以 10，然后给反转后的数字乘上 10，所以，当除完的原始数字不大于反转后的数字时，就意味着我们已经处理了一半位数的数字。

例如，原数字是4123，反转到321>41的时候，就到一半了；如果原数字是412，反转到21>4的时候也到一半了。也就是反转的位数比剩下的多，肯定到一半了。或者，原数字是1234，反转到34>12

举个是回文数的例子，原数字是3223，32==32，break了；原数字121，12>1，break掉

**当数字长度为奇数时，我们可以通过 revertedNumber/10 去除处于中位的数字。**

例如，当输入为 12321 时，在 while 循环的末尾我们可以得到 x = 12，revertedNumber = 123

由于处于中位的数字不影响回文（它总是与自己相等），所以我们可以简单地将其去除。所以对于奇数位，就是判断x==revertedNumber/10

```cpp
class Solution {
public:
    bool isPalindrome(int x) {
        if(x < 0 || (x % 10 == 0 && x != 0)) { //边界！！
            return false;
        }
        int revertedNumber = 0;
        while(x > revertedNumber) { // 大于
            revertedNumber = revertedNumber * 10 + x % 10; // 这么判断 
            x /= 10;
        }
        return (x == revertedNumber || x == revertedNumber / 10);
    }
};
```

### 盛最多水的容器

给定一个长度为 n 的整数数组 height 。有 n 条垂线，第 i 条线的两个端点是 (i, 0) 和 (i, height[i]) 。

找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。

返回容器可以储存的最大水量。

说明：你不能倾斜容器。

双指针！！

对于i，j两个点，能接的水量是min(num[i],num[j]) * (j - i)

这个时候应该移动的是num[i]和num[j]中较小的那个，因为j-i肯定会变小，

而想要变大，只能min(num[i],num[j])变大，所以要把小的移一下试试，如果小的在左边那就右移，否则同理

```cpp
    int maxArea(vector<int>& height) {
        // 对于i，j两个点，能接的水量是min(num[i],num[j]) * (j - i)
        // 这个时候应该移动的是num[i]和num[j]中较小的那个，因为j-i肯定会变小，
        // 而想要变大，只能min(num[i],num[j])变大，所以要把小的移一下试试，如果小的在左边那就右移，否则同理
        int max_res = 0;
        int i = 0, j = height.size() - 1;
        while (i < j) {
            int cur_water = min(height[i], height[j]) * (j - i);
            max_res = max(max_res, cur_water);
            if (height[i] >= height[j]) {
                --j;
            } else {
                ++i;
            }
        }
        return max_res;
    }
```

### 最接近的三数之和

给你一个长度为 n 的整数数组 nums 和 一个目标值 target。请你从 nums 中选出三个整数，使它们的和与 target 最接近。

返回这三个数的和。

假定每组输入只存在恰好一个解。

**解法**

「最接近」即为**差值的绝对值最小**

类似三数之和，双指针，固定第一个数，希望剩下b+c最接近target


```cpp
    int threeSumClosest(vector<int>& nums, int target) {
        int n = nums.size();
        if (n < 3) {
            return -1;
        }
        sort(nums.begin(), nums.end());
        int dist = INT_MAX;
        int res = INT_MIN;
        for (int i = 0; i < n; ++i) {
            int left = i + 1;
            int right = n - 1;
            // 保证和上一次枚举的元素不相等
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }
            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                if (sum < target) {
                    ++left;
                    // 注意，这个和三数之和那题的位置不一样
                    while (left < right && nums[left] == nums[left - 1]) {
                        left++;
                    }
                } else if(sum > target) {
                    --right;
                    // 注意，这个和三数之和那题的位置不一样
                    while (left < right && nums[right] == nums[right + 1]) {
                        --right;
                    }
                } else {
                    return sum;
                }
                if (dist > abs(sum - target)) {
                    res = sum;
                    dist = abs(sum - target);
                }
            }
        }
        return res;
    }
```

### Z 字形变换

将一个给定字符串 s 根据给定的行数 numRows ，以从上往下、从左到右进行 Z 字形排列。

比如输入字符串为 "PAYPALISHIRING" 行数为 3 时，排列如下：

```
P   A   H   N
A P L S I I G
Y   I   R
```

之后，你的输出需要从左往右逐行读取，产生出一个新的字符串，比如："PAHNAPLSIIGYIR"。

请你实现这个将字符串进行指定行数变换的函数：

```
示例 2：
输入：s = "PAYPALISHIRING", numRows = 4
输出："PINALSIGYAHRPI"
解释：
P     I    N
A   L S  I G
Y A   H R
P     I
```

画个图，直接找出新字符串每一位对应原来的下标

会向下填写 r 个字符，然后向右上继续填写 r−2 个字符(斜线的r扣掉最后一行，和新的第一行的各一个字符)，所以变换周期是t=2r-2。

所以第一行的下标都是2r-2的倍数即0+kt，而最后一行就应该是r-1 + kt

而中间的第i行，除了k个数外，每一轮间还有一个数，那个数是(k + 1)t-i 


```cpp
    string convert(string s, int numRows) {
        
        int t = 2 * numRows - 2;
        int i = 0;
        if (t == 0) {
            return s;
        }
        int round = s.length() / t;
        string res;
        while (i < numRows) {
            int k = 0;
            int idx = 0;
            if (i == 0) {
                while (k <= round) {
                    idx = k * t;
                    if (idx < s.length()) {
                        res.push_back(s[idx]);
                    }
                    k++;
                }
            } else if (i < numRows -1) {
                k = 0;
                while (k <= round) {
                   idx = i + k * t;
                   if (idx < s.length()) {
                        res.push_back(s[idx]);
                   }
                   idx = (k + 1) * t - i;
                   if (idx > 0 && idx < s.length()) {
                        res.push_back(s[idx]); 
                   }
                   ++k;
                }
            } else {
                k = 0;
                while (k <= round) {
                    idx = numRows - 1 + k * t;
                    if (idx < s.length()) {
                        res.push_back(s[idx]);
                    }
                    k++;
                }
            }
            ++i;
        }
        return res;
    }
```

标准答案简单很多：

其实就是。。而中间的第i行，除了k个数外，每一轮间还有一个数，那个数是(k + 1)t-i = kt + t-i

这样，就都有kt了

所以就是每个周期塞两个数（不越界的情况下），

第一个数是每个周期的起始下标kt + i

第二个数是kt+t-i

限制一下最后一行和第一行只插入一个数，不然会出问题！！

```cpp
    string convert(string s, int numRows) {
        int t = 2 * numRows - 2;
        int i = 0;
        if (t == 0) {
            return s;
        }
        int round = s.length() / t;
        string res;
        while (i < numRows) {
            for (int j = 0; j + i < s.length(); j += t) {
                // 循环k轮，枚举每轮的起始下标
                res.push_back(s[j + i]); // 当前周期第一个字符
                // 注意，这里要限制0<i < numRows -1，因为第一行和最后一行只加一个数！！！！！
                if (0 < i && i < numRows - 1 && j + t - i < s.length()) {
                    res.push_back(s[j + t - i]);
                }
            }
            ++i;
        }
        return res;
    }
```

### 删除有序数组中的重复项

给你一个 升序排列 的数组 nums ，请你 原地 删除重复出现的元素，使每个元素 只出现一次 ，返回删除后数组的新长度。元素的 相对顺序 应该保持 一致 。

由于在某些语言中不能改变数组的长度，所以必须将结果放在数组nums的第一部分。更规范地说，如果在删除重复项之后有 k 个元素，那么 nums 的前 k 个元素应该保存最终结果。

将最终结果插入 nums 的前 k 个位置后返回 k 。

不要使用额外的空间，你必须在 原地 修改输入数组 并在使用 O(1) 额外空间的条件下完成。

**解法**

双指针，一快一慢，如果遇到不相等的，那就把快的值复制到慢的下一位，两个指针继续移动。

```cpp
    int removeDuplicates(vector<int>& nums) {
        if (nums.size() == 0) return 0;
        int i = 0;
        for (int j = 1; j < nums.size(); j++) {
            if (nums[j] != nums[i]) {
                // 不相等，且j比i快，那就说明ij中间可能是一串重复的数，
                // 就把num[j]赋值给num[i+1],然后两个指针都往后移
                nums[i + 1] = nums[j];
                ++i;
            }
        }
        return i + 1;
    }
```

### 螺旋矩阵

给你一个 m 行 n 列的矩阵 matrix ，请按照 顺时针螺旋顺序 ，返回矩阵中的所有元素。

参考[https://leetcode.cn/problems/spiral-matrix/solution/cxiang-xi-ti-jie-by-youlookdeliciousc-3/](https://leetcode.cn/problems/spiral-matrix/solution/cxiang-xi-ti-jie-by-youlookdeliciousc-3/)

+ 首先设定上下左右边界
+ 其次向右移动到最右，此时第一行因为已经使用过了，可以将其从图中删去，体现在代码中就是重新定义上边界
+ 判断若重新定义后，上下边界交错，表明螺旋矩阵遍历结束，跳出循环，返回答案
+ 若上下边界不交错，则遍历还未结束，接着向下向左向上移动，操作过程与第一，二步同理
+ 不断循环以上步骤，直到某两条边界交错，跳出循环，返回答案

```cpp
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        // 首先设定上下左右边界
        // 其次向右移动到最右，此时第一行因为已经使用过了，可以将其从图中删去，体现在代码中就是重新定义上边界
        // 判断若重新定义后，上下边界交错，表明螺旋矩阵遍历结束，跳出循环，返回答案
        // 若上下边界不交错，则遍历还未结束，接着向下向左向上移动，操作过程与第一，二步同理
        // 不断循环以上步骤，直到某两条边界交错，跳出循环，返回答案
        vector<int> res;
        if (matrix.empty()) {
            return res;
        }
        int up = 0;
        int right = matrix[0].size() - 1;
        int down = matrix.size() - 1;
        int left = 0;
        while(true) {
            for (int i = left; i <= right; ++i) {
                res.push_back(matrix[up][i]);
            }
            if (++up > down) break;
            for (int i = up; i <= down; ++i) {
                res.push_back(matrix[i][right]);
            }
            if (--right < left) break;
            for (int i = right; i >= left; --i) {
                res.push_back(matrix[down][i]);
            }
            if (--down < up) break;
            for (int i = down; i >= up; --i) {
                res.push_back(matrix[i][left]);
            }
            if (++left > right) break;
        }
        return res;
    }
```

### 判定字符是否唯一

实现一个算法，确定一个字符串 s 的所有字符是否全都不同。

```
示例 1：
输入: s = "leetcode"
输出: false 
```

位运算

其实就是位图，假设当前是b，那1左移'b'-'a'位，和mark&一下，如果是0，说明这一位还没有出现过，那就和mark|一下得到新的mark，反之，不是0的话，就说明这一位之前出现过了

```cpp
    bool isUnique(string astr) {
        int mark = 0;
        for (auto& i: astr) {
            int bit = i - 'a';
            int res = 1<<bit;
            // 这里要加括号！！因为!=比&的优先级要高。。
            //或者也可以直接 if(res&mark)
            if ((res & mark) != 0) {
                return false;
            }
            mark |= res;
        }
        return true;
    }
```

### 第一个错误的版本

你是产品经理，目前正在带领一个团队开发新的产品。不幸的是，你的产品的最新版本没有通过质量检测。由于每个版本都是基于之前的版本开发的，所以错误的版本之后的所有版本都是错的。

假设你有 n 个版本 [1, 2, ..., n]，你想找出导致之后所有版本出错的第一个错误的版本。

你可以通过调用 bool isBadVersion(version) 接口来判断版本号 version 是否在单元测试中出错。实现一个函数来查找第一个错误的版本。你应该尽量减少对调用 API 的次数。

二分

```cpp
    int firstBadVersion(int n) {
        int left = 0, right = n - 1;
        while(left <= right) {
            int mid = left + (right - left) / 2;
            if (isBadVersion(mid + 1)) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
       return left + 1;
    }
```

### 字符串相乘

给定两个以字符串形式表示的非负整数 num1 和 num2，返回 num1 和 num2 的乘积，它们的乘积也表示为字符串形式。

注意：不能使用任何内置的 BigInteger 库或直接将输入转换为整数。

就是模拟竖式计算。。

```cpp
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
```

### 最长连续序列

给定一个未排序的整数数组 nums ，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。

请你设计并实现时间复杂度为 O(n) 的算法解决此问题。

**其实只需要每次在哈希表中检查是否存在x−1即可。如果x-1存在，说明当前数x不是连续序列的起始数字，我们跳过这个数。**

```cpp
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
            if (!xset.count(item - 1)) {
                while (xset.count(item + i)) {
                    // cout << "aa2 " << i << " " << item-i << endl;
                    tmp_vec.emplace_back(item + i);
                    i++;
                }
            }
            tmp_len += i;
            if (tmp_len > max_len) {
                res_vec.swap(tmp_vec);
            }
            max_len = max(max_len, tmp_len);
        }
        return max_len;
    }
```


#### 类似的byte面试题

返回一个序列中最长的连续数组

题目描述
Input: ​
[0,  78, 1, 2, -1, 5, 6, 7, 7]​

Output: ​
[-1, 0, 1, 2]
​

自己的解法，能过68/71，超时。。其实两个while可以去掉一个，这样也只能过69/71

```cpp
#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

pair<vector<int>, int> get_max_len(const vector<int>& vec) {
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
        // 可以只留一个while
        while (xset.count(item - i)) {
            // cout << "aa1 " << i << " " << item-i << endl;
            tmp_vec.emplace_back(item - i);
            i++;
        }
        tmp_len += i;
        
        i = 1;
        while (xset.count(item + i)) {
            // cout << "aa2 " << i << " " << item-i << endl;
            tmp_vec.emplace_back(item + i);
            i++;
        }
        tmp_len += i -1;
        if (tmp_len > max_len) {
            res_vec.swap(tmp_vec);
        }
        max_len = max(max_len, tmp_len);
    }
    return {res_vec, max_len};
}

int main() {
    vector<int> vec {0, 78, 1,2,-1,5,6,7,7};
    auto res = get_max_len(vec);
    cout << res.second << endl;
    cout << "=====" << endl;
    for (const auto&i: res.first) {
        cout << i << endl;
    }

    return 0;
}
```

优化后的解法：

```cpp
#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

pair<vector<int>, int> get_max_len(const vector<int>& vec) {
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
//        // 可以只留一个while
//        while (xset.count(item - i)) {
//            // cout << "aa1 " << i << " " << item-i << endl;
//            tmp_vec.emplace_back(item - i);
//            i++;
//        }
//        tmp_len += i;

//        i = 1;
        if (!xset.count(item - 1)) {
            while (xset.count(item + i)) {
                // cout << "aa2 " << i << " " << item-i << endl;
                tmp_vec.emplace_back(item + i);
                i++;
            }
        }
//        tmp_len += i -1;
        tmp_len += i;
        if (tmp_len > max_len) {
            res_vec.swap(tmp_vec);
        }
        max_len = max(max_len, tmp_len);
    }
    return {res_vec, max_len};
}

int main() {
    vector<int> vec {0, 78, 1,2,-1,5,6,7,7};
    auto res = get_max_len(vec);
    cout << res.second << endl;
    cout << "=====" << endl;
    for (const auto&i: res.first) {
        cout << i << endl;
    }

    return 0;
}
```


## 链表

### 两数相加

给你两个 非空 的链表，表示两个非负的整数。它们每位数字都是按照 逆序 的方式存储的，并且每个节点只能存储 一位 数字。

请你将两个数相加，并以相同形式返回一个表示和的链表。

你可以假设除了数字 0 之外，这两个数都不会以 0 开头。
head->...->tail 是倒序的整数，求两个整数的和，并返回同样格式的链表

```cpp
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int carry = 0;// 进位
        ListNode* dummy_head = new ListNode(0); //需要有个dummy head，最后return head->next
        ListNode* tmp = dummy_head;
        ListNode* ptr1 = l1;
        ListNode* ptr2 = l2;
        while (ptr1 != NULL || ptr2 != NULL) {
            int val1 = ptr1 != NULL? ptr1->val: 0;
            int val2 = ptr2 != NULL? ptr2->val: 0;
            int sum = val1 + val2 + carry;
            //cout << sum << " " << carry << " " << val1 << " " << val2 << endl;
            carry = sum / 10; // 很重要！！！！！新的carry
            int remain = sum % 10;
            tmp->next = new ListNode(remain);
            ptr1 = (NULL == ptr1? NULL: ptr1->next); //判断的是ptr1，而不是ptr1->next！！！！！！
            ptr2 = (NULL == ptr2? NULL: ptr2->next);
            tmp = tmp->next;
        }
        if (carry > 0) {
            tmp->next = new ListNode(carry);
        }
        return dummy_head->next;
    }
```

### 奇偶链表

给定单链表的头节点 head ，将所有索引为奇数的节点和索引为偶数的节点分别组合在一起，然后返回重新排序的列表。

第一个节点的索引被认为是 奇数 ， 第二个节点的索引为 偶数 ，以此类推。

请注意，偶数组和奇数组内部的相对顺序应该与输入时保持一致。

你必须在 O(1) 的额外空间复杂度和 O(n) 的时间复杂度下解决这个问题。

12345 变成13524

```cpp
    ListNode* oddEvenList(ListNode* head) {
        // 先把第一个偶数保存下来，
        // 跳着指(2->4,3->5)，
        // 最后再把奇数的指向第一个偶数，
        // return的应该还是head
        if (head == nullptr) {
            return nullptr;
        }
        ListNode* even_head = head->next; //第一个偶数，存下来
        ListNode* odd = head;
        ListNode* even = even_head;
        while (even != nullptr && even->next != nullptr) {
            odd->next = even->next;
            odd = odd->next;
            even->next = odd->next;
            even = even->next;
        }
        odd->next = even_head;
        return head;
    }
```

### 最长回文子串

```
输入：s = "babad"
输出："bab"
解释："aba" 同样是符合题意的答案。
```

dp

```cpp
    string longestPalindrome(string s) {
        // p(i,j)表示i:j是回文串
        // 转移：
        // if  si == sj then p(i,j) = p(i+1, j-1)
        // 边界：len=1是，len=2，如果si==sj那是
        // 结果就是所有p(i,j)=1的j-i+1的max
        int n = s.size();
        if (n < 2) {
            return s;
        }
        int max_len = 1;
        int begin = 0;
        // n * n的矩阵
        vector<vector<bool> > dp(n, vector<bool>(n));
        for (int i = 0; i < n; ++i) {
            dp[i][i] = true;//1个字符的肯定是

        }
        // L是子串长度
        for (int L = 2; L <= n; ++L) {
            for (int i = 0; i < n; ++i) {
                // 根据L找j的位置, L = j-i+1
                int j = L + i - 1;
                if (j >= n) {
                    break; // 到尽头了
                }
                if (s[i] != s[j]) {
                    dp[i][j] = false;
                } else {
                    if (j - i < 3) { // a aa aba 都ok
                        dp[i][j] = true;
                    } else {
                        dp[i][j] = dp[i + 1][j - 1];
                    }
                }

                if (dp[i][j] && L > max_len) {
                    max_len = L;
                    begin = i;
                }

            }
        }
        return s.substr(begin, max_len);

    }
```

### 递增的三元子序列

给你一个整数数组 nums ，判断这个数组中是否存在长度为 3 的递增子序列。

如果存在这样的三元组下标 (i, j, k) 且满足 i < j < k ，使得 nums[i] < nums[j] < nums[k] ，返回 true ；否则，返回 false 。
```cpp
    bool increasingTriplet(vector<int>& nums) {
        // first < second,且second肯定大于first，那么如果second右边的比second大，就是找到了
        int n = nums.size();
        //if (n < 3) {
        //    return false;
        //}
        int first = INT_MAX, second = INT_MAX;
        for (int i = 0; i < n; ++i) {
            int num = nums[i];
            if (num <= first) {
                first = num; // 更新第一个数
            } else if (num <= second) {
                second = num; // 这个数比first大，那就是second
            } else {
                // 如果这个数比两个数都大，那return
                return true; 
            }
        }
        return false;
    }
```

### 相交链表

返回交点

```cpp
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        // a b一直走，判断是否相等，假设b比a长
        // a到null的时候，a从b的头开始，这样和b一起走b-a的长度；
        // b到null的时候，二者都走了b-a，b从a的头开始，就能和a相遇了
        // 假设没交点，那最后两个都会指向null
        if (headA == nullptr || headB == nullptr) {
            return nullptr;
        }
        ListNode* p1 = headA;
        ListNode* p2 = headB;
        while (p1 != p2) {
            p1 = (p1 == nullptr? headB: p1->next);
            p2 = (p2 == nullptr? headA: p2->next);
        }
        return p1;
    }
```

### 合并两个有序链表

将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。 

**解法**

当 l1 和 l2 都不是空链表时，判断 l1 和 l2 哪一个链表的**头节点的值更小**，将**较小值的节点添加到结果**里，当一个节点被添加到结果里之后，将对应链表中的节点向后移一位。

设定一个哨兵节点 pre_head

然后3个指针，l1 l2分别有一个，还有一个prev

比较l1 l2，假设l1小，那就prev指向l1，然后prev+1，l1+1

比较l1 l2，假设l2小，那就prev指向l2，然后prev+1，l2+1

所以prev都要+1，可以只写一次

```cpp
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        // dummy head也得有个值，不能是个空的。。
        ListNode* pre_head = new ListNode(-1);
        ListNode* prev = pre_head;
        // 用&&，因为只要有一个到头了，其实就可以结束了
        while (list1 != nullptr && list2 != nullptr) {
            if (list1->val < list2->val) {
                prev->next = list1;
                list1 = list1->next;
            } else {
                prev->next = list2;
                list2 = list2->next;
            }
            prev = prev->next;
        }
        //如果l1到头了，那就指向l2剩下的元素
        prev->next = (list1 == nullptr? list2: list1);
        return pre_head->next;
    }
```

### 合并K个升序链表

给你一个链表数组，每个链表都已经按升序排列。

请你将所有链表合并到一个升序链表中，返回合并后的链表。

**解法**

维护当前**每个链表没有被合并的元素的最前面一个**，k个链表就最多有 k 个满足这样条件的元素，每次在这些元素里面**选取 $$\textit{val}$$ 属性最小的元素**合并到答案中。在选取最小元素的时候，我们可以用优先队列来优化这个过程。(**即小顶堆，比较函数是a>b**)

```cpp
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        
        struct MyCmp {
            bool operator()(ListNode* a, ListNode* b) {
                return a->val > b->val;
            }
        };
        // 小顶堆
        priority_queue<ListNode*, vector<ListNode*>, MyCmp> q;

        for (auto &h : lists) {
            if (h != nullptr) {
                q.push(h);
            }
        }
        ListNode* head = new ListNode(0); // dummy head
        ListNode* p = head;
        while (!q.empty()) {
            p->next = q.top();
            p = p->next;
            q.pop();
            if (p->next != nullptr){
                // 用了第xx个链表的节点，那就把它的下一个节点丢进来
                q.push(p->next);
            }
        }
        return head->next;// 因为head是dummy，所以返回next
    }
```

### 链表反转

给你单链表的头节点 head ，请你反转链表，并返回反转后的链表。
 
```
示例 1：
输入：head = [1,2,3,4,5]
输出：[5,4,3,2,1]
```

背下来

```cpp
    ListNode* reverseList(ListNode* head) {
        //prev cur next三个指针
        // prev初始化为空，很重要，因为head要指向它！！
        ListNode* prev = nullptr;
        ListNode* cur = head;
        while (cur) {
            // 记录下一个节点next
            ListNode* next = cur->next;
            // 往回指，涉及到xx->next的时候，只有cur->next=pre
            cur->next = prev;
            // 更新prev
            prev = cur;
            // 更新cur
            cur = next;
        }
        return prev;
    }
```

### K 个一组翻转链表

给你链表的头节点 head ，每 k 个节点一组进行翻转，请你返回修改后的链表。

k 是一个正整数，它的值小于或等于链表的长度。**如果节点总数不是 k 的整数倍，那么请将最后剩余的节点保持原有顺序。**

你不能只是单纯的改变节点内部的值，而是需要实际进行节点交换。

```cpp
    // 返回的是新的head和tail
    pair<ListNode*, ListNode*> myReverse(ListNode* head, ListNode* tail) {
        ListNode* prev = tail->next;
        ListNode* cur = head;
        while (prev != tail) {
            ListNode* next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        return {tail, head};
    }
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        ListNode* pre = dummy;
        while (head) { // while head
            ListNode* tail = pre;
            for (int i = 0; i < k; ++i) {
                tail = tail->next;
                if (tail == nullptr) {
                    // 因为题目要求的是，如果节点总数不是 k 的整数倍，
                    // 那么请将最后剩余的节点保持原有顺序。
                    return dummy->next; // 直接return了
                }
            }
            ListNode* xx = tail->next;
            pair<ListNode*, ListNode*> res = myReverse(head, tail);
            head = res.first;
            tail = res.second;
            // 把反转后的接到原链表中
            pre->next = head;
            tail->next = xx;
            // 更新pre和head
            pre = tail;
            head = tail->next;
        }
        return dummy->next;
    }
```

### 链表的中间结点

给定一个头结点为 head 的非空单链表，返回链表的中间结点。

如果有两个中间结点，则返回第二个中间结点。

**解法**

快慢指针，快的走两步，慢的一步，快的到tail时，慢的就是要的了

```cpp
    ListNode* middleNode(ListNode* head) {
        // 起点一样，都是head
        ListNode* fast = head;
        ListNode* slow = head;
        // 注意判断条件，&&
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }
```

### 重排链表

给定一个单链表 L 的头节点 head ，单链表 L 表示为：

```
L0 → L1 → … → Ln - 1 → Ln
请将其重新排列后变为：
L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …
```
不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。

**寻找链表中点 + 链表逆序 + 合并链表**

可以发现，其实就是先把右半边的链表反转，然后和左半边的链表一个个归并

```cpp
    void reorderList(ListNode* head) {
        ListNode* mid = middle_node(head);
        ListNode* l1 = head;
        // 搞出一个mid来
        ListNode* l2 = mid->next;
        l2 = reverse_list(l2);
        // 把l1变短
        mid->next = nullptr;
        merge_list(l1, l2);
    }

    ListNode* middle_node(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }
    ListNode* reverse_list(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* cur = head;
        while (cur) {
            ListNode* next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        return prev;
    }
    void merge_list(ListNode* l1, ListNode* l2) {
        ListNode* l1_p;
        ListNode* l2_p;
        while (l1 != nullptr && l2 != nullptr) {
            // 先记录当前的next
            l1_p = l1->next;
            l2_p = l2->next;
            l1->next = l2;
            l2->next = l1_p;
            l1 = l1_p;
            l2 = l2_p;
        }
    }
```

### 反转链表 II

给你单链表的头指针 head 和两个整数 left 和 right ，其中 left <= right 。请你反转从位置 left 到位置 right 的链表节点，返回 反转后的链表 。

```cpp
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        
        ListNode* dummy = new ListNode(-1);
        dummy->next = head;
        ListNode* prev = dummy; // 不能prev=nullptr了
        ListNode* cur = head;
        if (left == right || head->next == nullptr) {
            return head;
        }
        for(int i = 1; i <= left - 1; ++i) {
            // 如果prev初始化为nullptr，这里就崩了
            prev = cur;
            cur = cur->next;
        }
        ListNode* x_start = prev;
        ListNode* x_start2 = cur;

        for (int j = 0; j < right - left; ++j) {
            ListNode* next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        // 挂回去
        ListNode* x = cur->next;
        x_start->next = cur;
        x_start2->next = x;
        cur->next = prev;
        return dummy->next;
    }
```

### 排序链表

给你链表的头结点 head ，请将其按 升序 排列并返回 排序后的链表 。

**解法**

找到中点，然后归并排序

```cpp
    ListNode* middle_node(ListNode* head, ListNode* tail) {
        ListNode* fast = head;
        ListNode* slow = head;
        while (fast != tail && fast->next != tail) {
            fast = fast->next->next;
            slow = slow->next;
        }
        return slow;
    }
    ListNode* sort_list(ListNode* head, ListNode* tail) {
        if (head == nullptr) {
            return head;
        }
        //必须要有这段。。
        if (head->next == tail) {
            head->next = nullptr;
            return head;
        }
        ListNode* mid = middle_node(head, tail);
        ListNode* l1 = sort_list(head, mid);
        ListNode* l2 = sort_list(mid, tail);
        return merge(l1, l2);
    }
    ListNode* merge(ListNode* l1, ListNode* l2) {
        // 链表版的归并，加个dummy简单点。。
        ListNode* dummy = new ListNode(0);
        ListNode* cur = dummy;
        ListNode* tmp1 = l1;
        ListNode* tmp2 = l2;
        while (tmp1 != nullptr && tmp2 != nullptr) {
            if (tmp1->val <= tmp2->val) {
                cur->next = tmp1;
                tmp1 = tmp1->next;
            } else {
                cur->next = tmp2;
                tmp2 = tmp2->next;
            }
            cur = cur->next;//别漏了这个。。
        }
        if (tmp1 != nullptr) {
            cur->next = tmp1;
        } else if (tmp2 != nullptr) {
            cur->next = tmp2;
        }
        return dummy->next;
    }
    ListNode* sortList(ListNode* head) {
        return sort_list(head, nullptr);
    }
```


## 树

### 二叉树的中序遍历

栈 一直塞左子树，取出栈顶，扔到res里去，pop出来，开始遍历原栈顶的右子树

```cpp
vector<int> inorderTraversal(TreeNode* root) {
        stack<TreeNode*> stk;
        vector<int> res;
        while (root != nullptr || !stk.empty()) { // 两个条件 或！！！！
            while (root != nullptr) { // 一直把root的左子树丢进去
                stk.push(root);
                root = root->left;
            }
            root = stk.top();
            stk.pop(); // 栈顶扔出来
            res.emplace_back(root->val); // 值搞进去
            root = root->right; // 开始原栈顶的右子树
        }
        return res;
    }
```

### 层序遍历

队列（bfs）queue

### 二叉树的锯齿形层序遍历
给你二叉树的根节点 root ，返回其节点值的 锯齿形层序遍历 。（即先从左往右，再从右往左进行下一层遍历，以此类推，层与层之间交替进行）。

队列+优先队列deque

```cpp
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        // 层序遍历，加个参数，奇数左到右，偶数右到左
        // dequeue，双端队列
        vector<vector<int> > res;
        if (root == nullptr) {
            return res;
        }
        queue<TreeNode*> q;
        q.push(root);
        bool left_order = true;
        while (!q.empty()) {
            deque<int> level_lst;
            int size = q.size();
            for (int i = 0; i < size; ++i) { // 这里写size，而不是q.size，因为q一直在变！！！
                TreeNode* node = q.front();
                q.pop();
                if (left_order) {
                    level_lst.push_back(node->val);
                } else {
                    level_lst.push_front(node->val);
                }
                if (node->left) {
                    q.push(node->left);
                }
                if (node->right) {
                    q.push(node->right);
                }
            }
            res.emplace_back(vector<int>(level_lst.begin(), level_lst.end()));
            left_order = !left_order;
        }
        return res;
    }
```

### 从前序与中序遍历序列构造二叉树

前序：根 \[左]\[右] 中序：\[左] 根 \[右] 找到根在中序里的位置（先用map存好值-位置关系，o1查），然后递归

```cpp
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        // 递归：
        // 通过前序找到根，再在中序里找到根的位置，左边是左子树，右边是右子树，这样就知道在前序里走几步是左，后面的就是右
        // 因此，区间的端点就是递归的参数
        // 把中序的值和index存到一个map里，这样就能知道在前序中的区间位置了
        int len_pre = preorder.size();
        int len_in = inorder.size();
        if (len_pre != len_in) {
            return nullptr;
        }
        unordered_map<int, int> xmap;
        for (int i = 0; i < len_in; ++i) {
            xmap.emplace(inorder[i], i);
        }
        // 前序，左右区间；中序map，左右区间
        return buildTreeSub(preorder, 0, len_pre - 1, xmap, 0, len_in - 1);
    }
    
    // 这里xmap要传引用，不然会超时。。
    TreeNode* buildTreeSub(vector<int>& preorder, int pre_start, int pre_end, unordered_map<int, int>& xmap, int in_start, int in_end) {
        if (pre_start > pre_end || in_start > in_end) { // 终止条件
            return nullptr;
        }
        int root_val = preorder[pre_start];
        TreeNode* root = new TreeNode(root_val);
        int in_index = xmap[root_val]; //肯定会有
        root->left = buildTreeSub(preorder, pre_start + 1, pre_start + in_index - in_start, xmap, in_start, in_index - 1);
        root->right = buildTreeSub(preorder, pre_start + in_index - in_start + 1, pre_end, xmap, in_index + 1, in_end);
        return root;
    }

        
        // 迭代法(看不懂)：
        // 前序中的任意连续两个节点u,v而言，要么v是u的左儿子，
        // 要么u没有左儿子的话，那么v就是u或者u的祖先的右儿子（u向上回溯，到第一个有右儿子的就是他的右儿子）
```

### 二叉搜索树中第K小的元素

给定一个二叉搜索树的根节点 root ，和一个整数 k ，请你设计一个算法查找其中第 k 个最小元素（从 1 开始计数）。

**解法**

左边比根小，右边比根大，那就中序遍历，遍历完成左，然后根，然后右，然后k--，减到0就是了 中序就是栈

```cpp
    int kthSmallest(TreeNode* root, int k) {
        // 栈，中序遍历,左子树都比它小，所以找topk小，就先遍历完左的，再遍历它，再右
        stack<TreeNode*> stk;
        while (root != nullptr || stk.size() > 0) {
            while (root != nullptr) {
                stk.push(root);
                root = root->left;
            }
            root = stk.top();
            stk.pop();
            --k;
            if (k == 0) {
                break;
            }
            root = root->right;
        }
        return root->val;
    }
```

### 二叉树的右视图

给定一个二叉树的 根节点 root，想象自己站在它的右侧，按照从顶部到底部的顺序，返回从右侧所能看到的节点值。

**解法1：dfs**

按照根->右->左的方法，每层先访问到的是右节点

```cpp
    // dfs版本
    // 按照根->右->左的方法，每层先访问到的是右节点
    vector<int> rightSideView(TreeNode* root) {
        unordered_map<int, int> right_map;
        int max_depth = -1;
        stack<TreeNode*> node_stk;
        stack<int> depth_stk;
        node_stk.push(root);
        depth_stk.push(0);
        while (!node_stk.empty()) {
            TreeNode* node = node_stk.top();
            node_stk.pop();
            int depth = depth_stk.top();
            depth_stk.pop();
            if (node != nullptr) {
                max_depth = max(max_depth, depth);
                // 只搞一次
                if (right_map.find(depth) == right_map.end()) {
                    right_map[depth] = node->val;
                }
                // stk是后进先出，所以先left再right
                node_stk.push(node->left);
                node_stk.push(node->right);
                depth_stk.push(depth + 1);
                depth_stk.push(depth + 1);
            }
        }
        vector<int> res;
        for (int depth = 0; depth <= max_depth; ++depth) {
            res.push_back(right_map[depth]);
        }
        return res;
    }
```

**解法2：bfs**

bfs层序遍历（queue），记录每层的最后一个元素

```cpp
    // bfs版本
    // bfs层序遍历（queue），记录每层的最后一个元素
    vector<int> rightSideView(TreeNode* root) {
        unordered_map<int, int> right_map;
        int max_depth = -1;
        queue<TreeNode*> node_q;
        queue<int> depth_q;
        node_q.push(root);
        depth_q.push(0);
        while (!node_q.empty()) {
            TreeNode* node = node_q.front();
            node_q.pop();
            int depth = depth_q.front();
            depth_q.pop();
            if (node != nullptr) {
                // 记录最大深度
                max_depth = max(max_depth, depth);
                // 不断更新，最后一个就是最右边的了
                right_map[depth] = node->val;
                // left right都要扔进去，且都要扔depth+1进去
                node_q.push(node->left);
                depth_q.push(depth + 1);
                node_q.push(node->right);
                depth_q.push(depth + 1);
            }
        }
        vector<int> res;
        for (int depth = 0; depth <= max_depth; ++depth) {
            res.push_back(right_map[depth]);
        }
        return res;
    }
```

### 二叉树的直径

给定一棵二叉树，你需要计算它的直径长度。一棵二叉树的直径长度是任意两个结点路径长度中的最大值。这条路径可能穿过也可能不穿过根结点。

**解法**

![](./assets/tree-diameter.jpeg)

经过节点的最长路径就是**左孩子深度+右孩子深度**，

因此，求出所有节点的最长路径，取个max就是了

而求深度可以用递归的dfs，**depth返回的是max(左深度,右深度)+1**

```cpp
    int depth_max = 0;
    int depth(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        int left_depth = depth(root->left);
        int right_depth = depth(root->right);
        int cur_depth = left_depth + right_depth;
        depth_max = max(depth_max, cur_depth);
        return max(left_depth, right_depth) + 1;
    }

    int diameterOfBinaryTree(TreeNode* root) {
        depth(root);
        return depth_max;
    }
```

## 图

### 岛屿数量

给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。

岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。

此外，你可以假设该网格的四条边均被水包围。


以1开始，dfs，visited置0，dfs就是上下左右地递归：

```cpp
    int numIslands(vector<vector<char>>& grid) {
        // dfs，看成一个无向图，垂直或者水平相邻的1之间是一条边
        // 遇到1，就以它为起点，dfs，每个走到的1重新记为0！！！
        // 这样，走了多少次dfs，就有多少个岛屿
        // dfs中 就是先置0，然后上下左右分别递归找
        int rows = grid.size();
        if (rows == 0) {
            return 0;
        }
        int cols = grid[0].size();
        int num_islands = 0;
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] == '1') {
                    ++num_islands;
                    dfs(grid, r, c);
                }
            }
        }
        return num_islands;

    }
    void dfs(vector<vector<char> >& grid, int r, int c) {
        int rows = grid.size();
        int cols = grid[0].size();
        grid[r][c] = '0';
        if (r -1 >= 0 && grid[r - 1][c] == '1') {
            dfs(grid, r - 1, c); // 上
        }
        if (r + 1 < rows && grid[r + 1][c] == '1') {
            dfs(grid, r + 1, c); // 下
        }
        if (c - 1 >= 0 && grid[r][c - 1] == '1') {
            dfs(grid, r, c - 1); // 左
        }
        if (c + 1 < cols && grid[r][c + 1] == '1') {
            dfs(grid, r, c+1); // 右
        }
    }
```

## 回溯法

### 回溯小结

回溯法：一种通过探索所有可能的候选解来找出所有的解的算法。如果候选解被确认不是一个解（或者至少不是最后一个解），回溯算法会通过在上一步进行一些变化抛弃该解，即回溯并且再次尝试。

套路： 调用：

```cpp
        vector<string> res; // 也可能是vec的vec
        string cur; // 也可能是vec，看题目
        backtrace(res, cur, xxx);
        return res;
```

回溯函数：

```cpp
    void backtrace(vector<string>& res, string& cur, xxx) { // xxx一般有两个参数，当前值a，上限len
        if (aaaa) { // a+1之类的 加到上限了如
            res.push_back(cur);
            return;
        }
        if (bbbb) {
            cur.push_back('aaa'); //扔进去
            backtrace(res, cur, xxxx); // a+1之类的操作,把len也传进去
            cur.pop_back(); // 放出来
        }
    }
```

模板：

```
回溯(子集, 全集):
    if 满足条件:
        加入答案
    for 元素 in 全集:
        元素加入子集
        回溯(子集, 全集)
        元素退出子集
```

### N皇后

n 皇后问题 研究的是如何将 n 个皇后放置在 n × n 的棋盘上，并且使皇后彼此之间不能相互攻击。

给你一个整数 n ，返回 n 皇后问题 不同的解决方案的数量。

每一种解法包含一个不同的 n 皇后问题 的棋子放置方案，该方案中 'Q' 和 '.' 分别代表了皇后和空位。

**解法**

回溯法

每个皇后必须位于不同行和不同列，因此将 N 个皇后放置在 $$N \times N$$ 的棋盘上，一定是**每一行有且仅有一个皇后**，**每一列有且仅有一个皇后**，且**任何两个皇后都不能在同一条斜线上**。

使用一个数组记录**每行**放置的皇后的**列下标**，依次在每一行放置一个皇后。每次新放置的皇后都不能和已经放置的皇后之间有攻击：即新放置的皇后**不能**和任何一个已经放置的皇后在**同一列**以及**同一条斜线**上，并更新数组中的当前行的皇后列下标。

N 个皇后都放置完毕，则找到一个可能的解

为了判断一个位置所在的列和两条斜线上是否已经有皇后，使用三个集合 $$\textit{columns}$$、$$\textit{diagonals}_1$$和 $$\textit{diagonals}_2$$分别记录**每一列以及两个方向的每条斜线上是否有皇后**。


```cpp
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string> > solutions = vector<vector<string> >();
        vector<int> queens = vector<int>(n, -1); //初始化都是-1
        unordered_set<int> columns;
        unordered_set<int> diagonals1;
        unordered_set<int> diagonals2;
        backtrack(solutions, queens, n, 0, columns, diagonals1, diagonals2);
        return solutions;
    }

    vector<string> generate_board(vector<int>& queens, int n) {
        vector<string> board;
        for (int i = 0; i < n; ++i) {
            string row = string(n, '.'); // 初始化为n个.
            row[queens[i]] = 'Q';
            board.push_back(row);
        }
        return board;
    }
    void backtrack(vector<vector<string> > &solutions, vector<int>& queens, 
        int n, int row, unordered_set<int>& columns, 
        unordered_set<int>& diagonals1, unordered_set<int> diagonals2) {
        if (row == n) {
            vector<string> board = generate_board(queens, n); 
            solutions.push_back(board);
        } else {
            for (int i = 0; i < n; ++i) {
                if (columns.count(i)) {
                    continue;
                }
                int diagonal1 = row - i;
                if (diagonals1.count(diagonal1)) {
                    continue;
                }
                int diagonal2 = row + i;
                if (diagonals2.count(diagonal2)) {
                    continue;
                }
                queens[row] = i; // 放进来试试
                columns.insert(i); // 这一列不能继续放
                diagonals1.insert(diagonal1); // 左上角不能继续放
                diagonals2.insert(diagonal2); // 右上角不能继续放
                backtrack(solutions, queens, n, row + 1, columns, diagonals1, diagonals2);
                // 还原
                queens[row] = -1;
                columns.erase(i); 
                diagonals1.erase(diagonal1);
                diagonals2.erase(diagonal2);
            }
        }
    }
```

### 电话号码的字母组合

给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。答案可以按 任意顺序 返回。

给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。


```cpp
    vector<string> letterCombinations(string digits) {
        // 回溯+dfs
        unordered_map<char, string> phone_map {
            {'2', "abc"}, 
            {'3', "def"},
            {'4', "ghi"},
            {'5', "jkl"},
            {'6', "mno"},
            {'7', "pqrs"},
            {'8', "tuv"},
            {'9', "wxyz"}
        };
        vector<string> res;
        if (digits.empty()) {
            return res;
        }
        string comb;
        backtrace(res, phone_map, digits, 0, comb);
        return res;
    }
    void backtrace(vector<string>& res, const unordered_map<char, string>& phone_map, 
        const string& digits, int index, string& comb_str) {
            // index:输入的digits的第index个字母
            if (index == digits.length()) {
                 res.push_back(comb_str);
            } else {
                char digit = digits[index];
                const string& letters = phone_map.at(digit);
                for (const char& letter: letters) {
                    comb_str.push_back(letter); // 先搞一个
                    backtrace(res, phone_map, digits, index + 1, comb_str);
                    comb_str.pop_back(); // 扔掉，换一个新的
                }
            }

    }
```

### 括号生成

数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。

有效括号组合需满足：左括号必须以正确的顺序闭合。


```cpp
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        string cur;
        backtrace(res, cur, 0, 0, n);
        return res;
    }
    // open左括号个数，close 右括号个数
    void backtrace(vector<string>& res, string& cur, int open, int close, int n) {
        if (cur.size() == n * 2) { // 一共2n个左右括号
            res.push_back(cur);
            return;
        }
        if (open < n) { // 还可以继续加左括号（最多可以加n个）
            cur.push_back('(');
            backtrace(res, cur, open + 1, close, n);
            cur.pop_back();
        }
        if (close < open) { // 准备加新的右括号了
            cur.push_back(')');
            backtrace(res, cur, open, close + 1, n);
            cur.pop_back();
        }
    }
```

### 全排列

给定一个不含重复数字的数组 nums ，返回其 所有可能的全排列 。你可以 按任意顺序 返回答案。

```
输入：nums = [1,2,3]
输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
```

```cpp
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int> > res;
        backtrace(res, nums, 0, nums.size());
        return res;
    }
    void backtrace(vector<vector<int> >& res, vector<int>& output, int first, int len) {
        if (first == len) {
            res.push_back(output);
        }
        for (int i = first; i < len; ++i) {
            swap(output[i], output[first]); // 交换
            backtrace(res, output, first + 1, len);
            swap(output[i], output[first]); // 换回去
        }
    }
```

### 下一个排列

整数数组的一个 排列  就是将其所有成员以序列或线性顺序排列。

例如，arr = [1,2,3] ，以下这些都可以视作 arr 的排列：[1,2,3]、[1,3,2]、[3,1,2]、[2,3,1] 。

整数数组的 下一个排列 是指其整数的**下一个字典序更大的排列**。更正式地，如果数组的所有排列根据其字典顺序从小到大排列在一个容器中，那么数组的 下一个排列 就是在这个有序容器中排在它后面的那个排列。**如果不存在下一个更大的排列，那么这个数组必须重排为字典序最小的排列**（即，其元素按升序排列）。

例如，arr = [1,2,3] 的下一个排列是 [1,3,2] 。

类似地，arr = [2,3,1] 的下一个排列是 [3,1,2] 。

而 arr = [3,2,1] 的下一个排列是 [1,2,3] ，因为 [3,2,1] 不存在一个字典序更大的排列。

给你一个整数数组 nums ，找出 nums 的下一个排列。

必须 原地 修改，只允许使用额外常数空间。

**解法**

找到一个大于当前序列的新序列，且变大的幅度尽可能小。

+ 将一个**左边的较小数与右边的较大数进行交换**，这样当前排列可以变大
+ 让较小数尽可能靠右，较大数尽可能小。
  + 那就从右往左遍历，找到第一个**a[i] < a[i+1]**的，这样它的右边才会有比它小的，所以这是较大数
  + 再从右往左遍历一遍，找到第一个**a[j] > a[i]**的，所以这是较小数
+ 交换完成后，较大数右边的数按升序重新排列。
  + 其实上面这么找，就表示了i+1的右边在交换后是降序的，因为a[j-1] > a[j] > a[j+1]，而a[j]是第一个比a[i]大的，所以a[j+1] < a[j]，所以a[j-1]>a[j]>a[j+1]

```cpp
    void nextPermutation(vector<int>& nums) {
        int i = nums.size() - 2;// 因为要和i+1比较
        //找到第一个a[i]<a[i+1]
        while (i >= 0 && nums[i] >= nums[i + 1]) {
            --i;
        }
        if (i >= 0) {
            int j = nums.size() - 1;
            // 找到第一个j，使得a[i]>a[j]
            while (j >= 0 && nums[i] >= nums[j]) {
                j--;
            }
            swap(nums[i], nums[j]);
        }
        // 就算i<0，那就是i=-1，仍然成立
        reverse(nums.begin() + i + 1, nums.end());
    }
```

### 子集

给你一个整数数组 nums ，数组中的元素 互不相同 。返回该数组所有可能的子集（幂集）。

解集 不能 包含重复的子集。你可以按 任意顺序 返回解集。

```
输入：nums = [1,2,3]
输出：[[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
```


调用两次dfs，因为对于子集来说，每个数字可以选也可以不选。

```cpp
    void dfs(vector<vector<int> > &res, const vector<int>& nums, vector<int>& cur_res, int cur) {
        if (cur == nums.size()) {
            res.push_back(cur_res);
            return;
        }
        // 调用两次dfs，因为对于子集来说，每个数字可以选也可以不选。
        cur_res.push_back(nums[cur]);
        dfs(res, nums, cur_res, cur + 1);
        cur_res.pop_back();
        dfs(res, nums, cur_res, cur + 1);
    }

    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int> > res;
        vector<int> cur_res;
        dfs(res, nums, cur_res, 0);
        return res;
    }
```

### 单词搜索

给定一个 m x n 二维字符网格 board 和一个字符串单词 word 。如果 word 存在于网格中，返回 true ；否则，返回 false 。

单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。


```cpp
    bool check(vector<vector<char> >& board, vector<vector<int> >& visited, 
        int i, int j, string word, int k) {
        if (board[i][j] != word[k]) { //不匹配，不行 
            return false;
        } else if (k == word.length() - 1) { //到最后一个词了且相等，ok
            return true;
        }
        visited[i][j] = true;
        // 上下左右
        vector<pair<int, int> > directions{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        bool res = false;
        for (const auto& dir: directions) {
            int new_i = i + dir.first;
            int new_j = j + dir.second;
            if (new_i >= 0 && new_i < board.size() && new_j >= 0 && new_j < board[0].size()) {
                if(!visited[new_i][new_j]) {
                    bool flag = check(board, visited, new_i, new_j, word, k + 1);
                    if (flag) {
                        res = true;
                        break;
                    }
                }
            }
        }
        visited[i][j] = false; //还原
        return res;
    }
    bool exist(vector<vector<char>>& board, string word) {
        int h = board.size(), w = board[0].size();
        vector<vector<int> > visited(h, vector<int>(w));
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                bool flag = check(board, visited, i, j, word, 0);
                if (flag) {
                    return true;
                }
            }
        }
        return false;
    }
```

## 排序与搜索

### 各排序算法总结

![sort](assets/sort.jpeg)

大小顶堆参考：

```cpp
//小顶堆(是大于。。不是小于)，这也是默认
priority_queue <int,vector<int>,greater<int> > q;
//大顶堆
priority_queue <int,vector<int>,less<int> >q;
//默认大顶堆
priority_queue<int> a;

// 自定义比较函数：（小顶堆，实现大于操作）
struct MyCmp {
    bool operator()(pair<int, int>& a, pair<int, int>& b) {
        return a.second > b.second;
    }
};
// 小顶堆
priority_queue<pair<int, int>, vector<pair<int, int> >, MyCmp> q;
```

### 排序数组

给你一个整数数组 nums，请你将该数组升序排列。

借这题复习快排、堆排和归并

#### 快排

背起来，几个注意点：

+ vector一直是按引用传，中间函数都不返回vector
+ 主函数先随机一下```srand((unsigned)time(NULL));```
+ partion/randomized_partition都是返回下标int，qsort返回的是void
+ qsort一进来```l<r```，然后先通过l和r拿到pos，再递归两次qsort，分别是l, pos -1和pos + 1, r
+ randomized_partition
    + 先随机一个i出来(l之后加一个r-l+1范围内的随机数，```i=rand()%(r-l+1)+l```)
    + 然后把num[i]和num[r]互换（```swap(nums[i], nums[r]);```）
    + 然后```return partition(nums, l, r);```
+ partition
    + xx


```cpp
    int partition(vector<int>& nums, int l, int r) {
        int pivot = nums[r];
        int i = l;
        // 期望num[i]都比pivot小，num[j]都比pivot大
        // 所以一旦num[j]比pivot小，就交换下num[i]与num[j]，并i++
        for (int j = l; j <= r - 1; ++j) {
            if (nums[j] <= pivot) { // 和pivot比较
                swap(nums[i], nums[j]);
                ++i;
            }
        }
        //i已经++过了，与pivot交换下，保证pivot左边都比他小，右边比他大
        swap(nums[i], nums[r]);
        return i;
    }
    int randomized_partition(vector<int>& nums, int l, int r) {
        int i = rand() % (r - l + 1) + l;  //随机选个pivot_idx，换到最右边去
        swap(nums[r], nums[i]);
        return partition(nums, l, r);
    }
    void randomized_quicksort(vector<int>& nums, int l, int r) {
        if (l < r) {
            int pos = randomized_partition(nums, l, r);
            randomized_quicksort(nums, l, pos - 1);// 左半边递归下
            randomized_quicksort(nums, pos + 1, r);// 右半边递归下
        }
    }
public:
    vector<int> sortArray(vector<int>& nums) {
        srand((unsigned)time(NULL));
        randomized_quicksort(nums, 0, (int)nums.size() - 1);
        return nums;
    }
```

#### 堆排


#### 归并

变种：数组中的逆序对(offerNo51)：[https://daiwk.gitbook.io/int-collections/int#shu-zu-zhong-de-ni-xu-dui-offerno51](https://daiwk.gitbook.io/int-collections/int#shu-zu-zhong-de-ni-xu-dui-offerno51)

```cpp
    vector<int> tmp;
    void mergeSort(vector<int>& nums, int l, int r) {
        //递归终止条件，l>=r
        if (l >= r) return;
        //先找到中点
        int mid = (l + r) >> 1;
        //左半边递归，两边都是闭区间
        mergeSort(nums, l, mid);
        //右半边递归，两边都是闭区间
        mergeSort(nums, mid + 1, r);
        // 3个指针，左半边的起点、右半边的起点、新数组的下标
        int i = l, j = mid + 1;
        int cnt = 0;
        while (i <= mid && j <= r) { //是&&,因为有一个遍历完就比较不了了
            //把小的放进tmp，放的那半边的指针++
            if (nums[i] <= nums[j]) {
                tmp[cnt++] = nums[i++];
            }
            else {
                tmp[cnt++] = nums[j++];
            }
        }
        //剩下的搞进来
        while (i <= mid) {
            tmp[cnt++] = nums[i++];
        }
        while (j <= r) {
            tmp[cnt++] = nums[j++];
        }
        //把tmp复制回nums的l-r部分之中
        for (int i = 0; i < r - l + 1; ++i) {
            nums[i + l] = tmp[i];
        }
    }
public:
    vector<int> sortArray(vector<int>& nums) {
        tmp.resize((int)nums.size(), 0);
        mergeSort(nums, 0, (int)nums.size() - 1);
        return nums;
    }
```


### 二分小结

```cpp
    int search(vector<int>& nums, int target) {
        int low = 0, high = nums.size() - 1;
        while (low <= high) { // 小于等于
            int mid = low + (high - low) / 2; // 标准写法，背下来
            if (nums[mid] == target) {
                return mid;
            } else if (nums[mid] > target) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return -1;
    }
```

### 拓扑排序

参考[https://zhuanlan.zhihu.com/p/260112913](https://zhuanlan.zhihu.com/p/260112913)

[https://www.cnblogs.com/crab-in-the-northeast/p/topological-sort.html](https://www.cnblogs.com/crab-in-the-northeast/p/topological-sort.html)

拓扑排序是对DAG（有向无环图）上的节点进行排序，使得对于每一条有向边u->v， u都在v之前出现。简单地说，是在不破坏节点先后顺序的前提下，把DAG拉成一条链。

DAG的拓扑序可能并不唯一

#### Kahn算法(BFS)

+ 首先，先拿出所有入度为0的点排在前面，并在原图中将它们删除：

+ 这时有些点的入度减少了，于是再拿出当前所有入度为0的点放在已经排序的序列后面，然后删除：

因为是有向无环图，而且删除操作不会产生环，所以每时每刻都一定存在入度为0的点，一定可以不断进行下去，直到所有点被删除。

```src/data_structures/toposort.cpp```

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <unordered_set>
using namespace std;

void toposort(const unordered_map<string, vector<string> >& G, vector<string>& res) {
    unordered_map<string, int> in_degree_map;
    unordered_set<string> node_set;
    for (auto& it: G) {
        for (auto& node: it.second) {
            in_degree_map[node]++;
            node_set.emplace(node);
        }
        node_set.emplace(it.first);
    }
    queue<string> q;
    for (auto& it: node_set) { //无入度的节点不会在in_degree_map中
        if (in_degree_map.find(it) == in_degree_map.end()) {
            q.push(it);
        }
    }
    while (!q.empty()) {
        string val = q.front(); // 先进先出
        res.emplace_back(val);
        q.pop(); // 记得pop
        const auto& xit = G.find(val);
        if (xit != G.end()) {
            for (const auto& node: xit->second) {
                --in_degree_map[node];
                if (in_degree_map[node] == 0) {
                    q.push(node); // 入度为0，就push进队列里
                }
            }
        }
    }

}

int main() {
    // [A,B], [C,F], [F,B], [B,D], [D,E]

    unordered_map<string, vector<string> > G;
    G.emplace("A", vector<string>{"B"});
    G.emplace("C", vector<string>{"F"});
    G.emplace("F", vector<string>{"B"});
    G.emplace("B", vector<string>{"D"});
    G.emplace("E", vector<string>{"D"});
    vector<string> res;
    toposort(G, res);
    int i = 0;
    for (auto& it: res) {
        cout << it;
        if (i != res.size() - 1) {
            cout << ",";
        } else {
            cout << endl;
        }
        ++i;
    }

    return 0;
}

```


### 课程表 II

现在你总共有 numCourses 门课需要选，记为 0 到 numCourses - 1。给你一个数组 prerequisites ，其中 prerequisites[i] = [ai, bi] ，表示在选修课程 ai 前 必须 先选修 bi 。

例如，想要学习课程 0 ，你需要先完成课程 1 ，我们用一个匹配来表示：[0,1] 。
返回你为了学完所有课程所安排的学习顺序。可能会有多个正确的顺序，你只要返回 任意一种 就可以了。如果不可能完成所有课程，返回 一个空数组 。

```
输入：numCourses = 2, prerequisites = [[1,0]]
输出：[0,1]
解释：总共有 2 门课程。要学习课程 1，你需要先完成课程 0。因此，正确的课程顺序为 [0,1] 。

输入：numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
输出：[0,2,1,3]
解释：总共有 4 门课程。要学习课程 3，你应该先完成课程 1 和课程 2。并且课程 1 和课程 2 都应该排在课程 0 之后。
因此，一个正确的课程顺序是 [0,1,2,3] 。另一个正确的排序是 [0,2,1,3] 。

输入：numCourses = 1, prerequisites = []
输出：[0]
```

```cpp
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> res;
        unordered_map<int, int> in_degree_map;
        unordered_set<int> node_set;
        if (prerequisites.size() == 0) {
            for (int i = numCourses - 1; i >= 0; --i) {
                res.emplace_back(i);
            }
            return res;
        }
        for (int i = 0; i < numCourses; ++i) {
            node_set.emplace(i);
        }
        for (auto& it: prerequisites) {
            if (it.size() == 2) {
                in_degree_map[it[0]]++;
                node_set.emplace(it[1]);
                node_set.emplace(it[0]);
                // cout << it[0] << "xx" << it[1] <<endl;
            }
        }
        queue<int> q;
        for (auto& it: node_set) { //无入度的节点不会在in_degree_map中
            // cout << it << "ooo" << endl;
            if (in_degree_map.find(it) == in_degree_map.end()) {
                q.push(it);
                // cout << it << endl;
            }
        }
        while (!q.empty()) {
            int val = q.front(); // 先进先出
            res.emplace_back(val);
            q.pop(); // 记得pop
            for (const auto& edge: prerequisites) {
                int node_from = edge[1];
                int node_to = edge[0];
                if (node_from != val) {
                    continue;
                }
                --in_degree_map[node_to];
                // cout << node_to << "qq" << in_degree_map[node_to] << endl;
                if (in_degree_map[node_to] == 0) {
                    q.push(node_to); // 入度为0，就push进队列里
                }
            }
        }
        // 有环
        if (res.size() != numCourses) {
            res.clear();
            return res;
        }
        return res;
    }
```

上面的是基于string版本改的。。官方解法简单一点。。

```cpp
private:
    // 存储有向图
    vector<vector<int>> edges;
    // 存储每个节点的入度
    vector<int> indeg;
    // 存储答案
    vector<int> result;

public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        edges.resize(numCourses);
        indeg.resize(numCourses);
        for (const auto& info: prerequisites) {
            edges[info[1]].push_back(info[0]);
            ++indeg[info[0]];
        }

        queue<int> q;
        // 将所有入度为 0 的节点放入队列中
        for (int i = 0; i < numCourses; ++i) {
            if (indeg[i] == 0) {
                q.push(i);
            }
        }

        while (!q.empty()) {
            // 从队首取出一个节点
            int u = q.front();
            q.pop();
            // 放入答案中
            result.push_back(u);
            for (int v: edges[u]) {
                --indeg[v];
                // 如果相邻节点 v 的入度为 0，就可以选 v 对应的课程了
                if (indeg[v] == 0) {
                    q.push(v);
                }
            }
        }
        // 有环
        if (result.size() != numCourses) {
            return {};
        }
        return result;
    }

```

### 课程表

你这个学期必须选修 numCourses 门课程，记为 0 到 numCourses - 1 。

在选修某些课程之前需要一些先修课程。 先修课程按数组 prerequisites 给出，其中 prerequisites[i] = [ai, bi] ，表示如果要学习课程 ai 则 必须 先学习课程  bi 。

例如，先修课程对 [0, 1] 表示：想要学习课程 0 ，你需要先完成课程 1 。
请你判断是否可能完成所有课程的学习？如果可以，返回 true ；否则，返回 false 。

```
示例 1：

输入：numCourses = 2, prerequisites = [[1,0]]
输出：true
解释：总共有 2 门课程。学习课程 1 之前，你需要完成课程 0 。这是可能的。
示例 2：

输入：numCourses = 2, prerequisites = [[1,0],[0,1]]
输出：false
解释：总共有 2 门课程。学习课程 1 之前，你需要先完成​课程 0 ；并且学习课程 0 之前，你还应先完成课程 1 。这是不可能的。

```

其实和上面那题完全一样，只是改成了判断是否有环，那就是判断res的长度和节点数是否一样多就行

```cpp
private:
    // 存储有向图
    vector<vector<int>> edges;
    // 存储每个节点的入度
    vector<int> indeg;
    // 存储答案
    vector<int> result;
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        edges.resize(numCourses);
        indeg.resize(numCourses);
        for (const auto& info: prerequisites) {
            edges[info[1]].push_back(info[0]);
            ++indeg[info[0]];
        }

        queue<int> q;
        // 将所有入度为 0 的节点放入队列中
        for (int i = 0; i < numCourses; ++i) {
            if (indeg[i] == 0) {
                q.push(i);
            }
        }

        while (!q.empty()) {
            // 从队首取出一个节点
            int u = q.front();
            q.pop();
            // 放入答案中
            result.push_back(u);
            for (int v: edges[u]) {
                --indeg[v];
                // 如果相邻节点 v 的入度为 0，就可以选 v 对应的课程了
                if (indeg[v] == 0) {
                    q.push(v);
                }
            }
        }
        return result.size() == numCourses;
    }
```

### 合并两个有序数组

给定两个有序整数数组 nums1 和 nums2，将 nums2 合并到 nums1 中，使得 num1 成为一个有序数组。

说明:

+ 初始化 nums1 和 nums2 的元素数量分别为 m 和 n。
+ 你可以假设 nums1 有足够的空间（空间大小大于或等于 m + n）来保存 nums2 中的元素。

示例:

```
输入:
nums1 = [1,2,3,0,0,0], m = 3
nums2 = [2,5,6],       n = 3

输出: [1,2,2,3,5,6]
```

**解答：**

**归并排序**

提示中已经给出，假设array1有足够的空间了，于是我们不需要额外构造一个数组，并且可以**从后面**不断地比较元素进行合并。

+ 比较array2与array1中**最后面**的那个元素，把最大的插入第m+n位
+ 改变数组的索引，再次进行上面的比较，把最大的元素插入到array1中的第m+n-1位。
+ 循环一直到结束。循环结束条件：当index1或index2有一个小于0时，此时就可以结束循环了。如果index2小于0，说明目的达到了。如果index1小于0，就把array2中剩下的前面的元素都复制到array1中去就行。

```cpp
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int j = n - 1;
        int i = m - 1;
        while (j >= 0) {
            if (i < 0) {
                // 如果i数组遍历完了，要把j数据剩下的全部拷过来,记住是<j+1
                for(int k = 0; k < j + 1; ++k) {
                    nums1[k] = nums2[k];
                }
                break;
            }
            if (nums2[j] > nums1[i]) {
                // 留大的下来，留谁的就谁的指针--
                // 注意是i + j + 1
                nums1[i + j + 1] = nums2[j];
                j--;
            } else {
                nums1[i + j + 1] = nums1[i];
                i--;
            }
        }
    }
};
```

### 颜色分类

给定一个包含红色、白色和蓝色、共 n 个元素的数组 nums ，原地对它们进行排序，使得相同颜色的元素相邻，并按照红色、白色、蓝色顺序排列。

我们使用整数 0、 1 和 2 分别表示红色、白色和蓝色。

必须在不使用库的sort函数的情况下解决这个问题。


即荷兰国旗问题 数组里有0 1 2，要求相同颜色的相邻 单指针


```cpp
    void sortColors(vector<int>& nums) {
        int n = nums.size();
        int ptr = 0;
        // 遍历两次，第一遍把0交换到前面去，第二遍把1交换到0之后
        // 用指针ptr标记最后一个0的下一位，第二遍从ptr开始
        for (int i = 0; i < n; ++i) {
            if (nums[i] == 0) {
                swap(nums[i], nums[ptr]);
                ++ptr;
            }
        }
        for (int i = ptr; i < n; ++i) {
            if (nums[i] == 1) {
                swap(nums[i], nums[ptr]);
                ++ptr;
            }
        }
    }
```

### 前k个高频元素

给你一个整数数组 nums 和一个整数 k ，请你返回其中出现频率前 k 高的元素。你可以按 任意顺序 返回答案。
多存个map，堆里存的是个pair

```cpp
    struct MyCmp {
        bool operator()(pair<int, int>& a, pair<int, int>& b) {
            return a.second > b.second;
        }
    };
    vector<int> topKFrequent(vector<int>& nums, int k) {
        // 先遍历一遍，map存<k,cnt>，然后遍历map，用个小顶堆
        // 如果堆的元素个数小于 k，就可以直接插入堆中。
        // 如果堆的元素个数等于 k，则检查堆顶与当前出现次数的大小。
        //   如果堆顶更大，说明至少有 k 个数字的出现次数比当前值大，故舍弃当前值；
        //   否则，就弹出堆顶，并将当前值插入堆中。

        // c++的堆是priority_queue
        unordered_map<int, int> word_count;
        for (auto& v: nums) {
            word_count[v]++;
        }
        // pop的是优先级最高的元素，top也是优先级最高的
        // priorty_queue<int, vector<int>, cmp> 这是定义方式，一定要有个vec
        priority_queue<pair<int, int>, vector<pair<int, int> >, MyCmp> q;
        for (auto& [num, cnt]: word_count) {
            if (q.size() < k) {
                q.emplace(num, cnt);
            } else {
                if (q.top().second < cnt) {
                    q.pop();
                    q.emplace(num, cnt);
                }
            }
        }
        vector<int> res;
        while (!q.empty()){
            res.emplace_back(q.top().first);
            q.pop();
        }
        return res;
    }
```

### 数组中的第k个最大元素

给定整数数组 nums 和整数 k，请返回数组中第 k 个最大的元素。

请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。


堆顶就是了

```cpp
    int findKthLargest(vector<int>& nums, int k) {
        //小顶堆，堆顶就是要的
        struct MyCmp {
            bool operator()(int a, int b) {
                return a > b;
            }
        };
        priority_queue<int, vector<int>, MyCmp> q;
        for (auto& i: nums) {
            if (q.size() < k) {
                q.emplace(i);
            } else {
                if (i > q.top()) {
                    q.pop();
                    q.emplace(i);
                }
            }
        }
        return q.top();
    }
```

### 寻找峰值

峰值元素是指其值严格大于左右相邻值的元素。

给你一个整数数组 nums，找到峰值元素并返回其索引。数组可能包含多个峰值，在这种情况下，返回 任何一个峰值 所在位置即可。

你可以假设 nums[-1] = nums[n] = -∞ 。

你必须实现时间复杂度为 O(log n) 的算法来解决此问题。


二分，类似旋转数组，如果mid不是符合条件的，那看看是在上升还是在下降，如果是在上升，那就看右边区间，如果是下降，那看左边。

```cpp
    // 可以搞成匿名函数
    // pair<int, int> get(int i, int n, vector<int> & nums) {
    //     // 方便处理nums[-1]和nums[n]的边界情况
    //     if (i == -1 || i == n) {
    //         return {0, 0};
    //     }
    //     return {1, nums[i]};
    //     //保证能取到的比越界的大，都能取到的时候，用实际的数比较
    // }
    int findPeakElement(vector<int>& nums) {
        // 二分，类似旋转数组，如果mid不是符合条件的，那看看是在上升还是在下降，
        // 如果是在上升，那就看右边区间，如果是下降，那看左边。
        int left = 0, right = nums.size() - 1;
        int n = nums.size();
        auto get = [&](int i) -> pair<int, int> {
            // 方便处理nums[-1]和nums[n]的边界情况
            if (i == -1 || i == n) {
                return {0, 0};
            }
            return {1, nums[i]};
            //保证能取到的比越界的大，都能取到的时候，用实际的数比较
        };
        while (left <= right) {
            int mid = left + (right - left) / 2; //标准mid写法
            if (get(mid - 1) < get(mid) && get(mid) > get(mid + 1)) {
                return mid;
            }
            if (get(mid) < get(mid + 1)) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return -1;
    }
```

### 在排序数组中查找元素的第一个和最后一个位置

给定一个按照升序排列的整数数组 nums，和一个目标值 target。找出给定目标值在数组中的开始位置和结束位置。

如果数组中不存在目标值 target，返回 [-1, -1]。

进阶：

你可以设计并实现时间复杂度为 O(log n) 的算法解决此问题吗？


```cpp
public:
    int binary_search(vector<int>& nums, int target, bool lower) {
        // ans初始化为n！！！，因为外面要-1，对于[1]且target=1的case，会有问题
        int left = 0, right = nums.size() - 1, ans = nums.size(); 
        //不要急着return，要找到边界
        while (left <= right) {
            int mid = left + (right - left) / 2;
            // lower = true，想找左边界，只要nums[mid] >= target就可能可以，只有<target的时候才停
            // lower = false，想找右边第一个>target的
            // 都是找左区间
            if (nums[mid] > target || (lower && nums[mid] >= target)) {
                ans = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return ans;
    }
    vector<int> searchRange(vector<int>& nums, int target) {
        // 其实要找的就是第一个=target的位置，和第一个>target的位置-1
        int left_idx = binary_search(nums, target, true);
        int right_idx = binary_search(nums, target, false) - 1;
        if (left_idx <= right_idx && right_idx < nums.size() 
            && left_idx >=0 && nums[left_idx] == target && nums[right_idx] == target) {
            return vector<int>{left_idx, right_idx};
        }
        return vector<int>{-1, -1};

    }
```

### 合并区间

以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] = [starti, endi] 。请你合并所有重叠的区间，并返回 一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间 。

```cpp
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        // 先排序，然后第一个区间扔进去，遍历下一个的时候，
        // 看看和前面的最后一个区间有没交集，如果无交集（当前左>已有右），那就扔到最后
        // 如果有交集，那就取这两个区间max的右端点
        if (intervals.size() == 0) {
            return {};
        }
        sort(intervals.begin(), intervals.end());
        vector<vector<int> > merged;
        for (int i = 0; i < intervals.size(); ++i) {
            int left = intervals[i][0], right = intervals[i][1];
            if (merged.size() == 0 || left > merged.back()[1] ) {
                merged.push_back({left, right});
            } else {
                merged.back()[1] = max(merged.back()[1], right);
            }
        }
        return merged;
    }
```

### 搜索旋转排序数组

整数数组 nums 按升序排列，数组中的值 互不相同 。

在传递给函数之前，nums 在预先未知的某个下标 k（0 <= k < nums.length）上进行了 旋转，使数组变为 [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]]（下标 从 0 开始 计数）。例如， [0,1,2,4,5,6,7] 在下标 3 处经旋转后可能变为 [4,5,6,7,0,1,2] 。

给你 旋转后 的数组 nums 和一个整数 target ，如果 nums 中存在这个目标值 target ，则返回它的下标，否则返回 -1 。


```cpp
    int search(vector<int>& nums, int target) {
        // 局部有序，二分
        int n = nums.size();
        if (n == 0) {
            return -1;
        }
        if (n == 1) {
            return nums[0] == target? 0: -1;
        }
        int left = 0, right = n - 1;
        while (left <= right) {
            int mid = left + (right -left) / 2;
            if (nums[mid] == target) {
                return mid;
            }
            // 看下mid在哪个区间里，因为有两个上升的区间，和nums[0]比就行
            if (nums[0] <= nums[mid]) {
                // mid在第一个上升区间里
                if (nums[0] <= target && target < nums[mid]) {
                    // target也在这个区间里
                    right = mid -1;
                } else {
                    left = mid + 1;
                }
            } else {
                if (nums[mid] < target && target <= nums[n - 1]) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }
        return -1;
    }
```

### 搜索二维矩阵 II

编写一个高效的算法来搜索 m x n 矩阵 matrix 中的一个目标值 target 。该矩阵具有以下特性：

每行的元素从左到右升序排列。
每列的元素从上到下升序排列。

```cpp
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        // 右上角开始，保证只有一个搜索方向，要么变大要么变小，z字形
        int m = matrix.size(), n = matrix[0].size();
        int x = 0, y = n - 1;
        while (x < m && y >= 0) {
            if (matrix[x][y] ==  target) {
                return true;
            }
            if (matrix[x][y] > target) {
                --y;
            } else {
                ++x;
            }
        }
        return false;
    }
```

## dp

### 跳跃游戏

给定一个非负整数数组 nums ，你最初位于数组的 第一个下标 。

数组中的每个元素代表你在该位置可以跳跃的最大长度。

判断你是否能够到达最后一个下标。


```cpp
    bool canJump(vector<int>& nums) {
        // 贪心
        // 对于每个位置x，实时维护最远可到达的位置x+nums[x]，
        // 如果这个位置x在最远可到达位置内，那么可以从起点经过若干次跳跃到达
        // 在遍历的过程中，如果最远可到达位置>=数组最后一个位置 ，就可以return True
        int n = nums.size();
        int most_right = 0;
        for (int i = 0; i < n; ++i) {
             // 如果i>most_right，那这个点永远不可达，所以最后是return false
            if (i <= most_right) {
                most_right = max(most_right, i + nums[i]);
                if (most_right >= n - 1) {
                    return true;
                }
            }
        }
        return false;
    }
```

### 不同路径

一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为 “Start” ）。

机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为 “Finish” ）。

问总共有多少条不同的路径？

简单二维dp，注意边界条件

```cpp
    int uniquePaths(int m, int n) {
        // f(i,j)表示从左上角走到(i,j)的路径数量，
        // 这个点只可能是从左边或者上面走过来的，所以
        // f(i,j) = f(i-1,j) + f(i, j-1)
        // 对于第0行和第0列，f(i,0)=1，f(0,j)=1，因为只有直着能走到
        // f(0,0) = 1
        vector<vector<int> > f(m, vector<int>(n));
        for (int i = 0; i < m; ++i) {
            f[i][0] = 1;
        }
        for (int j = 0; j < n; ++j) {
            f[0][j] = 1;
        }
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j <n; ++j) {
                f[i][j] = f[i - 1][j] + f[i][j - 1];
            }
        }
        return f[m - 1][n - 1];
    }
```

### 零钱兑换

给你一个整数数组 coins ，表示不同面额的硬币；以及一个整数 amount ，表示总金额。

计算并返回可以凑成总金额所需的 最少的硬币个数 。如果没有任何一种硬币组合能组成总金额，返回 -1 。

你可以认为每种硬币的数量是无限的。


```cpp
    int coinChange(vector<int>& coins, int amount) {
        // dp[i]：组成金额i需要的最少硬币数
        // dp[i] = min(dp[i-c[j]) + 1, j = 0,...,n-1，
        // ！！！注意，是两项,dp[i]和dp[i - coins[j]]+ 1
        // dp[i] = min(dp[i], dp[i - coins[j]]+ 1);
        // c[j]是第j个面额，+1表示选择这个面额，那i-c[j]就是剩下的面额了
        // ！！需要判断凑不出的情况：把dp初始化为amount + 1，如果凑不出就不更新，
        // 如果最后还是amount +1那就是凑不出，当然也可以是amount+999
        int xmax = amount + 1;
        // 因为最后一个下标要是amount，所以大小是amount + 1
        vector<int> dp(amount + 1, xmax);
        dp[0] = 0;
        for(int i = 1; i <= amount; ++i) {
            for (int j = 0; j < coins.size(); ++j) {
                // 遍历每种面额
                if (coins[j] <= i) {
                    dp[i] = min(dp[i], dp[i - coins[j]]+ 1);
                }
            }
        }
        return dp[amount] > amount? -1: dp[amount];
    }
```

### 最长递增子序列

给你一个整数数组 nums ，找到其中最长严格递增子序列的长度。

子序列 是由数组派生而来的序列，删除（或不删除）数组中的元素而不改变其余元素的顺序。例如，[3,6,2,7] 是数组 [0,3,1,6,2,2,7] 的子序列。


```cpp
    int lengthOfLIS(vector<int>& nums) {
        // 不要求连续，比如[3,6,2,7]是[0,3,1,6,2,2,7]的子序列
        // dp[i]：以第i个数字结尾（选了nums[i]）的最长递增子序列的长度
        // dp[i] = max(dp[j]) +1, 0<=j<i，nums[j] < nums[i]，这样才能递增
        // 相当于前面i-1个数里，有一个和i是递增关系，那就可以把i选了
        // 要么就直接dp[i]，这两个取max
        // 最终的结果是max(dp[i])
        int n = nums.size();
        if (n == 0) {
            return 0;
        }
        vector<int> dp(n, 0);
        int res = 0;
        for (int i = 0; i < n; ++i) {
            dp[i] = 1;
            for (int j = 0; j < i; ++j) {
                if (nums[j] < nums[i]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            res = max(res, dp[i]);
        }
        return res;
    }
```

### 爬楼梯

假设你正在爬楼梯。需要 n 阶你才能到达楼顶。

每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？

```cpp
    int climbStairs(int n) {
        // 斐波那契
        int p= 0, q = 0, r = 1;
        // 注意，这里是从1开始，相当于把上面那三个数往右平移一格
        // i<=n，注意有等号
        for (int i = 1; i <= n; ++i) {
            p = q;
            q = r;
            r = p + q;
        }
        return r;
    }
```

### 接雨水

给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。

dp，存left_max和right_max，然后min(left_max, right_max) - height

```cpp
    int trap(vector<int>& height) {
        int n = height.size();
        if (n == 0) {
            return 0;
        }
        vector<int> left_max(n, 0), right_max(n, 0);
        for (int i = 0; i < n; ++i) {
            if (i > 0) {
                left_max[i] = max(height[i], left_max[i - 1]); // 注意，这里是left_max[i-1]
            } else {
                left_max[i] = height[i];
            }
        }
        for (int i = n - 1; i >= 0; --i) {
            if (i < n - 1) {
                right_max[i] = max(height[i], right_max[i + 1]);// 注意，这里是right_max[i+1]
            } else {
                right_max[i] = height[i];
            }
        }
        int res = 0;
        for (int i = 0; i < n; ++i) {
            res += min(left_max[i], right_max[i]) - height[i];
        }
        return res;
    }
```

### 跳跃游戏 II

给你一个非负整数数组 nums ，你最初位于数组的第一个位置。

数组中的每个元素代表你在该位置可以跳跃的最大长度。

你的目标是使用最少的跳跃次数到达数组的最后一个位置。

假设你总是可以到达数组的最后一个位置。

返回到达最后一个位置的最小跳跃数。

```
输入: nums = [2,3,1,1,4]
输出: 2
解释: 跳到最后一个位置的最小跳跃数是 2。
     从下标为 0 跳到下标为 1 的位置，跳 1 步，然后跳 3 步到达数组的最后一个位置。
```

对于数组 [2,3,1,2,4,2,3]

![](./assets/jump.png)

**解法：**

这个点所有可能到达的位置中，选下一步能跳得最远的那个

在遍历数组时，我们不访问最后一个元素，这是因为在访问最后一个元素之前，我们的边界一定大于等于最后一个位置，否则就无法跳到最后一个位置了。

如果访问最后一个元素，在边界正好为最后一个位置的情况下，我们会增加一次「不必要的跳跃次数」，因此我们不必访问最后一个元素。

```cpp
    int jump(vector<int>& nums) 
    {
        // 目前能跳到的最远位置，要么是i+nums[i]，要么是原来的max_far
        // max_far > i+nums[i]的情况就是比如i=3，nums[3]=1，但原来可以跳到10。
        int max_far = 0;
        int step = 0;   // 跳跃次数
        // 上次跳跃可达范围右边界（下次的最右起跳点）
        int end = 0; 
        for (int i = 0; i < nums.size() - 1; ++i) {
            max_far = max(max_far, i + nums[i]);
            if (end == i) { // 到了这个点，开始跳一步
                end = max_far; // 更新end为下一个最远的地方
                ++step;
            }
        }
        return step;
    }
```

### 最大子数组和

给你一个整数数组 nums ，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。

子数组 是数组中的一个连续部分。

```
输入：nums = [-2,1,-3,4,-1,2,1,-5,4]
输出：6
解释：连续子数组 [4,-1,2,1] 的和最大，为 6 。
```

f(i)表示以第i个数结尾的连续子数组最大和，那么求的就是i=0,...,n-1的max f(i)

f(i) = max(f(i-1) + nums[i], nums[i])

如果加上这个数能变得更大，那就加上；**如果不行，那这个数就是新的起点**

而只和f(i-1)有关的话，且最后要的是max，那么可以只用一个变量，不需要数组

```cpp
    int maxSubArray(vector<int>& nums) {
        // f(i)表示以第i个数结尾的连续子数组最大和，那么求的就是i=0,...,n-1的max f(i)
        // f(i) = max(f(i-1) + nums[i], nums[i])
        // 如果加上这个数能变得更大，那就加上；如果不行，那这个数就是新的起点
        int pre = 0;
        int max_res = INT_MIN; // 初始化极小值，或者nums[0]
        for (int i = 0; i < nums.size(); ++i) {
            pre = max(pre + nums[i], nums[i]);
            max_res = max(max_res, pre);
        }
        return max_res;
    }
```

### 买卖股票的最佳时机

给定一个数组，它的第 i 个元素是一支给定股票第 i 天的价格。

如果你最多只允许完成一笔交易（即买入和卖出一支股票），设计一个算法来计算你所能获取的最大利润。

注意你不能在买入股票前卖出股票。

```
示例 1:

输入: [7,1,5,3,6,4]
输出: 5
解释: 在第 2 天（股票价格 = 1）的时候买入，在第 5 天（股票价格 = 6）的时候卖出，最大利润 = 6-1 = 5 。
     注意利润不能是 7-1 = 6, 因为卖出价格需要大于买入价格。
示例 2:

输入: [7,6,4,3,1]
输出: 0
解释: 在这种情况下, 没有交易完成, 所以最大利润为 0。
```

**解答：**

我们需要找到**最小的谷之后的最大的峰**。 我们可以维持两个变量

+ minprice ：**迄今为止**所得到的**最小的谷值**。初始化为int_max，如果当前价格比它小，那就更新它为当前价格
+ maxprofit，**迄今为止**所得到的**最大的利润**（卖出价格与最低价格之间的最大差值）。如果当前价格与minprice的差比它大，那就更新它

```cpp
    int maxProfit(vector<int>& prices) {
        // 找到最小的谷之后的最大的峰。 我们可以维持两个变量
        // minprice ：迄今为止所得到的最小的谷值。初始化为int_max，如果当前价格比它小，那就更新它为当前价格
        // maxprofit，迄今为止所得到的最大的利润（卖出价格与最低价格之间的最大差值）。如果当前价格与minprice的差比它大，那就更新它
        int minprice = INT_MAX;
        int max_profit = 0;
        for (int i = 0; i < prices.size(); ++i) {
            if (prices[i] < minprice) {
                // 不卖
                minprice = prices[i];
            } else {
                // 卖或者不卖的最大profit
                max_profit = max(max_profit, prices[i] - minprice);
            }
        }
        return max_profit;
    }
```

### 正则表达式匹配

```
给你一个字符串 s 和一个字符规律 p，请你来实现一个支持 '.' 和 '*' 的正则表达式匹配。

'.' 匹配任意单个字符
'*' 匹配零个或多个前面的那一个元素
所谓匹配，是要涵盖 整个 字符串 s的，而不是部分字符串。

保证每次出现字符 * 时，前面都匹配到有效的字符===> '*'不会是第一个字符！！

输入：s = "ab", p = ".*"
输出：true
解释：".*" 表示可匹配零个或多个（'*'）任意字符（'.'）。

```

f[i][j]表示字符串s的前i个字符与正则p的前j个字符是否match（完全一致）

+ 如果p[j]是字母，如果s[i]与p[j]不一样，那肯定不行，反之，这位ok，就看f[i-1][j-1]：

$$
f[i][j]= \begin{cases}f[i-1][j-1], & s[i]=p[j] \\ \text { false, } & s[i] \neq p[j]\end{cases}
$$

+ 如果p[j]是'*'，那么就可以对p[j-1]匹配n次，也就是说

    + 如果p[j-1]==s[i]，那么，就算我把s[i]给删了，这个pattern(即p[j-1]p[j])还可以继续用：

f[i][j] = f[i-1][j]

而与此同时，我把这个pattern扔了也行，因为已经匹配至少一次了：

f[i][j] = f[i][j-2]

所以，f[i][j] =  f[i-1][j] or f[i][j-2], p[j-1] == s[i]

    + 如果p[j-1]!=s[i]，那么这个组合就扔了

f[i][j] = f[i][j-2], p[j-1] != s[i]

所以，

$$
f[i][j]= \begin{cases}f[i-1][j] \text { or } f[i][j-2], & s[i]=p[j-1] \\ f[i][j-2], & s[i] \neq p[j-1]\end{cases}
$$

综合起来就是

$$
f[i][j]= \begin{cases}\text { if }\left(p[j] \neq{ }'*'\right)= \begin{cases}f[i-1][j-1], & \text { matches }(s[i], p[j]) \\ \text { false, } & \text { otherwise }\end{cases} \\ \text { otherwise }= \begin{cases}f[i-1][j] \text { or } f[i][j-2], & \text { matches }(s[i], p[j-1]) \\ f[i][j-2], & \text { otherwise }\end{cases} \end{cases}
$$

其中的matches只有当y是.或者x=y时才会匹配

边界f[0][0] = 1，因为两个空串是匹配的。

注意：

当s为空，```p=a*```，这样这样是可以匹配的。因为可以决定前面的那个a一个都不选，带着它一起消失。

```cpp
    bool isMatch(string s, string p) {
        int m = s.size();
        int n = p.size();

        // 因为f是n+1 * m+1，所以这里其实是比较 s[i-1]和p[j-1]
        // [&]：父作用域的按引用传，其实[=]也行，父作用域的按值传
        auto matches = [=](int i, int j) {
            if (i == 0) {
                return false; // 不太懂这个
            }
            if (p[j - 1] == '.') {
                return true;
            }
            return s[i - 1] == p[j - 1];
        };

        vector<vector<int>> f(m + 1, vector<int>(n + 1));
        f[0][0] = true;
        for (int i = 0; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (p[j - 1] != '*')  {
                    if (matches(i, j)) { //比较的是i-1和j-1
                        f[i][j] |= f[i - 1][j - 1];
                    }
                } else { 
                    f[i][j] |= f[i][j - 2];
                    if (matches(i, j - 1)) { // 比较的是i-1和j-2
                        f[i][j] |= f[i - 1][j];
                    }
                }
            }
        }
        return f[m][n];
    }
```

### 二叉树中的最大路径和

路径 被定义为一条从树中任意节点出发，沿父节点-子节点连接，达到任意节点的序列。同一个节点在一条路径序列中 至多出现一次 。该路径 至少包含一个 节点，且不一定经过根节点。

路径和 是路径中各节点值的总和。

给你一个二叉树的根节点 root ，返回其 最大路径和 。

相当于**不能走回头路**

递归。。其实不是dp

max_gain(root)：计算二叉树中的一个节点的最大贡献值，即在**以该节点为根节点的子树中**寻找**以该节点为起点**的一条路径，使得该**路径上的节点值之和最大**。

叶节点的最大贡献值等于节点值

计算完叶子后，中间节点的```max_gain=他的值+max(左孩子max_gain, 右孩子max_gain)```

最大路径和：对于二叉树中的一个节点，该节点的最大路径和取决于**该节点的值**与该节点的**左右子节点的最大贡献值**，如果子节点的最大贡献值为正，则计入该节点的最大路径和，否则不计入该节点的最大路径和。

然后维护一个全局变量，只保留最终的max，注意初始化为INT_MIN

```cpp
    int max_sum = INT_MIN; //需要初始化为INT_MIN，因为如果整棵树全为负，max_sum得小于0
    int max_gain(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        // 只有在最大贡献值大于 0 时，才会选取对应子节点
        int left_gain = max(max_gain(root->left), 0);
        int right_gain = max(max_gain(root->right), 0);
        // 节点的最大路径和取决于该节点的值与该节点的左右子节点的最大贡献值, 这里是加！！，因为可以左边走上来，再往右边走下去
        int cur_max_gain = root->val + left_gain + right_gain;
        max_sum = max(max_sum, cur_max_gain);
        // 这里是max，因为定义的时候，是以root为起点，不能回头，所以只有一个方向 
        return root->val + max(left_gain, right_gain);
    }
    int maxPathSum(TreeNode* root) {
        max_gain(root);
        return max_sum;
    }
```

### 编辑距离

给你两个单词 word1 和 word2， 请返回将 word1 转换成 word2 所使用的最少操作数  。

你可以对一个单词进行如下三种操作：
```
插入一个字符
删除一个字符
替换一个字符
```

**解答：**

本质不同的操作实际上只有三种：

+ 在单词 A 中插入一个字符；（等价于B中删掉一个字符）
+ 在单词 B 中插入一个字符；（等价于A中删掉一个字符）
+ 修改单词 A 的一个字符。（等价于A中修改一个字符）

D[i][j] 表示 A 的前 i 个字母和 B 的前 j 个字母之间的编辑距离。

若 A 和 B 的最后一个字母相同：

D[i][j] = min(D[i-1][j]+1, D[i][j-1]+1, D[i-1][j-1])

若 A 和 B 的最后一个字母不同：

D[i][j] = min(D[i-1][j]+1, D[i][j-1]+1, D[i-1][j-1]+1)


二者差别就是D[i-1][j-1]，A[i]!=B[j]时，需要+1

对于边界情况，一个空串和一个非空串的编辑距离为 D[i][0] = i 和 D[0][j] = j，D[i][0] 相当于对 word1 执行 i 次删除操作，D[0][j] 相当于对 word1执行 j 次插入操作。


```cpp
    int minDistance(string word1, string word2) {
        int n = word1.length();
        int m = word2.length();
        vector<vector<int> > D(n+1, vector<int>(m+1));
        for (int i = 0; i < n + 1; ++i) {
            D[i][0] = i;
        }
        for (int j = 0; j < m + 1; ++j) {
            D[0][j] = j;
        }
        for (int i = 1; i < n + 1; ++i) {
            for (int j = 1; j < m + 1; ++j) {
                int a = D[i][j - 1] + 1;
                int b = D[i - 1][j] + 1;
                int c = D[i - 1][j - 1];
                if (word1[i - 1] != word2[j - 1]) { // 注意这里要-1
                    c += 1;
                }
                D[i][j] = min(a, min(b, c));
            }
        }
        return D[n][m];
    }
```

### 最大正方形

在一个由 '0' 和 '1' 组成的二维矩阵内，找到只包含 '1' 的最大正方形，并返回其面积。

dp(i,j) 表示以 (i,j) 为右下角，且只包含 1 的正方形的边长最大值

```cpp
    int maximalSquare(vector<vector<char>>& matrix) {
        int m = matrix.size();// row
        if (m < 1) return 0;
        int n = matrix[0].size(); // col
        int maxnum = 0;

        vector<vector<int> > dp(m, vector<int>(n));
        
        for (int i = 0; i < m; ++i) {
            if (matrix[i][0] == '1') {
                dp[i][0] = 1;
                maxnum = 1;
            }
        }
        for (int j = 0; j < n; ++j) {
            if (matrix[0][j] == '1') {
                dp[0][j] = 1;
                maxnum = 1;
            }
        }
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (matrix[i][j] == '1') {
                    dp[i][j] = min(min(dp[i - 1][j], dp[i - 1][j - 1]), dp[i][j - 1]) + 1;
                    maxnum = max(maxnum, dp[i][j]);
                }
            }
        }
        return maxnum * maxnum;
    }
```

### 统计全为 1 的正方形子矩阵

给你一个 m * n 的矩阵，矩阵中的元素不是 0 就是 1，请你统计并返回其中完全由 1 组成的 正方形 子矩阵的个数。

和上面那题几乎一样，只是最终求值不太一样

dp(i,j) 表示以 (i,j) 为右下角，且只包含 1 的正方形的边长最大值

而dp(i,j)恰好也表示以(i,j)为右下角的正方形有多少个，依次是边长为1,2,3,...,dp(i,j)的正方形

```cpp
    int countSquares(vector<vector<int>>& matrix) {
        int m = matrix.size();// row
        if (m < 1) return 0;
        int n = matrix[0].size(); // col
        int maxnum = 0;

        vector<vector<int> > dp(m, vector<int>(n));
        
        for (int i = 0; i < m; ++i) {
            if (matrix[i][0] == 1) {
                dp[i][0] = 1;
                maxnum += 1;
            }
        }
        for (int j = 0; j < n; ++j) {
            if (matrix[0][j] == 1) {
                dp[0][j] = 1;
                // 如果不判断，dp[0][0]就算了两次。。
                if (j != 0) {
                    maxnum += 1;
                }
            }
        }
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (matrix[i][j] == 1) {
                    dp[i][j] = min(min(dp[i - 1][j], dp[i - 1][j - 1]), dp[i][j - 1]) + 1; 
                }
                //cout << dp[i][j] << " " << i << " " << j << endl;
                maxnum += dp[i][j];
            }
        }
        return maxnum;
    }
```

### 乘积最大子数组

给你一个整数数组 nums ，请你找出数组中乘积最大的非空连续子数组（该子数组中至少包含一个数字），并返回该子数组所对应的乘积。

测试用例的答案是一个 32-位 整数。

子数组 是数组的连续子序列。


![](assets/maxmul.jpg)

```cpp
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        int min_f = nums[0], max_f = nums[0];
        int res = nums[0];
        for (int i = 1; i < n; ++i) {
            int cur = nums[i];
            int mx = max_f, mn = min_f; //必须搞个临时变量，因为改完max_f后，算min_f的时候还要用原来的max_f
            max_f = max(max(mn * cur, mx * cur), cur);
            min_f = min(min(mn * cur, mx * cur), cur);
            res = max(res, max_f);
        }
        return res;
    }
```

### 分发糖果

n 个孩子站成一排。给你一个整数数组 ratings 表示每个孩子的评分。

你需要按照以下要求，给这些孩子分发糖果：

```
每个孩子至少分配到 1 个糖果。
相邻两个孩子评分更高的孩子会获得更多的糖果。
请你给每个孩子分发糖果，计算并返回需要准备的 最少糖果数目 。
```

```
示例 1：

输入：ratings = [1,0,2]
输出：5
解释：你可以分别给第一个、第二个、第三个孩子分发 2、1、2 颗糖果。
示例 2：

输入：ratings = [1,2,2]
输出：4
解释：你可以分别给第一个、第二个、第三个孩子分发 1、2、1 颗糖果。
     第三个孩子只得到 1 颗糖果，这满足题面中的两个条件。

```

**解法**

糖果总是尽量少给，且从 1 开始累计，每次要么比相邻的同学多给一个，要么重新置为 1。

+ 如果当前同学比左边同学rating高，那说明他在最近的递增序列中，给他pre+1
+ 如果两个人相等，直接给他1个就行，如示例2
+ 否则属于一个递减序列，
  + 直接先给他1个，然后假设下一个还是递减的，那就再+2，下下个还是那就再+3，其实就是dec+=1, x+=dec;下一个继续dec+=1, x+=dec
  + 如果当前的递减序列长度和上一个递增序列等长时，需要把最近的递增序列的最后一个同学也并进递减序列中。也就是用两个变量，分别记录最近一个上升的长度inc与最近一个下降的长度dec，如果相等，dec++。注意，这个时候要把pre搞成1，因为下次要上升的时候，是递减的最后一个位置，这个人只给他一个糖果

```cpp
    int candy(vector<int>& ratings) {
        // 如果当前同学比左边同学rating高，那说明他在最近的递增序列中，给他pre+1
        // 如果两个人相等，直接给他1个就行，如示例2
        // 否则属于一个递减序列，
        //    直接先给他1个，然后假设下一个还是递减的，那就再+2，下下个还是那就再+3，其实就是dec+=1, x+=dec;下一个继续dec+=1, x+=dec
        //    如果当前的递减序列长度和上一个递增序列等长时，需要把最近的递增序列的最后一个同学也并进递减序列中。也就是用两个变量，分别记录最近一个上升的长度inc与最近一个下降的长度dec，如果相等，dec++。注意，这个时候要把pre搞成1，因为下次要上升的时候，是递减的最后一个位置，这个人只给他一个糖果
        int n = ratings.size();
        int ret = 1;
        int inc = 1, dec = 0, pre = 1;
        for (int i = 1; i < n; ++i) {
            if (ratings[i] >=  ratings[i - 1]) {
                dec = 0;
                pre = ratings[i] == ratings[i - 1]? 1: pre + 1;
                ret += pre;
                inc = pre;// 肯定是从1开始加上来的，所以inc=pre
            } else {
                dec++;
                if (dec == inc) {
                    dec++;
                }
                ret += dec;
                pre = 1;
            }
        }
        return ret;
    }
```


## 设计

### 二叉树的序列化与反序列化

序列化是将一个数据结构或者对象转换为连续的比特位的操作，进而可以将转换后的数据存储在一个文件或者内存中，同时也可以通过网络传输到另一个计算机环境，采取相反方式重构得到原数据。

请设计一个算法来实现二叉树的序列化与反序列化。这里不限定你的序列 / 反序列化算法执行逻辑，你只需要保证一个二叉树可以被序列化为一个字符串并且将这个字符串反序列化为原始的树结构。

提示: 输入输出格式与 LeetCode 目前使用的方式一致，详情请参阅 LeetCode 序列化二叉树的格式。你并非必须采取这种方式，你也可以采用其他的方法解决这个问题。


```cpp
class Codec {
public:

    // 前序遍历，到叶子的时候，左右儿子均搞成None
    void rser(TreeNode* root, string& str) {
        if (root == nullptr) {
            str += "None,";
        } else {
            str += to_string(root->val) + ",";
            rser(root->left, str);
            rser(root->right, str);
            //cout << str << endl;
        }
    }
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string res;
        rser(root, res);
        return res;
    }

    TreeNode* rde(list<string>& data_vec) {
        // 如果当前的元素为 None，则当前为空树
        // 否则先解析这棵树的左子树，再解析它的右子树
        // list的front是第一个元素的值，begin是迭代器
        if (data_vec.front() == "None") {
            data_vec.erase(data_vec.begin());
            return nullptr;
        }
        TreeNode* root = new TreeNode(stoi(data_vec.front()));
        data_vec.erase(data_vec.begin());
        root->left = rde(data_vec);
        root->right = rde(data_vec);
        return root;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        list<string> data_vec;
        string str;
        // 人肉实现下split
        for (auto &ch: data) {
            if (ch == ',') {
                data_vec.push_back(str);
                str.clear();
            } else {
                str.push_back(ch);
            }
        }
        if (!str.empty()) {
            data_vec.push_back(str);
            str.clear();
        }
        return rde(data_vec);
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));
```

### O(1) 时间插入、删除和获取随机元素

实现RandomizedSet 类：

```
RandomizedSet() 初始化 RandomizedSet 对象
bool insert(int val) 当元素 val 不存在时，向集合中插入该项，并返回 true ；否则，返回 false 。
bool remove(int val) 当元素 val 存在时，从集合中移除该项，并返回 true ；否则，返回 false 。
int getRandom() 随机返回现有集合中的一项（测试用例保证调用此方法时集合中至少存在一个元素）。每个元素应该有 相同的概率 被返回。
```

你必须实现类的所有函数，并满足每个函数的 平均 时间复杂度为 O(1) 。

```cpp
class RandomizedSet {
public:
    // 数组可以o(1)地获取元素，哈希可以o(1)插入删除，
    // 二者结合起来就是vec+hashmap
    RandomizedSet() {
        // 初始化随机种子
        srand((unsigned)time(NULL));
    }
    
    bool insert(int val) {
        // 塞进vec里，同时记录下标到map中
        if (indices.count(val)) {
            return false;
        }
        int index = nums.size();
        nums.emplace_back(val);
        indices[val] = index;
        return true;
    }
    
    bool remove(int val) {
        // 为了o(1)，先把这个数找出来，
        // 然后在vec把这个元素换成最后一个元素，pop_back就行
        // hashmap里也删掉，同时更新last的下标
        if (!indices.count(val)) {
            return false;
        }
        int index = indices[val];
        int last = nums.back();
        nums[index] = last;
        nums.pop_back();
        indices[last] = index;
        indices.erase(val);
        return true;
    }
    
    int getRandom() {
        int rand_idx = rand() % nums.size();
        return nums[rand_idx];
    }
    vector<int> nums;
    unordered_map<int, int> indices;
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
```

### LRU 缓存

请你设计并实现一个满足  LRU (最近最少使用) 缓存 约束的数据结构。
实现 LRUCache 类：

LRUCache(int capacity) 以 正整数 作为容量 capacity 初始化 LRU 缓存

int get(int key) 如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1 。

void put(int key, int value) 如果关键字 key 已经存在，则变更其数据值 value ；如果不存在，则向缓存中插入该组 key-value 。如果插入操作导致关键字数量超过 capacity ，则应该 逐出 最久未使用的关键字。

函数 get 和 put 必须以 O(1) 的平均时间复杂度运行。

**解法**

hash表+双向链表

**最近用的放最开头，这样自然链表尾部的就是最近没用的了**

**双向链表需要同时有dummyhead和dummytail**

**hashmap存的key是int，但value要是DLinkNode\*!!!**

```
get(key):
if key不存在:
    return -1;
else:
    把数据(key, val)移到开头（！！最近使用了）
    return val

put(key, val):
if key已存在:
    删掉旧数据
    把新数据扔到开头（！！注意）
else:
    if cache已满:
        删掉链表最后一个位置的元素
        删掉map里的元素
    新节点扔到开头
    map中加入kv
```

```cpp
struct DLinkeList {
    int key;
    int value;
    DLinkeList* pre;
    DLinkeList* next;
    DLinkeList(): key(0), value(0), pre(nullptr), next(nullptr) {}
    DLinkeList(int k, int v): key(k), value(v), pre(nullptr), next(nullptr) {}
};

class LRUCache {
private:
    unordered_map<int, DLinkeList*> cache;  
    DLinkeList* head;
    DLinkeList* tail;
    int capacity;
    int size; // 还要存实际size

public:    
    // 这里记得加上初始化列表！！！！
    LRUCache(int capacity): capacity(capacity), size(0) {
        head = new DLinkeList();
        tail = new DLinkeList();
        head->next = tail;// 把head和tail连起来
        tail->pre = head;
    }
    
    int get(int key) {
        if (!cache.count(key)) {
            return -1;
        } else {
            DLinkeList* node = cache[key];
            move_to_head(node);
            return node->value;
        }
    }

    void remove_node(DLinkeList* node) {
        node->pre->next = node->next;
        node->next->pre = node->pre;
    }

    void add_to_head(DLinkeList* node) {
        // 标准答案是别的顺序，效果应该一样吧。。
        node->next = head->next;
        head->next->pre = node;
        head->next = node;
        node->pre = head;     
    }

    void move_to_head(DLinkeList* node) {
        // 先把node删了，这样node就是孤立的节点了
        remove_node(node);
        // 然后把这个node插入头部
        add_to_head(node);
    }

    DLinkeList* remove_tail() {
        // 直接复用前面写的remove_node
        // 这样也方便return
        DLinkeList* node = tail->pre;
        remove_node(node);
        return node;
    }

    void put(int key, int value) {
        if(!cache.count(key)) {
            DLinkeList* node = new DLinkeList(key, value);
            add_to_head(node);
            cache[key] = node;
            ++size; //记得更新size
            // 开始LRU的操作
            if (size > capacity) {
                DLinkeList* remove_node = remove_tail();
                cache.erase(remove_node->key);
                delete remove_node; // 防止内存泄漏
                --size;
            }
        } else {
            DLinkeList* node = cache[key];
            node->value = value;
            move_to_head(node); // 记得扔到最前面去，这样才能lru
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
```


## 数学

### 快乐数

编写一个算法来判断一个数 n 是不是快乐数。

「快乐数」 定义为：

对于一个正整数，每一次将该数替换为它每个位置上的数字的平方和。
然后重复这个过程直到这个数变为 1，也可能是 无限循环 但始终变不到 1。
如果这个过程 结果为 1，那么这个数就是快乐数。
如果 n 是 快乐数 就返回 true ；不是，则返回 false 。

```cpp
    int square_sum(int n) {
        int sum = 0;
        while (n > 0) {
            int bit = n % 10;
            sum += bit * bit;
            n /= 10;
        }
        return sum;
    }
    bool isHappy(int n) {
        // 只有两种情况，
        // 一直走，最后是1，相当于无环链表，是快乐数，可以快慢指针
        // 一个有环链表，可以快慢指针，相遇点不是1
        // 没有第三种情况，因为数字再大，也会归结到一个小很多的数开始的链表，
        // 具体证明可以参考https://leetcode-cn.com/problems/happy-number/solution/kuai-le-shu-by-leetcode-solution/
        int fast = n, slow = n;
        // ！！用do while，因为一开始fast=slow，但仍想走一次循环
        do {
            fast = square_sum(square_sum(fast));
            slow = square_sum(slow);
        } while (fast != slow);
        if (fast == 1) {
            return true;
        }
        return false;
    }
```

### 阶乘后的零

给定一个整数 n ，返回 n! 结果中尾随零的数量。

![](assets/trailing-zeros.png)
其实这个就是n一直除以5，然后加起来

```cpp
    int trailingZeroes(int n) {
        // 因为5*2=10,其实就是看质因子中5和2的个数，5的个数肯定没有2多，
        // 如上图，其实就是一直除以5，再加起来
        int res = 0;
        while (n) {
            n /= 5;
            res += n;
        }
        return res;
    }
```

###  Excel 表列序号

给你一个字符串 columnTitle ，表示 Excel 表格中的列名称。返回 该列名称对应的列序号 。

例如：
```
A -> 1
B -> 2
C -> 3
...
Z -> 26
AA -> 27
AB -> 28 
```


```cpp
    int titleToNumber(string columnTitle) {
        // 其实是26进制转10进制
        int num = 0;
        long multiple = 1; // 从1开始，需要是long，因为int会爆！！！！！
        //倒着来，其实是从最低位开始
        for (int i = columnTitle.size() - 1; i >= 0; --i) {
            int k = columnTitle[i] - 'A' + 1; // 记得+1...
            num += k * multiple;
            multiple *= 26;
        }
        return num;
    }
```

### Pow(x, n)

实现 pow(x, n) ，即计算 x 的 n 次幂函数（即，xn ）。


```cpp
    double pow_sub(double x, long long N) {
        double res = 1.0;
        double x_contribute = x;
        while (N > 0) {
            if (N % 2 == 1) {
                res *= x_contribute;
            }
            x_contribute *= x_contribute;
            N /= 2;
        }
        return res;
    }
    double myPow(double x, int n) {
        // 其实就是把幂指数n进行二进制拆分，如n=9，那就是
        // 1 * 2^3 + 0 * 2^2 + 0 * 2^1 + 1 * 2^0= 2^3+1 
        // ==> x^9=x^8 *x^1
        // 这么变成二进制：
        // n=9，n %2 =1,要！ 
        // n/=2==> n=4, n%2=0，不要！
        // n/=2==>n=2, n%2=0，不要！
        // n/=2 ==>n=1, n%2=1，要！
        // 因为除了1外，2^n全是偶数，所以如果n%2=1，那就需要这个1
        // 还需要考虑如果n是负的，那就是1/xx
        long long N = n;
        return N >= 0? pow_sub(x, N): 1 / pow_sub(x,-N);
    }
```

### x 的平方根

给你一个非负整数 x ，计算并返回 x 的 算术平方根 。

由于返回类型是整数，结果只保留 整数部分 ，小数部分将被 舍去 。

注意：不允许使用任何内置指数函数和算符，例如 pow(x, 0.5) 或者 x ** 0.5 。


```cpp
    int mySqrt(int x) {
        // 二分
        // 只返回整数部分，那就是k^2<=x的最大k，可以从0到x开始二分
        int left = 0, right = x, res = -1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if ((long long)mid * mid <= x) {
                res = mid; // 一直更新 不break
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return res;
    }
```

### 两数相除

给定两个整数，被除数 dividend 和除数 divisor。将两数相除，要求不使用乘法、除法和 mod 运算符。

返回被除数 dividend 除以除数 divisor 得到的商。

整数除法的结果应当截去（truncate）其小数部分，例如：truncate(8.345) = 8 以及 truncate(-2.7335) = -2

```cpp
    // 求dividend / divisor
    int divide(int dividend, int divisor) {
        // // 参考https://leetcode-cn.com/problems/divide-two-integers/solution/jian-dan-yi-dong-javac-pythonjs-liang-sh-ptbw/
        // // 先处理边界
        // // INT_MIN：-2147483648=2^31，INT_MAX：2147483648=-2^31
        // // int 属于[-2^31 +1, 2^31 - 1]
        // 假设x <0， y <0，求x/y相当于找个最大的正数z，使得
        // yz>=x，注意应该是最大！，举例：算-10/-2，
        // 如果z=5, -10=-10，z=4，那-8>-10,z=6，那-12<-10
        // 因此，是最大的z，使得yz>=x，因为z=6就yz<x了

        if (dividend == INT_MIN) {
            if (divisor == 1) {
                return INT_MIN;
            }
            if (divisor == -1) {
                return INT_MAX;
            }
        }
        if (divisor == INT_MIN) {
            // a / (-2^31) = 0，因为除数绝对值最大
            return dividend == INT_MIN? 1: 0;
        }
        if (dividend == 0) {
            return 0;
        }
        bool rev = false; // 看最后要不要变号
        if (dividend > 0) {
            dividend = -dividend;
            rev = !rev;
        }
        if (divisor > 0) {
            divisor = -divisor;
            rev = !rev;
        }
        auto quick_add = [](int y, int z, int x) {
            // 判断zy是否>=x
            // y负数，x负数，z正数！
            // 对于三个负数a b c，要比较a+b与c，因为a+b可能溢出
            // 所以要改成a与c-b比较，因为两个负数的差不会越界

            // 计算y*z类似y^z
            // 3^5= 3^(1*2^2 + 0*2^1 + 1)
            // 3 * 5 = 3 * (1*2^2+ 0*2^1 + 1)=3*1*2^2+ 3*0 + 3 *1
            // 都是相当于对z=5不断除以2
            // y^z：如果是1，那就res*=y，然后y*=y
            // y*z：如果是1，那就res+=y，然后y+=y

            int result = 0, add = y;
            while(z) {
                if (z & 1) {
                    // z的二进制的最后一位是1,z % 2 == 1，
                    // 要保证result + add >= x
                    if (result < x - add) {
                        return false; //注意这里是直接return false
                    }
                    result += add;
                }
                if (z != 1) {
                    // 要保add + add >= x
                    if (add < x - add) {
                        return false; //注意这里是直接return false
                    }
                    add += add;
                }
                z >>= 1;// z/2
            }
            return true;
        };

        int left = 0, right = INT_MAX, res = 0;
        while (left <= right) {
            int mid = left + ((right - left) >> 1);
            bool check = quick_add(divisor, mid, dividend);
            if (check) {
                res = mid;
                if (mid == INT_MAX) {
                    break;
                }
                left = mid + 1; // 想找更大的 直到找到最大的
            } else {
                right = mid - 1;
            }
        }
        return rev? -res: res;

    }
```

### 分数到小数

给定两个整数，分别表示分数的分子 numerator 和分母 denominator，以 字符串形式返回小数 。

如果小数部分为循环小数，则将循环的部分括在括号内。

如果存在多个答案，只需返回 任意一个 。

对于所有给定的输入，保证 答案字符串的长度小于 104 。

有限小数：
![](assets/fraction-to-decimal-2.png)
无限循环小数：
![](assets/fraction-to-decimal.png)

```cpp
    string fractionToDecimal(int numerator, int denominator) {
        // !!!!!无限不循环小数属于实数中的无理数，
        // !!!!!并且任何一个无限不循环小数都找不到一个与之相等的分数来对应。
        // 所以如果是无限小数，肯定是无限循环小数
        // 每一位小数=余数*10再除以除数得到的商。
        // 循环小数：通过判断被除数（*10之前）有没有出现过，
        // 出现的位置就是循环节的开始，到结尾就是循环节的结束(哈希记录)
        // 如果余数==0，那就是可以除尽了，不是循环小数
        long numerator_long = numerator; //防止溢出，转成int64！！！
        long denominator_long = denominator;
        if (numerator_long % denominator_long == 0) { //整除
            return to_string(numerator_long / denominator_long);
        }
        string res;
        if ((numerator_long < 0) ^ (denominator_long < 0)) {
            //异或，为true说明二者异号
            res.push_back('-');
        }
        numerator_long = abs(numerator_long);
        denominator_long = abs(denominator_long);
        long integer = numerator_long / denominator_long;
        res += to_string(integer);
        res.push_back('.');
        string fraction;
        unordered_map<long, int> remainder_index_map;
        long remainder = numerator_long % denominator_long;
        int idx = 0;
        while (remainder != 0 && !remainder_index_map.count(remainder)) {
            remainder_index_map[remainder] = idx; // 记录*10之前的remainder的位置
            remainder *= 10;
            fraction += to_string(remainder / denominator_long);
            remainder %= denominator;
            ++idx;
        }
        if (remainder != 0) {
            int first_idx = remainder_index_map[remainder];
            // 把循环节部分用括号包起来
            fraction = fraction.substr(0, first_idx) + '(' + \
                fraction.substr(first_idx) + ')';
        }
        res += fraction;
        return res;
    }
```


## 其他

### 两整数之和
给你两个整数 a 和 b ，不使用 运算符 + 和 - ​​​​​​​，计算并返回两整数之和。

```cpp
    int getSum(int a, int b) {
        // 不能用+-，那就位运算
        // 正整数的补码与原码相同；
        // 负整数的补码为其原码除符号位外的所有位取反后加1。
        // 可以将减法运算转化为补码的加法运算来实现。
        // 0 + 0 = 0
        // 0 + 1 = 1
        // 1 + 0 = 1
        // 1 + 1 = 0 (进位)
        // 相当于不考虑进位，就是a^b（异或），
        // 而进位的值是a&b，进位完就是左移一位 (a&b) << 1
        // 注意，实际的a b是很多位的，所以进位也是很多位的，
        // 所以要有个while，一直加进位直到没有进位为止！！！
        while (b != 0) {
            // 当我们赋给signed类型一个超出它表示范围的值时，结果是undefined；
            // 而当我们赋给unsigned类型一个超出它表示范围的值时，结果是
            // 初始值对无符号类型表示数值总数取模的余数！！
            // 因此，我们可以使用无符号类型来防止溢出。
            unsigned int carry = (unsigned int)(a & b) << 1;
            // 另外，这里得是(unsigned int)(a & b) 再<<1，而不是(a & b) << 1再unsigned int!!!
            a = a ^ b;
            b = carry;
        }
        return a;
    }
```

### 逆波兰表达式求值

根据 逆波兰表示法，求表达式的值。

有效的算符包括 ```+、-、*、/ ```。每个运算对象可以是整数，也可以是另一个逆波兰表达式。

注意 两个整数之间的除法只保留整数部分。

可以保证给定的逆波兰表达式总是有效的。换句话说，表达式总会得出有效数值且不存在除数为 0 的情况。

```cpp
    bool is_num(string& token) {
        return !(token == "+" || token == "-" || token == "*" | token == "/");
    }

    int evalRPN(vector<string>& tokens) {
        // 栈：从左到右遍历表达式
        // 遇到数字，入栈
        // 遇到运算符号op，pop栈顶b出来作为右，再pop栈顶a出来作为左，
        //   计算a op b的结果再入栈
        // 遍历完后，栈内只有一个数，就是结果
        // 注意 题目要求除法只保留整除的结果，所以stk用int就行
        stack<int> stk;
        int n = tokens.size();
        for (int i = 0; i < n; ++i) {
            string& token = tokens[i];
            if (is_num(token)) {
                stk.push(atoi(token.c_str())); // string转int
            } else {
                int right = stk.top();
                stk.pop();
                int left = stk.top();
                stk.pop();
                switch (token[0]) {
                    case '+':
                        stk.push(left + right);
                        break;
                    case '-':
                        stk.push(left - right);
                        break;
                    case '*':
                        stk.push(left * right);
                        break;
                    case '/':
                        stk.push(left / right);
                        break;
                }
            }
        }
        return stk.top();
    }
```

### 多数元素

给定一个大小为 n 的数组 nums ，返回其中的多数元素。多数元素是指在数组中出现次数 大于 ⌊ n/2 ⌋ 的元素。

你可以假设数组是非空的，并且给定的数组总是存在多数元素。


```cpp
    int majorityElement(vector<int>& nums) {
        // 因为题目说了大于半数，所以排序后肯定会占据一半一上的区间，
        // 所以中间的数肯定是它
        sort(nums.begin(), nums.end());
        return nums[nums.size() / 2];
    }
```

### 任务调度器

给你一个用字符数组 tasks 表示的 CPU 需要执行的任务列表。其中每个字母表示一种不同种类的任务。任务可以以任意顺序执行，并且每个任务都可以在 1 个单位时间内执行完。在任何一个单位时间，CPU 可以完成一个任务，或者处于待命状态。

然而，两个 相同种类 的任务之间必须有长度为整数 n 的冷却时间，因此至少有连续 n 个单位时间内 CPU 在执行不同的任务，或者在待命状态。

你需要计算完成所有任务所需要的 最短时间 。


![](assets/task-distribute.png)

```cpp
    int leastInterval(vector<char>& tasks, int n) {
        unordered_map<char, int> freq; // 记录每一种任务的个数
        for (auto& i: tasks) {
            ++freq[i];
        }
        // stl的max_element
        // 获取所有任务中最多的次数
        int max_exec = max_element(freq.begin(), freq.end(), 
            [](const auto& a, const auto& b) {
                return a.second < b.second;
            })->second;
        // <1> [var] 表示值传递方式捕捉变量var
        // <2> [=] 表示值传递方式捕捉所有父作用域的变量（包括this指针）
        // <3> [&var] 表示引用传递捕捉变量var
        // <4> [&] 表示引用传递捕捉所有父作用域的变量（包括this指针）
        // <5> [this] 表示值传递方式捕捉当前的this指针
        // <6> [=，&a，&b] 表示以引用传递的方式捕捉变量 a 和 b，而以值传递方式捕捉其他所有的变量
        // <7> [&，a，this] 表示以值传递的方式捕捉 a 和 this，而以引用传递方式捕捉其他所有变量
        
        // 计算总共有多少个任务出现了max_exec次
        int max_cnt = accumulate(freq.begin(), freq.end(), 0, 
            [=](int acc, const auto& u){
                return acc + (u.second == max_exec);
            });
        
        // 对于max_exec个任务a来讲，每执行一次后面要n个空位，
        // 所以要(max_exec -1) * (n+1) +1，最后这个+1是最后一个a任务，因为它执行完就行了
        // 而总共有max_cnt个a任务，如果max_cnt<= n+1，那么可以塞进去
        // 就有max_exec - 1) * (n + 1) + max_cnt了
        // 填后面任务按这个方法：
        // 我们从倒数第二行开始，按照反向列优先的顺序（即先放入靠左侧的列，同一列中先放入下方的行），
        // 依次放入每一种任务，并且同一种任务需要连续地填入。
        // 如果max_cnt > n+1，那排完n+1后还要再排k列，然后才是其他任务，
        // 这个时候就不需要再这么按顺序了，因为任意两个任务间肯定大于n，所以总时间就是|tasks|
        // xx.size()需要强转成int，因为原来是size_t
        return max((max_exec - 1) * (n + 1) + max_cnt, static_cast<int>(tasks.size()));
    }
```

## 字典树

### 字典序的第K小数字

给定整数 n 和 k，返回  [1, n] 中字典序第 k 小的数字。

```
示例 1:
输入: n = 13, k = 2
输出: 10
解释: 字典序的排列是 [1, 10, 11, 12, 13, 2, 3, 4, 5, 6, 7, 8, 9]，所以第二小的数字是 10。

示例 2:
输入: n = 1, k = 1
输出: 1
```

字典序就是**根据数字的前缀进行排序**，比如 10 < 9，因为 10 的前缀是 1，比 9 小。

![](assets/trie-tree.png)

**前序遍历**字典树即可得到字典序从小到大的数字序列，遍历到第k个节点就是第k小的数

但其实不用建树

节点i的子节点为$$(i\times 10, i\times 10+1,...,i\times 10 + 9)$$，

设**当前的字典树的第 i 小的节点为 $$n_i$$**，则只需按照先序遍历再继续往后找 k - i个节点即为目标节点。

假设**以$$n_i$$为根的子树的节点数是** $$step(n_i)$$，那么

+ 如果$$step(n_i)<=k-i$$，那么第k小的节点在$$n_i$$的右兄弟的子树中，可以直接从兄弟$$n_{i+1}$$开始往后找$$k-i-step(n_i)$$个节点
+ 如果$$step(n_i)>k-i$$，那么第k小的节点肯定在$$n_i$$的子树中，从左侧第一个孩子中找k-i-1个节点

计算$$step(n_i)$$：

层次遍历，第i层的最左侧的孩子节点是$$first_i$$，最右侧节点是$$last_i$$，第i层总共有$$last_i - first_i + 1$$个节点，

其中，$$first_i = 10\times first_{i-1}$$

$$last_i = 10\times last_{i-1} + 9$$

因为总节点数最多为n，所以第i层最右节点是min(n, last_i)

不断迭代直到$$first_i>n$$就不再向下搜索

```cpp
    int get_steps(int cur, long n) {
        int steps = 0;
        long first = cur; //long?
        long last = cur;
        // 层次遍历
        while (first <= n) {
            steps += min(last, n) - first + 1;
            first = first * 10;
            last = last * 10 + 9;
        }
        return steps;
    }

    int findKthNumber(int n, int k) {
        int cur = 1;
        k--;
        while (k > 0) {
            int steps = get_steps(cur, n);
            if (steps <= k) {
                k -= steps;// 跳过当前子树，往右走
                cur++;
            } else {
                cur = cur * 10;//进入左子树
                k--;
            }
        }
        return cur;
    }
```

## 其他2

### auc计算

自己写的，假设m正例，n负例，

方法一：先按score排序，然后看1后面多少个0，就是分对了多少个pair对，加起来就是分子，分母是mxn

方法二：先按score排序，然后倒着看每个对应的真实label，如果是0那就a+1，如果是1，那就res+a，res就是分子，分母还是mxn

方法三：包括了rank的那个公式，也就是先排序，然后计算label=1的rank之和（最大的rank是n，次大是n-1），【其实算的就是当前数比多少个要大】，再减掉两个都是正样本的情况，分母还是mxn

注意，是先对rank求和，再减掉xxx，不是每个rank都要减掉xxx！！！

$$
A U C=\frac{\sum_{\mathrm{i} \in \text { positiveClass }} \operatorname{rank}_{i}-\frac{M(1+M)}{2}}{M \times N}
$$

[https://zhuanlan.zhihu.com/p/411010918](https://zhuanlan.zhihu.com/p/411010918)这里是升序，一个道理，只是把rank倒过来了


```python
def calc_auc(labels, scores):
    """calc_auc"""
    pos_cnt = 0
    neg_cnt = 0
    for i in labels:
        if i == 0:
            neg_cnt +=1
        elif i == 1:
            pos_cnt += 1
    if pos_cnt == 0 or neg_cnt == 0:
        return -1
    sorted_scores = sorted(scores, reverse=True)
    xdic = {}
    for i in range(0, len(scores)):
        xdic[scores[i]] = i
    auc = 0
    xpos_cnt = 0
    for idx in range(0, len(sorted_scores)):
        label = labels[xdic[sorted_scores[idx]]]
        if label == 1:
            for j in range(idx + 1, len(sorted_scores)):
                xlabel = labels[xdic[sorted_scores[j]]]
                if xlabel == 0:
                    xpos_cnt += 1

    return float(xpos_cnt) / (pos_cnt * neg_cnt)

def calc_auc2(labels, scores):
    """xx"""
    pos_cnt = 0
    neg_cnt = 0
    for i in labels:
        if i == 0:
            neg_cnt +=1
        elif i == 1:
            pos_cnt += 1
    if pos_cnt == 0 or neg_cnt == 0:
        return -1
    sorted_scores = sorted(scores, reverse=True)
    xdic = {}
    for i in range(0, len(scores)):
        xdic[scores[i]] = i
    a = 0
    xres = 0
    idx = len(scores) - 1
    while idx >= 0:
        label = labels[xdic[sorted_scores[idx]]]
        if label == 0:
            a += 1
        if label == 1:
            xres += a
        idx -= 1

    return float(xres) / (pos_cnt * neg_cnt)

def calc_auc3(labels, scores):
    """calc_auc3"""
    pos_cnt = 0
    neg_cnt = 0
    for i in labels:
        if i == 0:
            neg_cnt +=1
        elif i == 1:
            pos_cnt += 1
    if pos_cnt == 0 or neg_cnt == 0:
        return -1
    sorted_scores = sorted(scores, reverse=True)
    xdic = {}
    for i in range(0, len(scores)):
        xdic[scores[i]] = i
    auc = 0
    xpos_cnt = 0
    rank = 0
    for idx in range(0, len(sorted_scores)):
        label = labels[xdic[sorted_scores[idx]]]
        if label == 1:
            rank += len(sorted_scores) - idx

    return (rank - pos_cnt * (pos_cnt + 1) / 2.) / (pos_cnt * neg_cnt)

if __name__ == "__main__":
    labels = [0,1,0, 1]
    scores = [0.3, 0.3, 0.2, 0.8]
    print calc_auc(labels, scores)
    print calc_auc2(labels, scores)
    print calc_auc3(labels, scores)
```

但第三种解法对于相同预估值的情况会有问题，正确的解法是

学习下pnr：

[https://www.jianshu.com/p/e9813ac25cb6](https://www.jianshu.com/p/e9813ac25cb6)

auc和pnr的关系？

随便找一个正负pair，auc是预测对的pair数/总pair数

pnr是预测对的pair数/错的pair数

a=对的pair数，b=错的pair数

auc=a/(a+b)

pnr = a/b

==>1/auc = 1+b/a = 1+1/pnr

==> auc= 1/(1+1/pnr)=pnr/(pnr+1)

o(n^2)解法如下

```python
#encoding=utf8
from itertools import groupby
import sys
def calc_auc_and_pnr(labels, probs):
    N = 0           # 正样本数量
    P = 0           # 负样本数量
    neg_prob = []   # 负样本的预测值
    pos_prob = []   # 正样本的预测值
    for index, label in enumerate(labels):
        if label == 1:
            # 正样本数++
            P += 1
            # 把其对应的预测值加到“正样本预测值”列表中
            pos_prob.append(probs[index])
        else:
            # 负样本数++
            N += 1
            # 把其对应的预测值加到“负样本预测值”列表中
            neg_prob.append(probs[index])
    number = 0
    r_number = 0
    # 遍历正负样本间的两两组合
    for pos in pos_prob:
        for neg in neg_prob:
            # 如果正样本预测值>负样本预测值，正序对数+1
            if (pos > neg):
                number += 1.
            # 如果正样本预测值==负样本预测值，算0.5个正序对
            elif (pos == neg):
                number += 0.5
                r_number += 0.5
            else:
                r_number += 1.
    pnr = number / r_number
    auc = number / (N * P)
    return auc, pnr


if __name__ == '__main__':
    for user, lines in groupby(sys.stdin, key=lambda x:x.split('\t')[0]):
        lines = list(lines)
        #print lines
        trues = [float(x.strip().split('\t')[1]) for x in lines]
        preds = [float(x.strip().split('\t')[2]) for x in lines]
        auc, pnr = calc_auc_and_pnr(trues, preds)
        ## auc = 1/(1+1/pnr) ==> pnr = 1/ (1/a - 1)
        pnr_check = 1. / (1. / auc - 1 + 1e-9)
        print auc, pnr, pnr_check
```

O(nlogn)如下：

```python
from itertools import groupby
import sys
def calc_auc_and_pnr_fast(label,pred):
    sample = zip(label,pred)
    ## 根据pred倒排
    sample_sorted = sorted(sample,key=lambda x: -x[1])
    pos = 0
    cnt = 0
    r_cnt = 0
    last_pred = 0
    for i in range(len(sample_sorted)):
        l, p = sample_sorted[i]
        if l == 1:
            pos += 1
        elif l == 0:
            cnt += pos # 截止目前，有pos个正样本比他大
            if (i != 0 and last_pred == p):
                cnt -= 0.5
        last_pred = p
    n = len(label)
    negs = n - pos
    r_cnt = pos * negs - cnt
    auc = float(cnt) / float(pos * negs)
    pnr = float(cnt) / r_cnt
    return auc, pnr

if __name__ == '__main__':
    for user, lines in groupby(sys.stdin, key=lambda x:x.split('\t')[0]):
        lines = list(lines)
        #print lines
        trues = [float(x.strip().split('\t')[1]) for x in lines]
        preds = [float(x.strip().split('\t')[2]) for x in lines]
        auc, pnr = calc_auc_and_pnr_fast(trues, preds)
        ## auc = 1/(1+1/pnr) ==> pnr = 1/ (1/a - 1)
        pnr_check = 1. / (1. / auc - 1 + 1e-9)
        print auc, pnr, pnr_check
```
