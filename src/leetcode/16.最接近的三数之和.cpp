/*
 * @lc app=leetcode.cn id=16 lang=cpp
 *
 * [16] 最接近的三数之和
 */

// @lc code=start
class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        cout << "bbbb" << endl;
        int n = nums.size();
        cout << n << endl;
        if (n < 3) {
            cout << "bbb" << endl;
            return -1;
        }
        cout << "ooo" << endl;
        sort(nums.begin(), nums.end());
        int dist = INT_MAX;
        int res = INT_MIN;
        for (int i = 0; i < n; ++i) {
            cout << i << endl;
            //if (i > 0 && )
            int left = i + 1;
            int right = n - 1;
            while (left < right) {
                cout << left << "left" << endl;
                cout << right << "right" << endl;
                int sum = nums[i] + nums[left] + nums[right];


                cout << left << "qqq" << endl;
                if (sum < target) {
                    ++left;
                } else if(sum > target) {
                    --right;
                } else {
                    return sum;
                }
                cout << right << "kkk" << endl;
                cout << "sum" << sum << endl;
                cout << "target" << target << endl;
                cout << "sum-target" << sum - target << endl;
                if (dist > abs(sum - target)) {
                    cout << dist << " " << abs(sum - target) << endl;
                    res = sum;
                    dist = abs(sum - target);
                }
                ++left;
                --right;
                cout << left << "iiii" << endl;
                cout << right << "ccc" << endl;
                while (left < right && nums[left] == nums[left - 1]) {

                cout << left << "mmmmmm" << endl;
                    left++;
                }
                while (left < right && nums[right] == nums[right + 1]) {
                    --right;
                } 
            }
        }
        return res;
    }
};
// @lc code=end

