# 基础知识

## 大小写

A的ascii码：65
a的ascii码：97

小写转大写：a-32; 大写转小写：a+32

## 进制转换

输入十六进制数，输出10进制数：

例如输入0xA，输出10

```c++
    int a;
    while (cin >> hex >> a) {
        cout << a << endl;
    }
```


# c++基础

## 实现单例模式

参考[https://www.cnblogs.com/qiaoconglovelife/p/5851163.html](https://www.cnblogs.com/qiaoconglovelife/p/5851163.html)

### 线程不安全版本的经典实现(懒汉实现)

+ **构造函数**声明为**private或protect**防止被外部函数实例化
+ 内部保存一个**private static的类指针p**保存唯一的实例
+ 由一个**public**的类方法 **(instance函数)**返回单例类唯一的**static实例指针**
+ 全局范围内给p赋**初始值NULL**
+ insance函数里判断指针p是否为NULL，如果是就new一个，反之直接return p

如果两个线程同时首次调用instance方法且**同时检测到p是NULL值**，则两个线程会**同时构造一个实例给p**，因此是线程不安全的！！

```c++
class singleton
{
protected:
    singleton(){}
private:
    static singleton* p;
public:
    static singleton* instance();
};
singleton* singleton::p = NULL;
singleton* singleton::instance()
{
    if (p == NULL)
        p = new singleton();
    return p;
}
```

单例大约有两种实现方法：懒汉与饿汉。

+ **懒汉**：故名思义，**不到万不得已就不会去实例化类**，也就是说在**第一次用到类实例的时候才会去实例化**，所以上边的经典方法被归为懒汉实现；
+ **饿汉**：饿了肯定要饥不择食。所以在**单例类定义的时候就进行实例化**。
　　
特点与选择：

+ 由于要进行**线程同步**，所以在**访问量比较大，或者可能访问的线程比较多时**，采用**饿汉**实现，可以实现更好的性能。这是**以空间换时间**。
+ 在**访问量较小时**，采用**懒汉**实现。这是**以时间换空间**。

### 加锁的经典版本懒汉实现

```c++
class singleton
{
protected:
    singleton()
    {
        pthread_mutex_init(&mutex);
    }
private:
    static singleton* p;
public:
    static pthread_mutex_t mutex;
    static singleton* initance();
};

pthread_mutex_t singleton::mutex;
singleton* singleton::p = NULL;
singleton* singleton::initance()
{
    if (p == NULL)
    {
        pthread_mutex_lock(&mutex);
        if (p == NULL)
            p = new singleton();
        pthread_mutex_unlock(&mutex);
    }
    return p;
}
```

### 加锁的懒汉实现

+ 定义一个**静态**的pthread_mutex_t类型的**类变量mutex**
+ **构造函数**中对这个mutex进行**pthread_mutex_init**
+ **instance函数里**
    + 先加锁pthread_mutex_lock
    + 定义一个**静态的实例**
    + 释放锁pthread_mutex_unlock
    + **返回其静态实例的地址**

```c++
class singleton
{
protected:
    singleton()
    {
        pthread_mutex_init(&mutex);
    }
public:
    static pthread_mutex_t mutex;
    static singleton* initance();
    int a;
};

pthread_mutex_t singleton::mutex;
singleton* singleton::initance()
{
    pthread_mutex_lock(&mutex);
    static singleton obj;
    pthread_mutex_unlock(&mutex);
    return &obj;
}
```

### 不用加锁的饿汉版本实现

+ **构造函数**声明为**private或protect**防止被外部函数实例化
+ 内部保存一个**private static的类指针p**保存唯一的实例
+ 由一个**public**的类方法 **(instance函数)**返回单例类唯一的**static实例指针**，实现时**直接返回p**
+ 全局范围内**new一个对象给p**

```c++
class singleton
{
protected:
    singleton()
    {}
private:
    static singleton* p;
public:
    static singleton* initance();
};
singleton* singleton::p = new singleton;
singleton* singleton::initance()
{
    return p;
}
```

# 字符串

## 实现 strStr()

[https://leetcode-cn.com/problems/implement-strstr/](https://leetcode-cn.com/problems/implement-strstr/)

给定一个 haystack 字符串和一个 needle 字符串，在 haystack 字符串中找出 needle 字符串出现的第一个位置 (从0开始)。如果不存在，则返回  -1。

示例 1:

```
输入: haystack = "hello", needle = "ll"
输出: 2
```

示例 2:

```
输入: haystack = "aaaaa", needle = "bba"
输出: -1
```

说明:

当 needle 是空字符串时，我们应当返回什么值呢？这是一个在面试中很好的问题。
对于本题而言，当 needle 是空字符串时我们应当返回 0 。这与C语言的 strstr() 以及 Java的 indexOf() 定义相符。


```c++
class Solution {
public:
    int strStr(string haystack, string needle) {
        int len_1 = haystack.size();
        int len_2 = needle.size();
        if (len_2 == 0) return 0;
        for (int i = 0; i < len_1 - len_2 + 1; ++i) {
            int j = i;
            int k = 0;
            while (haystack[j++] == needle[k++]) {
                if (k == len_2) {
                    return i;
                }
            }
        }
        return -1;
    }
};
```

## 替换空格(offerNo5)

请实现一个函数，将一个字符串中的每个空格替换成“%20”。例如，当字符串为We Are Happy.则经过替换之后的字符串为```We%20Are%20Happy```。

解答：

+ 先**从前往后**，计算有**多少个空格**，然后预分配原始长度+2倍的空格数这么长
+ 然后使用**两个指针**，**从后往前**处理：
    + 第一个指针初始指向原字符串的末尾。
    + 第二个指针初始指向新的末尾。
    + 如果第一个指针指向的是空格，那么第二个指针往前移三格，并依次置```0```、```2```、```%```，并前移第一个指针
    + 如果第一个指针指向的不是空格，那么第二个指针把第一个指针的值拷过来，并前移两个指针
    + 当两个指针相遇时结束

```char*str```，直接用下标来取就行```str[xxlength]```，所以上面说的两个指针，其实就是两个下标~！


```c++
class Solution {
public:
	void replaceSpace(char *str,int length) {
        if (str == NULL || length <= 0) {
            return;
        }
        int old_len = 0;
        int new_len = 0;
        int space_cnt = 0;
        while (str[old_len] != '\0') {
            if (str[old_len] == ' ') space_cnt++;
            old_len++;
        }
        new_len = old_len + 2 * space_cnt;
        if (new_len > length) {
            return;
        }
        int pOldlength = old_len; //注意不要减一因为隐藏个‘\0’也要算里
        int pNewlength = new_len;
        while (pOldlength >= 0 && pNewlength > pOldlength) {
             if (str[pOldlength] == ' ') {
                 str[pNewlength--]='0';
                 str[pNewlength--]='2';
                 str[pNewlength--]='%';
                 } else {//不是空格就把pOldlength指向的字符装入pNewlength指向的位置
                     str[pNewlength--]=str[pOldlength];
                 }
                 pOldlength--; //不管是if还是else都要把pOldlength前移      
          }       

	}
};
```



## 亲密字符串

给定两个由小写字母构成的字符串 A 和 B ，只要我们可以通过交换 A 中的两个字母得到与 B 相等的结果，就返回 true ；否则返回 false 。

例如：

```
示例 1：

输入： A = "ab", B = "ba"
输出： true
示例 2：

输入： A = "ab", B = "ab"
输出： false
示例 3:

输入： A = "aa", B = "aa"
输出： true
示例 4：

输入： A = "aaaaaaabc", B = "aaaaaaacb"
输出： true
示例 5：

输入： A = "", B = "aa"
输出： false
```

限制：

+ 0 <= A.length <= 20000
+ 0 <= B.length <= 20000
+ A 和 B 仅由小写字母构成。


分析：

因为题目要求只有两个元素交换一次，所以

+ 如果AB不等长，不可能
+ 如果AB完全相等，看看有没有重复数字，有的话，随便交换两个就能达到要求，否则不可能
+ else，只要遍历数组，找到两个位置i和j，```A[i]!=B[i]```，且```A[j]!=B[j]```，且```A[i]=B[j]```，且```A[j]=B[i]```

```c++
class Solution {
public:
    bool buddyStrings(string A, string B) {
        if (A.size() != B.size()) {
            return false;
        }
        if (A == B) {
            // 这种情况下，如果A里面字母都不重复，那就不符合要求
            int* counts = new int[26];
            for (auto& i: A) {
                counts[i - 'a']++;
            }
            for (int i = 0; i < 26; ++i) {
                if (counts[i] > 1) {
                    return true;
                }
            }
            return false;
        } else {
            int first = -1, second = -1;
            for (int i = 0; i < A.size(); ++i) {
                if (A[i] != B[i]) {
                    // 第一次不相等，给first赋值
                    if (first == -1) {
                        first = i;
                    } else if (second == -1) {
                        // 第二次不相等，给second赋值
                        second = i;
                    } else {
                        // 如果有第3次不相等，就不行了
                        return false;
                    }
                }
            }
            // 如果只有一个不相等是不行的，如果有两个，那就是前面提到的判断条件
            return (second != -1 && A[first] == B[second] && A[second] ==B[first]);
        }
    }
};
```

## 回文数

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

为了避免数字反转可能导致的溢出问题，为什么不考虑只反转 数字的一半？毕竟，如果该数字是回文，其后半部分反转后应该与原始数字的前半部分相同。

例如，输入 1221，我们可以将数字“1221”的后半部分从“21”反转为“12”，并将其与前半部分“12”进行比较，因为二者相同，我们得知数字 1221 是回文。

* 特判

所有负数都不可能是回文，例如：-123 不是回文，因为 - 不等于 3

尾数能被10整除，即尾数是0的也不行，因为首位不是0

* 反转

对于数字 1221，如果执行 1221 % 10，我们将得到最后一位数字 1，要得到倒数第二位数字，我们可以先通过除以 10 把最后一位数字从 1221 中移除，1221 / 10 = 122，再求出上一步结果除以10的余数，122 % 10 = 2，就可以得到倒数第二位数字。如果我们把**最后一位数字乘以10**，再**加上倒数第二位数字**，1 * 10 + 2 = 12，就得到了我们想要的反转后的数字。 如果继续这个过程，我们将得到更多位数的反转数字。

所以，每次把**上一次的数字\*10**，**加上这一次的最后一位数字**，然后**x/=10**，**把这次的尾数扔掉**

现在的问题是，我们如何知道反转数字的位数已经达到原始数字位数的一半？

* 终止

我们将原始数字除以 10，然后给反转后的数字乘上 10，所以，当除完的原始数字不大于反转后的数字时，就意味着我们已经处理了一半位数的数字。

例如，原数字是4123，反转到321>41的时候，就到一半了；如果原数字是412，反转到21>4的时候也到一半了。也就是反转的位数比剩下的多，肯定到一半了。或者，原数字是1234，反转到34>12

举个是回文数的例子，原数字是3223，32==32，break了；原数字121，12>1，break掉

当数字长度为奇数时，我们可以通过 revertedNumber/10 去除处于中位的数字。

例如，当输入为 12321 时，在 while 循环的末尾我们可以得到 x = 12，revertedNumber = 123

由于处于中位的数字不影响回文（它总是与自己相等），所以我们可以简单地将其去除。所以对于奇数位，就是判断x==revertedNumber/10

```c++
class Solution {
public:
    bool isPalindrome(int x) {
        if(x < 0 || (x % 10 == 0 && x != 0)) {
            return false;
        }
        int revertedNumber = 0;
        while(x > revertedNumber) {
            revertedNumber = revertedNumber * 10 + x % 10;
            x /= 10;
        }
        return (x == revertedNumber || x == revertedNumber / 10);
    }
};
```


## 反转整数

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

假设我们的环境只能存储 32 位有符号整数，其数值范围是 [−231,  231 − 1]。根据这个假设，如果反转后的整数溢出，则返回 0。

**解答**

写一个valid函数，记得参数变成long，然后去看这个long是不是在int32的范围里

```c++
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
        if (!valid(x)) {
            return 0;
        }
        bool flag = true;
        if (x < 0) {
            x = -x;
            flag = false;
        }
        while (x != 0) {
            tmp *= 10;
            tmp += x % 10;
            x /= 10;
        }
        if (flag == false) {
            tmp = -tmp;
        }
        if (valid(tmp)) {
            return tmp;
        }
        return 0;
    }
};
```

## 罗马数字转整数

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

```c++
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

## 有效的括号

给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串，判断字符串是否有效。

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
注意一定要先判断st.size()>0再取top，不然会出错，其他的是常规操作

```c++
class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        unordered_map<char, char> mp;
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

### 基础的括号匹配

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

如果先出现了右括号，前面没有左括号的时候（top=0时出现了右括号），直接是NO

```c++
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


# 数组、栈、队列

## 旋转数组的最小数字（offerNo11）

把一个数组**最开始的若干个元素搬到数组的末尾**，我们称之为数组的旋转。 输入一个**非减排序**的数组的一个旋转，输出旋转数组的最小元素。 例如数组{3,4,5,1,2}为{1,2,3,4,5}的一个旋转，该数组的最小值为1。 NOTE：给出的所有元素都大于0，若数组大小为0，请返回0。

旋转之后的数组实际上可以划分成**两个有序的子数组**：**前面子数组**的大小**都大于后面子数组**中的元素

实际上**最小的元素就是两个子数组的分界线**。


方法一：直接找到后一个数比上一个小的位置，那这后一个数就是我们要的了：

```c++
class Solution {
public:
    int minNumberInRotateArray(vector<int> rotateArray) {
        if (rotateArray.size() == 0) return 0;
        int tmp = rotateArray[0];
        for (int i = 0; i < rotateArray.size(); ++i) {
            if (tmp > rotateArray[i]) {
                return rotateArray[i];
            }
            tmp = rotateArray[i];
        } 
        return tmp;
    }
};
```

方法二：二分法：

数组一定程度上是排序的，因此我们试着用**二分查找法**寻找这个最小的元素。拿mid和high做比较，考虑以下三种情况：

+ array[mid] > array[high]:

出现这种情况的array类似[3,4,5,6,0,1,2]，此时最小数字**一定在mid的右边**。

```
low = mid + 1
```

+ array[mid] == array[high]:

出现这种情况的array类似 [1,0,1,1,1] 或者[1,1,1,0,1]，此时最小数字不好判断在mid左边还是右边,这时只好一个一个试 ，所以**high左移一格**

```
high = high - 1
```

+ array[mid] < array[high]:

出现这种情况的array类似[2,2,3,4,5,6,6],此时最小数字一定就**是array[mid]**或者**在mid的左边**。因为右边必然都是递增的。所以**往左半边找。**

```
high = mid
```

注意这里有个坑：如果待查询的范围**最后只剩两个数**，那么mid 一定会指向下标靠前的数字
比如 array = [4,6]
array[low] = 4 ;array[mid] = 4 ; array[high] = 6 ;
**如果high = mid - 1，就会产生错误， 因此high = mid**

但情形(1)中low = mid + 1就不会错误

+ 最终返回array[low]或者array[high]都行

```c++
class Solution {
public:
    int minNumberInRotateArray(vector<int> rotateArray) {
        int low = 0;
        int high = rotateArray.size() - 1;
        while (low < high) {
            int mid = low + (high - low) / 2;
            if (rotateArray[mid] > rotateArray[high]) {
                low = mid + 1;
            } else if (rotateArray[mid] == rotateArray[high]) {
                high = high - 1;
            } else if (rotateArray[mid] < rotateArray[high]) {
                high = mid;
            }
        }
        return rotateArray[high];
    }
};
```

## 用两个栈来实现一个队列（offerNo9）

用两个栈来实现一个队列，完成队列的Push和Pop操作。 队列中的元素为int类型。

+ 入队：将元素进栈A
+ 出队：判断栈B是否为空，
    + 如果为空，则将栈A中所有元素pop，并push进栈B，栈B出栈；
    + 如果不为空，栈B直接出栈。

```c++
class Solution
{
public:
    void push(int node) {
       stack1.push(node); 
    }

    int pop() {
        int a;
        if (stack2.empty()) {
            while (!stack1.empty()) {
                a = stack1.top();
                stack2.push(a);
                stack1.pop();
            }
        }
        a = stack2.top();
        stack2.pop();
        return a;
    }

private:
    stack<int> stack1;
    stack<int> stack2;
};
```

**变形**：用两个队列实现一个栈的功能

+ 入栈：将元素进队列A
+ 出栈：判断队列A中元素的个数是否为1，
    + 如果等于1，则出队列，
    + 否则将队列A中的元素依次出队列并放入队列B，直到队列A中的元素留下一个，然后队列A出队列，再把队列B中的元素出队列以此放入队列A中。

## 数组中重复的数字(offerNo3)

### 重复数字原始题目

一个长度为n的数组中所有数字都在0~n-1之间，有一些数字重复了，找出任意一个重复的数字。

解法：

最简单的是排序，然后从头扫描，要O(nlogn)；或者可以用hashset，O(n)时间，但也要O(n)的hashset的空间

可以用交换的思路：

* 先从头往后走，到第i个位置，
    * 开始一个while循环，判断该位置的数字numbers[i]是不是和它的下标i相等（是否在正确的位置上）
        * 相等的话，跳出while, ++i
        * 不相等，那么比较这个数字a=numbers[i]和以这个数字为下标的数b=numbers[numbers[i]]
            * 相等，找到了！
            * 不等，交换两个数，**继续前面的while，也就是比较换完后的b和numbers[b]**！！！

注意，中间那个while循环，每进行一次交换，就有一个数字在正确的位置上，而最外面的那个判断，如果位置正确就不会while，所以其实复杂度是O(n)

```c++
bool dup(int numbers[], int length, int* dup) {
    if(numbers == nullptr || length <= 0) {
        return false;
    }
    for(int i = 0; i < length; ++i) {
        if(numbers[i] < 0 || numbers[i] > length - 1) { // 边界检查
            return false;
        }
    }

    for(int i = 0; i < length; ++i) {
        while (numbers[i] != i) {
            if (numbers[i] == numbers[numbers[i]]) {
                *dup = numbers[i];
                return true;
            }
        }

        //交换numbers[i]和numbers[numbers[i]]
        int tmp = numbers[i];
        numbers[i] = numbers[temp];
        numbers[temp] = temp;
    }
    return false;
}
```

### 重复数字变种

长度为n+1的数组中，所有数字都是1~n，所以至少有一个重复，要求不能修改输入数组，找出任意一个重复数字

解法：

二分的思想，数字是1~n，那么分成两半，各x个，算一下左边那一半在这个数组里出现的次数，如果比x大，说明重复数字出现在这个区间里，否则在另一个区间里。

```c++
int dup2(const int* numbers, int length) {
    if (numbers == nullptr || length <= 0) {
        return -1;
    }
    int start = 1;
    int end = length - 1;
    while (end >= start) {
        int middle = ((end - start) >> 1) + start; // >>1右移一位，相当于除以2
        int count = count_range(numbers, length, start, middle);
        if (end == start) {
            if (count > 1) {
                return start;
            } else {
                break;
            }
        }

        if (count > (middle - start + 1)) { //比区间长度大，说明在左边的区间里
            end = middle;
        } else {
            start = middle + 1;
        }
    }
    return -1;
}

int count_range(const int* numbers, int length, int start, int end) {
    if (numbers == nullptr) {
        return 0;
    }
    int count = 0;
    for (int i = 0; i < length; ++i) { // 遍历原始的整个数组
        if (numbers[i] >= start && numbers[i] <= end) {
            ++count;
        }    
    }
    return count;
}
```

## 二维数组中的查找(offerNo4)

在一个二维数组中（每个一维数组的长度相同），每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。

解法：

* 矩阵是有序的，从**左下角**来看，向上数字递减，向右数字递增，
* 因此从左下角开始查找，当要查找数字比左下角数字大时。右移
* 要查找数字比左下角数字小时，上移
* 别写两重while

```c++
class Solution {
public:
    bool Find(int target, vector<vector<int> > array) {
        int row_len = array.size();
        if (row_len < 1) {
            return false;
        }
        int col_len = array[0].size();
        int i = col_len - 1;
        int j = 0;
        while (i >= 0 && j < row_len) { // 别写两个while!!!!
                if (array[j][i] < target) {
                    ++j;
                } else if (array[j][i] > target) {
                    --i;
                } else {
                    return true;
                }
        }
        return false;
    }
};
```

注意：也可以从**右上角**开始，但不能从左上角或者右下角开始（因为这样就无法缩小查找范围了）

## 转置矩阵

给定一个矩阵 A， 返回 A 的转置矩阵。

矩阵的转置是指将矩阵的主对角线翻转，交换矩阵的行索引与列索引。

```
示例 1：

输入：[[1,2,3],[4,5,6],[7,8,9]]
输出：[[1,4,7],[2,5,8],[3,6,9]]
示例 2：

输入：[[1,2,3],[4,5,6]]
输出：[[1,4],[2,5],[3,6]]
```

限制：

+ 1 <= A.length <= 1000
+ 1 <= A[0].length <= 1000

解答：

其实就是把按行遍历改成按列遍历输出，拿笔画一下就知道，例如有一个2x3的，push的顺序就是```a[0][0]、a[1][0]、a[2][0]、a[0][1]、...```

```c++
class Solution {
public:
    vector<vector<int>> transpose(vector<vector<int>>& A) {
        vector<vector<int> > res;
        int row_size = A.size();
        int col_size = A[0].size();
        for (int i = 0; i < col_size; ++i) {
            vector<int> tmp_vec;
            for (int j = 0; j < row_size; ++j) {
                tmp_vec.push_back(A[j][i]);
            }
            res.push_back(tmp_vec);
        }
        return res;
    }
};
```

## 移除元素

给定一个数组 nums 和一个值 val，你需要原地移除所有数值等于 val 的元素，返回移除后数组的新长度。

不要使用额外的数组空间，你必须在原地修改输入数组并在使用 O(1) 额外空间的条件下完成。

元素的顺序可以改变。你不需要考虑数组中超出新长度后面的元素。


示例 1:

```
给定 nums = [3,2,2,3], val = 3,

函数应该返回新的长度 2, 并且 nums 中的前两个元素均为 2。

你不需要考虑数组中超出新长度后面的元素。
```

示例 2:

```
给定 nums = [0,1,2,2,3,0,4,2], val = 2,

函数应该返回新的长度 5, 并且 nums 中的前五个元素为 0, 1, 3, 0, 4。

注意这五个元素可为任意顺序。

你不需要考虑数组中超出新长度后面的元素。
```

说明:

为什么返回数值是整数，但输出的答案是数组呢?

请注意，输入数组是以“引用”方式传递的，这意味着在函数里修改输入数组对于调用者是可见的。

你可以想象内部操作如下:

```c++
// nums 是以“引用”方式传递的。也就是说，不对实参作任何拷贝
int len = removeElement(nums, val);

// 在函数里修改输入数组对于调用者是可见的。
// 根据你的函数返回的长度, 它会打印出数组中该长度范围内的所有元素。
for (int i = 0; i < len; i++) {
    print(nums[i]);
}
```

**解答：**

**关键： 保留两个指针 i 和 j，其中 i 是慢指针，j是快指针。**
用j来遍历数组，当nums[j]!=val时，把num[j]赋值给num[i]，然后移动i

```c++
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int i = 0, j = 0; 
        for (;j < nums.size(); ++j) {
            if (nums[j] != val) {
                nums[i] = nums[j];
                ++i;
            }
        }
        return i;
    }
};
```

## 两数之和

给定一个整数数组和一个目标值，找出数组中和为目标值的两个数。

你可以假设每个输入只对应一种答案，且同样的元素不能被重复利用。

**示例:**

给定 nums = [2, 7, 11, 15], target = 9

因为 nums[0] + nums[1] = 2 + 7 = 9 所以返回 [0, 1]

**解法：**

用一个map，key是元素值，value是idx 看新来的这个元素的目标值（tgt - nums[i]）在不在map里，在的话把它的value拿出来就行了。。

```c++
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

