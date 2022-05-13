#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:

    int partition(vector<int>& nums, int l, int r) {
        int pivot = nums[r];
        int i = l;
        for (int j = l; j <= r - 1; ++j) {
            if (nums[j] < pivot) {
                swap(nums[j], nums[i]);
                ++i;
            }
        }
        swap(nums[i], nums[r]);
        return i;
    }

    int randomized_partition(vector<int>& nums, int l, int r) {
        int i = rand() % (r - l + 1) + l;
        swap(nums[i], nums[r]);
        return partition(nums, l, r);
    }
    void randomized_quicksort(vector<int>& nums, int l, int r) {
        if (l < r) {
            int pos = randomized_partition(nums, l, r);
            randomized_quicksort(nums, l, pos - 1); // left
            randomized_quicksort(nums, pos + 1, r); // right
        }
    }

    vector<int> sortArray(vector<int>& nums) {
        srand((unsigned)time(NULL));
        randomized_quicksort(nums, 0, nums.size() - 1);
        return nums;
    }
};

int main() {
    Solution s;
    vector<int> nums{1,5,2,3,1};
    vector<int> x = s.sortArray(nums);
    for (auto& i: x) {
        cout << i << endl;
    }
    return 0;
}
