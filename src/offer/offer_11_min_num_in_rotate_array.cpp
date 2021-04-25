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
