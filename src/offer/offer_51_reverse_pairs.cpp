/*Copyright 2022 The grace_t Authors. All Rights Reserved.
 
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
 
http://www.apache.org/licenses/LICENSE-2.0
 
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/
class Solution {
public:
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

};
