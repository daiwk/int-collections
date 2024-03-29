# 基础知识

主要是剑指offer相关的题

## 大小写

A的ascii码：65
a的ascii码：97

小写转大写：a-32; 大写转小写：a+32

## 进制转换

输入十六进制数，输出10进制数：

例如输入0xA，输出10

```cpp
    int a;
    while (cin >> hex >> a) {
        cout << a << endl;
    }
```


# cpp基础

## 实现单例模式

参考[https://www.cnblogs.com/qiaoconglovelife/p/5851163.html](https://www.cnblogs.com/qiaoconglovelife/p/5851163.html)

### 线程不安全版本的经典实现(懒汉实现)

+ **构造函数**声明为**private或protect**防止被外部函数实例化
+ 内部保存一个**private static的类指针p**保存唯一的实例
+ 由一个**public**的类方法 **(instance函数)**返回单例类唯一的**static实例指针**
+ 全局范围内给p赋**初始值NULL**
+ insance函数里判断指针p是否为NULL，如果是就new一个，反之直接return p
+ 构造函数是空的

如果两个线程同时首次调用instance方法且**同时检测到p是NULL值**，则两个线程会**同时构造一个实例给p**，因此是线程不安全的！！但如果放在进程级的初始化是不是也行。。。

```cpp
class SingletonLazy
{
protected:
    SingletonLazy(){}
private:
    static SingletonLazy* p;
public:
    static SingletonLazy* instance();
};
SingletonLazy* SingletonLazy::p = NULL;
SingletonLazy* SingletonLazy::instance()
{
    if (p == NULL)
        p = new SingletonLazy();
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

```cpp
class SingletonLazyLock
{
protected:
    SingletonLazyLock()
    {
        pthread_mutex_init(&mutex, NULL);
    }
private:
    static SingletonLazyLock* p;
public:
    static pthread_mutex_t mutex;
    static SingletonLazyLock* instance();
};

pthread_mutex_t SingletonLazyLock::mutex;
SingletonLazyLock* SingletonLazyLock::p = NULL;
SingletonLazyLock* SingletonLazyLock::instance()
{
    if (p == NULL)
    {
        pthread_mutex_lock(&mutex);
        if (p == NULL)
            p = new SingletonLazyLock();
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

```cpp
class SingletonLazyLockNoPtr
{
protected:
    SingletonLazyLockNoPtr()
    {
        pthread_mutex_init(&mutex_noptr, NULL);
    }
public:
    static pthread_mutex_t mutex_noptr;
    static SingletonLazyLockNoPtr* instance();
    int a;
};

pthread_mutex_t SingletonLazyLockNoPtr::mutex_noptr;
SingletonLazyLockNoPtr* SingletonLazyLockNoPtr::instance()
{
    pthread_mutex_lock(&mutex_noptr);
    static SingletonLazyLockNoPtr obj;
    pthread_mutex_unlock(&mutex_noptr);
    return &obj;
}
```

### 不用加锁的饿汉版本实现

+ **构造函数**声明为**private或protect**防止被外部函数实例化
+ 内部保存一个**private static的类指针p**保存唯一的实例
+ 由一个**public**的类方法 **(instance函数)**返回单例类唯一的**static实例指针**，实现时**直接返回p**
+ 全局范围内**new一个对象给p**

```cpp
class SingletonHungry
{
protected:
    SingletonHungry()
    {}
private:
    static SingletonHungry* p;
public:
    static SingletonHungry* instance();
};
SingletonHungry* SingletonHungry::p = new SingletonHungry();
SingletonHungry* SingletonHungry::instance()
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


```cpp
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
    + 当两个指针相遇时结束(不一定要到头！！)

其中，```char*str```，直接用下标来取就行```str[xxlength]```，所以上面说的两个指针，其实就是两个下标~！


```cpp
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
            if (str[old_len] == ' ') {
                space_cnt++;
            }
            old_len++;
        }
        new_len = old_len + 2 * space_cnt;
        if (new_len > length) {
            return;
        }
        int pOldlength = old_len; //注意不要减一因为隐藏个‘\0’也要算里
        int pNewlength = new_len;
        while (pOldlength >= 0 && pNewlength > pOldlength) {// 相遇时结束
            if (str[pOldlength] == ' ') {
                str[pNewlength--] = '0';
                str[pNewlength--] = '2';
                str[pNewlength--] = '%';
            } else {//不是空格就把pOldlength指向的字符装入pNewlength指向的位置
                str[pNewlength--] = str[pOldlength];
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

```cpp
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

# 数组、栈、队列

## 旋转数组的最小数字（offerNo11）

把一个数组**最开始的若干个元素搬到数组的末尾**，我们称之为数组的旋转。 输入一个**非减排序**的数组的一个旋转，输出旋转数组的最小元素。 例如数组{3,4,5,1,2}为{1,2,3,4,5}的一个旋转，该数组的最小值为1。 NOTE：给出的所有元素都大于0，若数组大小为0，请返回0。

旋转之后的数组实际上可以划分成**两个有序的子数组**：**前面子数组**的大小**都大于后面子数组**中的元素

实际上**最小的元素就是两个子数组的分界线**。


方法一：直接找到后一个数比上一个小的位置，那这后一个数就是我们要的了：

```cpp
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

```cpp
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

[https://leetcode.cn/problems/yong-liang-ge-zhan-shi-xian-dui-lie-lcof/](https://leetcode.cn/problems/yong-liang-ge-zhan-shi-xian-dui-lie-lcof/)

```cpp
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
        // 要判断下，如果没数据，就返回-1
        if (stack2.empty()) { 
            return -1;
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

没有任何重复的情况下，数组的每个下标i处存放的就是i值，这是“正确 ”的位置；

有重复，遍历时，前面的重复元素会放到它“正确”的位置上，后面一个重复元素在想要也放到该位置时，发现该位置已有“正确”元素了，即判断重复。

写的时候注意：要交换i，j元素的时候，i的值更新了还需要在下一次遍历中判断，**此时i指针不动，只有当值在“正确”位置时，才将i右移一位**

```cpp
    int findRepeatNumber(vector<int>& nums) {
        int i = 0;
        while (i < nums.size()) {
            if (nums[i] == i) {
                ++i;
                continue;
            }
            if (nums[i] == nums[nums[i]]) {
                return nums[i];
            }
            swap(nums[i], nums[nums[i]]);
        }
        return -1;
    }
```

### 重复数字变种

长度为n+1的数组中，所有数字都是1~n，所以至少有一个重复，要求不能修改输入数组，找出任意一个重复数字

解法：

二分的思想，数字是1~n，那么分成两半，各x个，算一下左边那一半在这个数组里出现的次数，如果比x大，说明重复数字出现在这个区间里，否则在另一个区间里。

```cpp
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

```cpp
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

```cpp
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

```cpp
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

```cpp
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

```cpp
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

```cpp
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

## 数组中的逆序对(offerNo51)

在数组中的两个数字，如果前面一个数字大于后面的数字，则这两个数字组成一个逆序对。输入一个数组，求出这个数组中的逆序对的总数。

```
示例 1:
输入: [7,5,6,4]
输出: 5
```

```cpp
    vector<int> tmp;
    int mergeSort(vector<int>& nums, int l, int r) {
        //递归终止条件，l>=r
        if (l >= r) return 0;
        //先找到中点
        int mid = (l + r) >> 1;
        //左半边递归，两边都是闭区间
        int c1 = mergeSort(nums, l, mid);
        //右半边递归，两边都是闭区间
        int c2 = mergeSort(nums, mid + 1, r);
        int inv_cnt = c1 + c2;
        // 3个指针，左半边的起点、右半边的起点、新数组的下标
        int i = l, j = mid + 1;
        int cnt = 0;
        while (i <= mid && j <= r) { //是&&,因为有一个遍历完就比较不了了
            //把小的放进tmp，放的那半边的指针++
            if (nums[i] <= nums[j]) {
                tmp[cnt++] = nums[i];
                //这个时候nums[i]比nums[j]小，
                //而nums[j]比mid+1...j-1的都要大，
                //故nums[i]与j-1-(mid+1)+1= j-(mid+1)个数构成逆序对
                inv_cnt += j - (mid + 1);
                i++;
            }
            else {
                tmp[cnt++] = nums[j++];
            }
        }
        //剩下的搞进来
        while (i <= mid) {
            tmp[cnt++] = nums[i];
            inv_cnt += j - (mid + 1);//同上
            i++;
        }
        while (j <= r) {
            tmp[cnt++] = nums[j++];
        }
        //把tmp复制回nums的l-r部分之中
        for (int i = 0; i < r - l + 1; ++i) {
            nums[i + l] = tmp[i];
        }
        return inv_cnt;
    }
public:
    int reversePairs(vector<int>& nums) {
        tmp.resize((int)nums.size(), 0);
        return mergeSort(nums, 0, (int)nums.size() - 1);
    }
```

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

```cpp
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

更好的解法：

使用栈，后进先出：

```cpp
#include <stack>

class Solution {
public:
    vector<int> printListFromTailToHead(ListNode* head) {
        stack<int> st;
        while (head != NULL) {
            st.push(head->val);
            head = head->next;
        }
        vector<int> array_list;
        int size = st.size();
        for (int i = 0; i < size; ++i) {
            array_list.emplace_back(st.top());
            st.pop();
        }
        return array_list;
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

```cpp
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

```cpp
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

```cpp
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

```cpp
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

```cpp
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

```cpp
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

```cpp
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

```cpp
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

```cpp
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

```cpp
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
+ 把根节点在**中序遍历结果**的**第i位**存放于变量root中
+ 对于中序遍历，根节点左边的节点位于二叉树的左边，根节点右边的节点位于二叉树的右边。所以
    + 把**中序**的根节点**左边的元素**（0->root-1）依次**扔到left_in数组中**，作为左子树的中序遍历结果；
    + 把**前序**的(1->root-1)的元素**扔到left_pre数组中**，当做左子树的前序遍历结果
+ 同样地：
    + 把根节点右边的元素（root+1->inlen）依次扔到right_in数组中，作为右子树的中序遍历结果；
    + 把(root+1->inlen)的元素扔到right_pre这个数组中，当做右子树的前序遍历结果
+ head->left就是递归left_pre,left_in的返回结果
+ head->right就是递归rightt_pre,right_in的返回结果
+ 返回head

```cpp
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
        TreeNode* head = new TreeNode(pre[0]); // new是堆上的操作，可以return出去
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

## 对称的二叉树(offerNo28)

leetcode 101

## 二叉树的最近公共祖先(offerNo68)

参考[https://blog.csdn.net/wangls56/article/details/88783783](https://blog.csdn.net/wangls56/article/details/88783783)

递归

```cpp
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

```cpp
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

```cpp
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

```cpp
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

```cpp
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

1. cpp11里的string和各种数值类型的互转：[http://www.cnblogs.com/gtarcoder/p/4925592.html](http://www.cnblogs.com/gtarcoder/p/4925592.html)
1. 如果是数字，就push进去
1. 如果是C，就pop掉top，因为这个stack只存『有效的』
1. 如果是D，就把top乘以2，push进去（因为这个stack只存『有效的』）
1. 如果是+，计算top两个元素的和，当做这轮的得分，扔进去（注意，前面几轮的得分不能变，而因为是栈，所以我们先把top给pop出来，算原来两个top的和得到新的top，然后把原来的top扔回去，再把新的top扔进去。。。）
1. stack没有迭代器，不能被遍历。。。所以只能一个个pop出来

```cpp
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

```cpp
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