## 无重复字符的最长子串

给定一个字符串，找出不含有重复字符的最长子串的长度。

```
示例 1:
输入: "abcabcbb"
输出: 3 
解释: 无重复字符的最长子串是 "abc"，其长度为 3。

示例 2:
输入: "bbbbb"
输出: 1
解释: 无重复字符的最长子串是 "b"，其长度为 1。

示例 3:
输入: "pwwkew"
输出: 3

```

解释: 无重复字符的最长子串是 "wke"，其长度为 3。
请注意，答案必须是一个子串，"pwke" 是一个子序列 而不是子串。

**解答：**

* 用滑动窗口，最终要返回的size就是这个窗口的大小（j-i+1），而set只是为了存储这个窗口里的元素
* 对于j，如果在set中没找到这个元素s[j]，更新res，并把s[j]扔进set，再++j；
* 如果找到了，那么，说明s[j]在set里了，这时候需要把开头的元素s[i]从set里删了，把i++，窗口的开始往右移一格

```c++
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        set<char> set_char;
        int res = 0;
        int tmp = 0;
        for (int i = 0, j = 0; i < s.size() && j < s.size(); ) {
            if (set_char.find(s[j]) != set_char.end()) {
                set_char.erase(s[i]);
                ++i;
            } else {
                if (j - i + 1 > res) {
                    res = j - i + 1;
                }
                set_char.insert(s[j]);
                ++j;
            }
        }
        
        return res;
    }
};
```

