/*
 * @lc app=leetcode.cn id=295 lang=cpp
 *
 * [295] 数据流的中位数
 */

// @lc code=start
class MedianFinder {
public:
    priority_queue<int, vector<int>, less<int> > q_min; // 大顶堆 
    priority_queue<int, vector<int>, greater<int> > q_max; // 小顶堆

    MedianFinder() {
        //啥都不用干
    }
    
    void addNum(int num) {
        if (q_min.empty() || num <= q_min.top()) {
            q_min.push(num);
            if (q_min.size() > q_max.size() + 1) {
                q_max.push(q_min.top());
                q_min.pop();
            }
        } else {
            q_max.push(num);
            if (q_max.size() > q_min.size()) {
                q_min.push(q_max.top());
                q_max.pop();
            }
        }
    }
    
    double findMedian() {
        if (q_min.size() > q_max.size()) {
            return 1.0 * q_min.top();
        } else {
            return (q_max.top() + q_min.top()) / 2.;
        }
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
// @lc code=end

