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