## 两个排序数组的中位数

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

```c++
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        vector<int> tmp;
        int m = nums1.size();
        int n = nums2.size();
        int total_size = n + m;
        tmp.resize(total_size);
        int j = n - 1;
        int i = m - 1;
        while (j >= 0) {
            if (i < 0) {
                // 如果i数组遍历完了，要把j数据剩下的全部拷过来,记住是<j+1
                for(int k = 0; k < j + 1; ++k) {
                    tmp[k] = nums2[k];
                }
                break;
            }
            if (nums2[j] > nums1[i]) {
                tmp[i + j + 1] = nums2[j];
                j--;
            } else {
                tmp[i + j + 1] = nums1[i];
                i--;
            }
        }
        if (j < 0) {
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
};
```

方法2：二分查找

[https://leetcode-cn.com/problems/median-of-two-sorted-arrays/solution/xun-zhao-liang-ge-you-xu-shu-zu-de-zhong-wei-s-114/](https://leetcode-cn.com/problems/median-of-two-sorted-arrays/solution/xun-zhao-liang-ge-you-xu-shu-zu-de-zhong-wei-s-114/)


## 合并两个有序数组

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

提示中已经给出，假设array1有足够的空间了，于是我们不需要额外构造一个数组，并且可以**从后面**不断地比较元素进行合并。

+ 比较array2与array1中**最后面**的那个元素，把最大的插入第m+n位
+ 改变数组的索引，再次进行上面的比较，把最大的元素插入到array1中的第m+n-1位。
+ 循环一直到结束。循环结束条件：当index1或index2有一个小于0时，此时就可以结束循环了。如果index2小于0，说明目的达到了。如果index1小于0，就把array2中剩下的前面的元素都复制到array1中去就行。

```c++
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

## 数值的整数次方(offerNo16)--notdone

## 打印从1到最大的n位数(offerNo17)--notdone

## 正则表达式匹配(offerNo19)--notdone

## 表示数值的字符串(offerNo20)--notdone

## 调整数组顺序使奇数位于偶数前面(offerNo21)--notdone

## 顺时针打印矩阵(offerNo29)--notdone

## 包含min函数的栈(offerNo30)--notdone

## 栈的压入、弹出序列(offerNo31)--notdone

## 字符串的排列(offerNo38)--notdone

## 数组中出现次数超过一半的数字(offerNo39)--notdone

## 最小的k个数(offerNo40)--notdone

## 数据流中的中位数(offerNo41)--notdone

## 连续子数组的最大和(offerNo42)


HZ偶尔会拿些专业问题来忽悠那些非计算机专业的同学。今天测试组开完会后,他又发话了:在古老的一维模式识别中,常常需要计算连续子向量的最大和,当向量全为正数的时候,问题很好解决。但是,如果向量中包含负数,是否应该包含某个负数,并期望旁边的正数会弥补它呢？例如:{6,-3,-2,7,-15,1,2,2},连续子向量的最大和为8(从第0个开始,到第3个为止)。给一个数组，返回它的最大连续子序列的和，你会不会被他忽悠住？(子向量的长度至少是1)

**解答：**

动态规划：

dp[i]表示以元素num[i]为结尾的数组里，最大的和

dp[i] = max(dp[i - 1] + array[i], array[i]);

因为是连续子数组，所以当前数要放进去。

+ 如果dp[i-1]小于0，那么加上dp[i-1]后会变小，所以只取array[i]
+ 反之，array[i] + dp[i-1]

```c++
class Solution {
public:
    int FindGreatestSumOfSubArray(vector<int> array) {
        size_t len = array.size();
        vector<int> dp;
        dp.resize(len);
        dp[0] = array[0];
        int res = dp[0];// 不能=0，因为可能整个数组都是负的
        for (int i = 1; i < len; i++) {
            dp[i] = max(dp[i - 1] + array[i], array[i]);
            res = max(dp[i], res);
        }
        return res;
    }
};
```



## 1-n整数中1出现的次数(offerNo43)--notdone

## 数字序列中某一位的数字(offerNo44)--notdone

## 把数组排成最小的数(offerNo45)--notdone

## 把数字翻译成字符串(offerNo46)--notdone

## 礼物的最大价值(offerNo47)--notdone

## 最长不含重复字符的子字符串(offerNo48)--notdone

## 丑数(offerNo49)--notdone

## 第一个只出现一次的字符(offerNo50)--notdone

## 数组中的逆序对(offerNo51)--notdone

## 在排序数组中查找数字(offerNo53)--notdone

## 数组中数字出现的次数(offerNo56)--notdone

## 和为s的数字(offerNo57)--notdone

## 翻转字符串(offerNo58)--notdone

## 队列的最大值(offerNo59)--notdone

## 求1+2+...+n(offerNo64)--notdone

## 不用加减乘除做加法(offerNo65)--notdone

## 构造乘积数组(offerNo66)--notdone

## 把字符串转换成整数(offerNo67)--notdone

# 链表

## 从头到尾打印一个链表(offerNo6)

输入一个链表，按链表值从尾到头的顺序返回一个ArrayList。

解析：

直接按顺序扔到一个vec里，然后返回前调用```std::reverse```把这个vec反转一下

```c++
/**
*  struct ListNode {
*        int val;
*        struct ListNode *next;
*        ListNode(int x) :
*              val(x), next(NULL) {
*        }
*  };
*/
class Solution {
public:
    vector<int> printListFromTailToHead(ListNode* head) {
        vector<int> vec;
        while (head != NULL) {
            vec.emplace_back(head->val);
            head = head->next;
        }
        std::reverse(vec.begin(), vec.end());
        return vec;
    }
};
```

## 环形链表

给定一个链表，判断链表中是否有环。

**分析：**

**方法一：哈希表**

检查一个结点此前是否被访问过来判断链表。常用的方法是使用哈希表。

我们遍历所有结点并在哈希表中存储每个结点的引用（或内存地址）。如果当前结点为空结点 null（即已检测到链表尾部的下一个结点），那么我们已经遍历完整个链表，并且该链表不是环形链表。如果当前结点的引用已经存在于哈希表中，那么返回 true（即该链表为环形链表）。

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool hasCycle(ListNode *head) {
        set<ListNode*> set_link;
        ListNode* p = head;
        while (p != NULL) {
            if (set_link.find(p) != set_link.end()) {
                return true;
            }
            set_link.insert(p);
            p = p->next;
        }
        return false;
    }
};
```

**方法二：双指针**

使用具有 不同速度 的快、慢两个指针遍历链表，空间复杂度可以被降低至 O(1)O(1)。慢指针每次移动一步，而快指针每次移动两步。

如果列表中不存在环，最终快指针将会最先到达尾部，此时我们可以返回 false

时间复杂度的分析见[https://leetcode-cn.com/problems/linked-list-cycle/solution/](https://leetcode-cn.com/problems/linked-list-cycle/solution/)

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool hasCycle(ListNode *head) {
        if (head == NULL || head->next == NULL) {
            return false;
        }
        ListNode* fast = head->next;// fast初始化为next，起点就比slow快了
        ListNode* slow = head;
        while(fast != slow) {
            if (fast == NULL || fast->next == NULL) {
                // 如果fast到终点了，或者fast的下一个节点是终点，说明slow肯定追不上来了
                return false;
            }
            slow = slow->next;
            fast = fast->next->next;
        }
        return true;
    }
};
```

## 删除链表中的节点(offerNo18)--maybedone

请编写一个函数，使其可以删除某个链表中**给定的（非末尾）**节点，输入的是要求被删除的节点的值。

示例 1:

```
输入: head = [4,5,1,9], node = 5
输出: [4,1,9]
解释: 给定你链表中值为 5 的第二个节点，那么在调用了你的函数之后，该链表应变为 4 -> 1 -> 9.
```

示例 2:

```
输入: head = [4,5,1,9], node = 1
输出: [4,5,9]
解释: 给定你链表中值为 1 的第三个节点，那么在调用了你的函数之后，该链表应变为 4 -> 5 -> 9.
```

说明：

+ 链表至少包含两个节点。
+ 链表中所有节点的值都是唯一的。
+ 给定的节点为非末尾节点并且一定是链表中的一个有效节点。
+ 不要从你的函数中返回任何结果。


**解答：**

正常的是例如1->2->3->4->5，想把3给删了，那么我们可以让2指向4。

但这题传入的就是3，我们没法拿到2。所以要稍微改一下：

把4的值赋给3，然后让3指向5。

这样就相当于把4前移了到3的位置，然后把4删了。。成立的前提是，我们要删除的节点不是末尾。

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    void deleteNode(ListNode* node) {
        node->val = node->next->val;
        node->next = node->next->next;
    }
};
```

## 删除排序链表中的重复元素

给定一个排序链表，删除所有重复的元素，使得每个元素只出现一次。

```
示例 1:

输入: 1->1->2
输出: 1->2
示例 2:

输入: 1->1->2->3->3
输出: 1->2->3
```

**解答：**

**方法一：set+双指针**
双指针，记得理清楚什么时候两个指针后移就行，记得用new ListNode(xx)，还有insert的时间点

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == NULL) {
            return NULL;
        }
        ListNode* res = new ListNode(head->val);
        ListNode* j = head->next;
        ListNode* i = res;
        set<int> set_v;
        set_v.insert(head->val);
        for (; j != NULL; j = j->next) {
            cout << j->val << "xx" << endl;
            if (set_v.find(j->val) == set_v.end()) {
                cout << j->val << "xx2" << endl;
                i->next = new ListNode(j->val);
                i = i->next;
                set_v.insert(j->val);
            }
        }
        return res;
    }
};
```

方法二：

考虑到这题限制了是排序数组，所以其实可以不用set，重复的数字是连续出现的。。。而且，连new都不用，直接在原链表上改next就行，如果next=当前值，就把next指向next的next

注意：只有当next!=当前值时，才i = i->next；不然超过两个连续的重复就干不掉了，例如[1,1,1,1,2]

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* i = head;
        while (i != NULL && i->next != NULL) {
            if(i->val == i->next->val) {
                i->next = i->next->next;
            } else {
                i = i->next;
            }
        }
        return head;
    }
};
```

