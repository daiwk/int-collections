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
