/*Copyright 2020 The grace_t Authors. All Rights Reserved.
 
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
#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    int strStr(string haystack, string needle) {
        int len_1 = haystack.size();
        int len_2 = needle.size();
        for (int i = 0; i < len_1 - len_2 + 1; ++i) {
            int j = i;
            int k = 0;
            while (haystack[j++] == needle[k++]) {
                if (k == len_2) {
                    return i;
                }
            }
        }
        return -1;
    }
};

int main()
{
    Solution sol;
    string str1 = "hello";
    string str2 = "ll";
    cout << sol.strStr(str1, str2) << endl;
    return 0;
}