## 两数相加

给定两个非空链表来表示两个非负整数。位数按照逆序方式存储，它们的每个节点只存储单个数字。将两数相加返回一个新的链表。

你可以假设除了数字 0 之外，这两个数字都不会以零开头。

**示例：**

```
输入：(2 -> 4 -> 3) + (5 -> 6 -> 4)
输出：7 -> 0 -> 8
原因：342 + 465 = 807
```

**解答：**

* 搞一个dummyhead，然后每一次while的时候，填充他的next，最后返回出是dummyhead的next
* 要x->next之前先判断x!=NULL(不是判断x->next!=NULL)
* while的条件是或，处理两个链表不等长的情况
* while外面，如果还有carry，要再new一个

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int carry = 0;
        ListNode* dummy_head = new ListNode(0);
        ListNode* tmp = dummy_head;
        ListNode* ptr1 = l1;
        ListNode* ptr2 = l2;
        while (ptr1 != NULL || ptr2 != NULL) {
            int val1 = ptr1 != NULL? ptr1->val: 0;
            int val2 = ptr2 != NULL? ptr2->val: 0;
            int sum = val1 + val2 + carry;
            //cout << sum << " " << carry << " " << val1 << " " << val2 << endl;
            carry = sum / 10;
            int remain = sum % 10;
            tmp->next = new ListNode(remain);
            ptr1 = (NULL == ptr1? NULL: ptr1->next);
            ptr2 = (NULL == ptr2? NULL: ptr2->next);
            tmp = tmp->next;
        }
        if (carry > 0) {
            tmp->next = new ListNode(carry);
        }
        return dummy_head->next;
    }
};
```

## 链表中倒数第k个节点(offerNo22)--notdone

## 链表中环的入口节点(offerNo23)--notdone

## 反转链表(offerNo24)--notdone

## 合并两个排序的链表(offerNo25)--notdone

## 复杂链表的复制(offerNo35)--notdone

## 两个链表的第一个公共节点(offerNo52)--notdone

# 树

## 前序遍历

根-》左-》右这样遍历

递归：

```c++
/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> res;
    void helper(TreeNode* root) {
        if (root == NULL) return ;
        res.push_back(root->val);
        helper(root->left);
        helper(root->right);
    }
     
    vector<int> preorderTraversal(TreeNode *root) {
        helper(root);
        return res;
    }
};
```

非递归：

使用栈：

方法1：

注意，先扔右子树再扔左子树，因为栈是后进先出，前序是先左再右。但是这种方法好像会爆内存…

+ push根，
+ while栈不空：pop栈顶，输出数字，push**栈顶右孩子**，push**栈顶左孩子**

```c++
class Solution {
public:
    vector<int> preorderTraversal(TreeNode *root) {
        vector<int> res;
        stack<TreeNode *> s;
        if (root == NULL){
            return res;
        }
        s.push(root);
        while (!s.empty()){
            TreeNode *cur = s.top();
            s.pop();
            res.push_back(cur->val);
            if (cur->right!=NULL)
                s.push(cur->right);
            if (cur->left!=NULL)
                s.push(cur->left);
        }
        return res;
    }
};
```

方法2：

不是非常非常懂。。先记着

```c++
/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> preorderTraversal(TreeNode *root) {
        vector<int> preorder;
        stack<TreeNode*> st;
        TreeNode *p = root;
        while (p || !st.empty()) {
            if (p) {
                preorder.push_back(p->val);
                st.push(p);
                p=p->left;
            } else {
                p=st.top();
                st.pop();
                p=p->right;
            }
        }
        return preorder;
    }
};
```



## 后序遍历

左-》右-》根

递归：

```c++
/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    void postOrder(TreeNode *root, vector<int>& vec){
        if (root != NULL) {
            postOrder(root->left, vec);
            postOrder(root->right, vec);
            vec.push_back(root->val);
        }
    }
    vector<int> postorderTraversal(TreeNode *root) {
        vector<int> vec;
        postOrder(root, vec);
        return vec;  
    }
};
```

非递归：

方法1：

参考非递归的前序遍历，然后做如下改动：

前序遍历 根->左->右 变成 根->右->左 结果再reverse一下

```c++
/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> postorderTraversal(TreeNode *root) {
       vector<int> res;
       if(!root)
           return res;
       stack<TreeNode*> st;
       st.push(root);
       TreeNode *temp;
       while( st.size()) {
           temp = st.top();
           st.pop();
           res.push_back(temp->val);
           if (temp->left) {
               st.push(temp->left);
           }
           if (temp->right) {
               st.push(temp->right);
           }
       }
       std::reverse(res.begin(),res.end());
       return res;
    }
};
```

方法2：

先从根往左一直入栈，直到为空，然后判断栈顶元素的右孩子，如果不为空且未被访问过，则从它开始重复左孩子入栈的过程；否则说明此时栈顶为要访问的节点（因为左右孩子都是要么为空要么已访问过了），出栈然后访问即可，接下来再判断栈顶元素的右孩子...直到栈空。

```c++
/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> postorderTraversal(TreeNode *root) {
        vector<int> postorder;
        stack<TreeNode*> st;
        TreeNode *p = root;
        TreeNode *r = NULL;// r用来记录上一次访问的节点
        while (p || !st.empty()) {
            if (p) { //左孩子一直入栈，直到左孩子为
                st.push(p);
                p=p->left;
            } else {
                p=st.top();
                p = p->right;
                if (p!=NULL && p != r) {
                    //如果栈顶元素的右孩子不为空，且未被访问
                    //则右孩子进栈，
                    //然后重复左孩子一直进栈直到为空的过程
                    st.push(p);
                    p = p->left;
                } else {
                    //否则取出栈顶元素，放到结果数组中，
                    //然后pop，
                    //r记录刚刚访问的节点
                    p = st.top();
                    postorder.push_back(p->val);
                    st.pop();
                    r = p;
                    p = NULL;
                }
            }
        }
        return postorder;
    }
};
```

## 重建二叉树(offerNo7)

输入某二叉树的**前序遍历**和**中序遍历**的结果，请**重建**出该二叉树。假设输入的前序遍历和中序遍历的结果中都**不含重复的数字**。例如输入前序遍历序列{1,2,4,7,3,5,6,8}和中序遍历序列{4,7,2,1,5,3,8,6}，则重建二叉树并返回。


思路：

+ 创建根节点，根节点肯定是前序遍历的第一个数，new一个head节点，值是根
+ 把根节点在中序遍历结果的『第几位』存放于变量root中
+ 对于中序遍历，根节点左边的节点位于二叉树的左边，根节点右边的节点位于二叉树的右边。所以
    + 把根节点左边的元素（i->root-1）依次扔到left_in数组中，作为左子树的中序遍历结果；
    + 把(i+1->root-1)的元素扔到left_pre这个数组中，当做左子树的前序遍历结果
+ 同样地：
    + 把根节点右边的元素（root+1->inlen）依次扔到right_in数组中，作为右子树的中序遍历结果；
    + 把(i->inlen)的元素扔到right_pre这个数组中，当做右子树的前序遍历结果
+ head->left就是递归left_pre,left_in的返回结果
+ head->right就是递归rightt_pre,right_in的返回结果
+ 返回head

```c++
/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> vin) {
        int inlen = vin.size();
        if(inlen == 0)
            return NULL;
        vector<int> left_pre, right_pre, left_in, right_in;
        // 创建根节点，根节点肯定是前序遍历的第一个数
        TreeNode* head = new TreeNode(pre[0]);
        // 找到中序遍历根节点所在位置,存放于变量root中
        int root = 0;
        for(int i=0; i < inlen; i++) {
            if (vin[i] == pre[0]) {
                root = i;
                break;
            }
        }
        // 对于中序遍历，根节点左边的节点位于二叉树的左边，根节点右边的节点位于二叉树的右边
        // 利用上述这点，对二叉树节点进行归并
        for(int i = 0; i < root; i++) {
            left_in.push_back(vin[i]);
            left_pre.push_back(pre[i + 1]);//前序第一个为根节点
        }
        for(int i = root + 1; i < inlen; i++) {
            right_in.push_back(vin[i]);
            right_pre.push_back(pre[i]);
        }
        //和shell排序的思想类似，取出前序和中序遍历根节点左边和右边的子树
        //递归，再对其进行上述所有步骤，即再区分子树的左、右子子数，直到叶节点
        head->left = reConstructBinaryTree(left_pre, left_in);
        head->right = reConstructBinaryTree(right_pre, right_in);
        return head;
    }
};
```

## 二叉树的下一个节点(offerNo8)--notdone

## 对称的二叉树(offerNo28)--maybedone

给定一个二叉树，检查它是否是镜像对称的。

例如，二叉树 [1,2,2,3,4,4,3] 是对称的。

```
    1
   / \
  2   2
 / \ / \
