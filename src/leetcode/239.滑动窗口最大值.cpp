/*
 * @lc app=leetcode.cn id=239 lang=cpp
 *
 * [239] 滑动窗口最大值
 */

// @lc code=start
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> res;
        struct MyCmp {
            bool operator() (const pair<int, int>& a, const pair<int, int>& b) {
                return a.first < b.first;
            }
        };
        priority_queue<pair<int, int>, vector<pair<int, int> >, MyCmp> q;
        for (int i = 0; i < k; ++i) {
            q.push({nums[i], i});
        }
        // 先push_back进去！！！要不然后面可能给pop掉了。。
        res.push_back(q.top().first);
        for (int i = k; i < nums.size(); ++i) {
            // 先塞进堆里
            q.push({nums[i], i});
            // 这是个while，要一次性把窗口外的都删了，
            // 可能删不全，但下个i的时候会继续删
            while (i - q.top().second >= k) {
                q.pop();
            }
            // 堆顶就是当前这个窗口的max
            res.push_back(q.top().first);
        }
        return res;
    }
};
// @lc code=end

