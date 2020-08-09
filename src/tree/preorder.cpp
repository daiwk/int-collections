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
#include <vector>
using namespace std;

class TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x): val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    void pre_order(TreeNode* root, vector<int>& vec) {
        if (root == NULL) {
            return;
        }
        vec.emplace_back(root->val);
        pre_order(root->left, vec);
        pre_order(root->right, vec);
    }
};

int main()
{
    TreeNode root(0);
    TreeNode t1(1);
    TreeNode t2(2);
    TreeNode t3(3);
    TreeNode t4(4);
    TreeNode t5(5);
    root.left = &t1;
    root.right = &t2;
    t1.left = &t3;
    t1.right = &t4;
    t2.left = &t5;
    vector<int> vec;
    Solution sol;
    sol.pre_order(&root, vec);
    for (auto& i: vec) {
        cout << i << ",";
    }
    cout << endl;
    return 0;
}