3  4 4  3
```

但是下面这个 [1,2,2,null,3,null,3] 则不是镜像对称的:

```
    1
   / \
  2   2
   \   \
   3    3
```

**解答**：

方法一：递归

如果同时满足下面的条件，两个树互为镜像：

* 它们的两个根结点具有相同的值。
* 每个树的右子树都与另一个树的左子树镜像对称。

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool isMirror(TreeNode* t1, TreeNode* t2) {
        if (t1 == NULL && t2 == NULL) return true;
        // 如果两个不都是NULL，这个时候，如果一个是NULL,另一个不是，那么肯定不镜像！！
        // 如果两个都不是NULL,那还有可能，可以等下一次递归
        if (t1 == NULL || t2 == NULL) return false;
        return (t1->val == t2->val &&
               isMirror(t1->left, t2->right) &&
               isMirror(t1->right, t2->left));
    }
    bool isSymmetric(TreeNode* root) {
        return isMirror(root, root);
    }
};
```

方法二：迭代

利用**队列**进行迭代

队列中每两个连续的结点应该是相等的，而且它们的子树互为镜像。最初，队列中包含的是 root 以及 root。该算法的工作原理类似于 BFS，但存在一些关键差异。每次提取两个结点并比较它们的值。然后，将两个结点的左右子结点按**相反的顺序**插入队列中(即t1->left, t2->right, t1->right, t2->left)。

