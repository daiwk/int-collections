/*
 * @lc app=leetcode.cn id=155 lang=cpp
 *
 * [155] 最小栈
 */

// @lc code=start
class MinStack {
public:
    stack<int> real_stk;
    stack<int> min_stk;
    MinStack() {
        // 保证主栈push第一个数时，辅助栈也能正常work
        // 这里是INT_MAX，不是INT_MIN..
        min_stk.push(INT_MAX);
    }
    
    void push(int val) {
        // 是和min的top比较
        min_stk.push(min(min_stk.top(), val));
        real_stk.push(val);
    }
    
    void pop() {
        min_stk.pop();
        real_stk.pop();
    }
    
    int top() {
        return real_stk.top();
    }
    
    int getMin() {
        return min_stk.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
// @lc code=end

