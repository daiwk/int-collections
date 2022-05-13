/*
 * @lc app=leetcode.cn id=912 lang=cpp
 *
 * [912] 排序数组
 */

// @lc code=start
class Solution {
    int partition(vector<int>& nums, int l, int r) {
        int pivot = nums[r];
        int i = l;
        // 期望num[i]都比pivot小，num[j]都比pivot大
        // 所以一旦num[j]比pivot小，就交换下num[i]与num[j]，并i++
        for (int j = l; j <= r - 1; ++j) {
            if (nums[j] <= pivot) {
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
};
// @lc code=end