当队列为空时，或者我们检测到树不对称（即从队列中取出**两个不相等的连续结点**）时，该算法结束。

注意，c++的queue的front不会pop，要手动pop

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        queue<TreeNode*> q;
        q.push(root);
        q.push(root);
        while (!q.empty()) {
            TreeNode* t1 = q.front();
            q.pop();
            TreeNode* t2 = q.front();
            q.pop();
            if (t1 == NULL && t2 == NULL) continue;
            if (t1 == NULL || t2 == NULL) return false;
            if (t1->val != t2->val) return false;
            q.push(t1->left);
            q.push(t2->right);
            q.push(t1->right);
            q.push(t2->left);
        }
        return true;
    }
};
```

## 二叉树的最大深度--maybedone(offerNo55)

给定一个二叉树，找出其最大深度。

二叉树的深度为根节点到最远叶子节点的最长路径上的节点数。

说明: 叶子节点是指没有子节点的节点。

示例：
给定二叉树 [3,9,20,null,null,15,7]，

```
    3
   / \
  9  20
    /  \
   15   7
```

返回它的最大深度 3 。

**解答：**

方法一：递归

每往下一层就加1，体现在走完左右子树的时候，return的时候加1，只有这样，最终的深度才会体现出来。。只有一个节点的时候，深度是1。

时间复杂度O(N), N为节点总数，因为需要遍历所有节点

空间复杂度：在最糟糕的情况下，树是完全不平衡的，例如每个结点只剩下左子结点，递归将会被调用 N 次，因此保持调用栈的存储将是O(N)。但在最好的情况下（树是完全平衡的），树的高度将是 log(N)。因此，在这种情况下的空间复杂度将是O(log(N))。

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    
    int maxDepth(TreeNode* root) {
        if (root == NULL) {
            return 0;
        } else {
            int left_height = maxDepth(root->left);
            int right_height = maxDepth(root->right);
            return std::max(left_height, right_height) + 1; // 每往下一层就要加1
        }
    }
};
```

方法2：**迭代（栈）**

使用 **DFS** 策略访问每个结点，同时在**每次访问时更新最大深度。**

从包含根结点且相应深度为 1 的栈开始。然后我们继续迭代：将当前结点弹出栈并推入子结点。每一步都会更新深度。

注意，push的时候是cur_depth + 1，而非depth+1

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    
    int maxDepth(TreeNode* root) {
        stack<std::pair<TreeNode*, int> > st;
        if (root != NULL) {
            st.push(std::make_pair(root, 1));
        }
        int depth = 0;
        while (!st.empty()) {
            std::pair<TreeNode*, int> a = st.top();
            TreeNode* cur_root = a.first;
            int cur_depth = a.second;
            st.pop();
            if (cur_root != NULL) {
                depth = std::max(depth, cur_depth);
                st.push(std::make_pair(cur_root->left, cur_depth + 1));
                st.push(std::make_pair(cur_root->right, cur_depth + 1));
            }
        }
        return depth;
    }
};
```

## 二叉树的最近公共祖先(offerNo68)

参考[https://blog.csdn.net/wangls56/article/details/88783783](https://blog.csdn.net/wangls56/article/details/88783783)

递归

```c++
TreeNode findAncestor(TreeNode root, TreeNode node1, TreeNode node2) {
    if (root == null) return null;
    if (root == node1 || root == node2) return root;
    TreeNode left  = findAncestor(root.left,  node1, node2);
    TreeNode right = findAncestor(root.right, node1, node2);
    if (left != null && right != null) return root;
    return right == null ? left : right;
}
```

如果有指向父节点的指针，可以转化成两个链表求第一个交点的问题。

## 树的子结构(offerNo26)--notdone

## 二叉树的镜像(offerNo27)--notdone

## 从上到下打印二叉树(offerNo32)--notdone

## 二叉搜索树的后序遍历序列(offerNo33)--notdone

## 二叉树中和为某一值的路径(offerNo34)--notdone

## 二叉搜索树与双向链表(offerNo36)--notdone

## 序列化二叉树(offerNo37)--notdone

## 二叉搜索树的第k大节点(offerNo54)--notdone

## 二叉树的深度(offerNo55)--notdone

# 递归法

## 斐波那契数列(offerNo10)--notdone

# 回溯法

[https://greyireland.gitbook.io/algorithm-pattern/suan-fa-si-wei/backtrack](https://greyireland.gitbook.io/algorithm-pattern/suan-fa-si-wei/backtrack)

回溯法（backtrack）常用于遍历列表所有子集，是DFS深度搜索一种，一般用于**全排列**，穷尽所有可能，遍历的过程实际上是一个决策树的遍历过程。**时间复杂度一般O(N!)**，它**不像动态规划存在重叠子问题**可以优化，回溯算法就是**纯暴力穷举**，复杂度一般都很高。

## 子集问题(leetcode78)

[https://leetcode-cn.com/problems/subsets/solution/zi-ji-by-leetcode/](https://leetcode-cn.com/problems/subsets/solution/zi-ji-by-leetcode/)

leetcode78: [https://leetcode-cn.com/problems/subsets/](https://leetcode-cn.com/problems/subsets/)

给定一组不含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。

说明：解集不能包含重复的子集。

```
输入: nums = [1,2,3]
输出:
[
  [3],
  [1],
  [2],
  [1,2,3],
  [1,3],
  [2,3],
  [1,2],
  []
]
```

观察全排列/组合/子集问题，它们比较相似，且可以使用一些通用策略解决。

首先，它们的解空间非常大：

+ 全排列：$$N!$$。
+ 组合：$$N!$$。
+ 子集：$$2^N$$，每个元素都可能存在或者不存在。

在它们的指数级解法中，要确保生成的**结果完整**且**无冗余**，有三种常用的方法：

+ 递归
+ 回溯
+ 基于**二进制位掩码**和对应位掩码之间的映射字典生成排列/组合/子集

相比前两种方法，第三种方法将每种情况都简化为二进制数，易于实现和验证。此外，第三种方法具有最优的时间复杂度，可以生成按照字典顺序的输出结果。

### 子集问题递归解法

![](assets/recursion.png)


## 矩阵中的路径(offerNo12)--notdone

## 机器人的运动范围(offerNo13)--notdone


# 图

# 动态规划

## 剪绳子(offerNo14)--notdone

# 位运算

## 二进制中1的个数(offerNo15)--notdone

# 模拟题

## 杨辉三角

在杨辉三角中，每个数是它左上方和右上方的数的和。

```
示例:

输入: 5
输出:
[
     [1],
    [1,1],
   [1,2,1],
  [1,3,3,1],
 [1,4,6,4,1]
]
```

**解答**：

1. i从1开始，到<numRows +1
2. j从0开始，到<i
3. j=0|| i-1时，直接放1
4. else，放```res[i-2][j-1]+res[i-2][j]```

```c++
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> res;
        
        for (size_t i = 1; i < numRows + 1; ++i) {
            vector<int> sub_res;
            size_t j = 0;
            while (j < i) {
                //cout << i << "xxxx" << j << endl;
                if (j == 0 || j == i - 1) {
                    sub_res.emplace_back(1);
                } else {
                    //cout << i << "x" << j << endl;
                    sub_res.emplace_back(res[i - 2][j - 1] + res[i - 2][j]);
                }
                ++j;
            }
            res.emplace_back(sub_res);
        }
        return res;
    }
};
```

## 买卖股票的最佳时机

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

+ minprice ：**迄今为止**所得到的**最小的谷值**。初始化为int_max，如果当前价格有比它小，那就更新它为当前价格
+ maxprofit，**迄今为止**所得到的**最大的利润**（卖出价格与最低价格之间的最大差值）。如果当前价格与minprice的差比它大，那就更新它

```c++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int minprice = INT_MAX;
        int maxprofit = 0;
        for (int i = 0; i < prices.size(); ++i) {
            if (prices[i] < minprice) {
                minprice = prices[i];
            } else if (prices[i] - minprice > maxprofit) {
                maxprofit = prices[i] - minprice;
            }
        }
        return maxprofit;
    }
};
```

## 买卖股票的最佳时机 II

给定一个数组，它的第 i 个元素是一支给定股票第 i 天的价格。

设计一个算法来计算你所能获取的最大利润。你可以尽可能地完成更多的交易（多次买卖一支股票）。

注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

```
示例 1:

输入: [7,1,5,3,6,4]
输出: 7
解释: 在第 2 天（股票价格 = 1）的时候买入，在第 3 天（股票价格 = 5）的时候卖出, 
    这笔交易所能获得利润 = 5-1 = 4 。
     随后，在第 4 天（股票价格 = 3）的时候买入，在第 5 天（股票价格 = 6）的时候卖出, 
     这笔交易所能获得利润 = 6-3 = 3 。
示例 2:

输入: [1,2,3,4,5]
输出: 4
解释: 在第 1 天（股票价格 = 1）的时候买入，在第 5 天 （股票价格 = 5）的时候卖出, 
     这笔交易所能获得利润 = 5-1 = 4 。
     注意你不能在第 1 天和第 2 天接连购买股票，之后再将它们卖出。
     因为这样属于同时参与了多笔交易，你必须在再次购买前出售掉之前的股票。
示例 3:

输入: [7,6,4,3,1]
输出: 0
解释: 在这种情况下, 没有交易完成, 所以最大利润为 0。
```


**解答：**

方法一：

我们的兴趣点是连续的峰和谷。

关键是我们需要考虑到紧跟谷的每一个峰值以最大化利润。如果我们试图跳过其中一个峰值来获取更多利润，那么我们最终将失去其中一笔交易中获得的利润，从而导致总利润的降低。

$$totalprofit=\sum_i{height(peak_i)-height(valley_i)}$$

例如，在上述情况下，如果我们跳过$$peak_i$$和$$valley_j$$。试图通过考虑差异较大的点以获取更多的利润，获得的净利润总是会小与包含它们而获得的静利润，因为 C 总是小于 A+B。

时间复杂度：O(n)。遍历一次。

空间复杂度：O(1)。需要常量的空间。 

```c++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int i = 0;
        if (prices.size() == 0) return 0;
        int valley = prices[0];
        int peak = prices[0];
        int maxprofit = 0;
        while (i < prices.size() - 1) {
            while (i < prices.size() - 1 && prices[i] >= prices[i + 1])
                i++;
            valley = prices[i];
            while (i < prices.size() - 1 && prices[i] <= prices[i + 1])
                i++;
            peak = prices[i];
            maxprofit += peak - valley;
        }
        return maxprofit;
    }
};
```

方法二：

该解决方案遵循 方法一 的本身使用的逻辑，但有一些轻微的变化。在这种情况下，我们可以简单地继续在斜坡上爬升并持续增加从连续交易中获得的利润，而不是在谷之后寻找每个峰值。最后，我们将有效地使用峰值和谷值，但我们不需要跟踪峰值和谷值对应的成本以及最大利润，但我们可以直接继续增加加数组的连续数字之间的差值，如果第二个数字大于第一个数字，我们获得的总和将是最大利润。

时间复杂度：O(n)。遍历一次。

空间复杂度：O(1)。需要常量的空间。

```c++
class Solution {
public:
     int maxProfit(vector<int>& prices) {
        int maxprofit = 0;
        for (int i = 1; i < prices.size(); i++) {
            if (prices[i] > prices[i - 1])
                maxprofit += prices[i] - prices[i - 1];
        }
        return maxprofit;
    }
};
```

## 棒球比赛

给定一个字符串列表，每个字符串可以是以下四种类型之一：

1. 整数（一轮的得分）：直接表示您在本轮中获得的积分数。
2. "+"（一轮的得分）：表示本轮获得的得分是**前两轮有效**回合得分的总和。
3. "D"（一轮的得分）：表示本轮获得的得分是**前一轮有效**回合得分的**两倍**。
4. "C"（一个操作，这不是一个回合的分数）：表示您获得的**最后一个有效回合的分数是无效的**，应该被**移除**。

每一轮的操作都是永久性的，可能会对前一轮和后一轮产生影响。
你需要返回你在所有回合中得分的总和。

示例：

```
输入: ["5","-2","4","C","D","9","+","+"]
输出: 27
解释: 
第1轮：你可以得到5分。总和是：5。
第2轮：你可以得到-2分。总数是：3。
第3轮：你可以得到4分。总和是：7。
操作1：第3轮的数据无效。总数是：3。
第4轮：你可以得到-4分（第三轮的数据已被删除）。总和是：-1。
第5轮：你可以得到9分。总数是：8。
第6轮：你可以得到-4 + 9 = 5分。总数是13。
第7轮：你可以得到9 + 5 = 14分。总数是27。
```

注意：

+ 输入列表的大小将介于1和1000之间。
+ 列表中的每个整数都将介于-30000和30000之间。

**解法**：

使用**栈**！！！因为我们只处理涉及最后或倒数第二轮的操作。

1. c++11里的string和各种数值类型的互转：[http://www.cnblogs.com/gtarcoder/p/4925592.html](http://www.cnblogs.com/gtarcoder/p/4925592.html)
1. 如果是数字，就push进去
1. 如果是C，就pop掉top，因为这个stack只存『有效的』
1. 如果是D，就把top乘以2，push进去（因为这个stack只存『有效的』）
1. 如果是+，计算top两个元素的和，当做这轮的得分，扔进去（注意，前面几轮的得分不能变，而因为是栈，所以我们先把top给pop出来，算原来两个top的和得到新的top，然后把原来的top扔回去，再把新的top扔进去。。。）
1. stack没有迭代器，不能被遍历。。。所以只能一个个pop出来

```c++
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
```

## 柠檬水找零

在柠檬水摊上，每一杯柠檬水的售价为 5 美元。

顾客排队购买你的产品，（按账单 bills 支付的顺序）一次购买一杯。

每位顾客只买一杯柠檬水，然后向你付 5 美元、10 美元或 20 美元。你必须给每个顾客正确找零，也就是说净交易是每位顾客向你支付 5 美元。

注意，一开始你手头没有任何零钱。

如果你能给每位顾客正确找零，返回 true ，否则返回 false 。

```
示例 1：

输入：[5,5,5,10,20]
输出：true
解释：
前 3 位顾客那里，我们按顺序收取 3 张 5 美元的钞票。
第 4 位顾客那里，我们收取一张 10 美元的钞票，并返还 5 美元。
第 5 位顾客那里，我们找还一张 10 美元的钞票和一张 5 美元的钞票。
由于所有客户都得到了正确的找零，所以我们输出 true。
示例 2：

输入：[5,5,10]
输出：true
示例 3：

输入：[10,10]
输出：false
示例 4：

输入：[5,5,10,10,20]
输出：false
解释：
前 2 位顾客那里，我们按顺序收取 2 张 5 美元的钞票。
对于接下来的 2 位顾客，我们收取一张 10 美元的钞票，然后返还 5 美元。
对于最后一位顾客，我们无法退回 15 美元，因为我们现在只有两张 10 美元的钞票。
由于不是每位顾客都得到了正确的找零，所以答案是 false。
```

限制：

+ 0 <= bills.length <= 10000
+ ```bills[i]``` 不是 5 就是 10 或是 20 

解答：

用两个变量，分别表示5块和10块的个数。因为20块没用。。找不出去

```c++
class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        int five = 0;
        int ten = 0;
        for (auto& i: bills) {
            if (i == 5) {
                five++;
            } else if (i == 10) {
                if (five > 0) {
                    five--;
                    ten++;
                } else {
                    return false;
                }
            } else {
                if (five > 0 && ten > 0) {
                    five--;
                    ten--;
                    
                } else if (five >=3 ) {
                    five -=3;
                } else {
                    return false;
                }
            }
        }
        return true;
    }
};
```

## n个骰子的点数(offerNo60)--notdone

## 扑克牌中的顺子(offerNo61)--notdone

## 圆圈中最后剩下的数字(offerNo62)--notdone

## 股票的最大利润(offerNo63)--notdone
