/*
 * @lc app=leetcode.cn id=399 lang=cpp
 *
 * [399] 除法求值
 */

// @lc code=start

class UnionFind {
private:
    vector<int> parent;
    vector<double> weight;
public:
    UnionFind(int n) {
        for (int i = 0; i < n; ++i) {
            parent.push_back(i);
            weight.push_back(1.0);
        }
    }

    int find(int x) {
        if (x != parent[x]) {
            int origin = parent[x];
            // 递归！
            parent[x] = find(parent[x]);
            // weight乘上去
            weight[x] *= weight[origin];
        }
        return parent[x];
    }

    void x_union(int x, int y, double value) {
        int root_x = find(x);
        int root_y = find(y);
        // 已经是同一个根，这个时候直接return..!!
        if (root_x == root_y) {
            return;
        }
        // 这里搞的是图里的红色边
        parent[root_x] = root_y;
        weight[root_x] = weight[y] * value / weight[x];
    }
    
    double is_connected(int x, int y) {
        int root_x = find(x);
        int root_y = find(y);
        // 同根，那就是在同一个集合中
        if (root_x == root_y) {
            return weight[x] / weight[y];
        } else {
            return -1.0;
        }
    }
};

class Solution {
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        int size = equations.size();
        UnionFind uf(2 * size);
        int id = 0;
        map<string, int> xmap;
        for (int i = 0; i < size; ++i) {
            string x = equations[i][0];
            string y = equations[i][1];
            if (!xmap.count(x)) {
                xmap[x] = id;
                id++;
            }

            if (!xmap.count(y)) {
                xmap[y] = id;
                id++;
            }
            uf.x_union(xmap[x], xmap[y], values[i]);
        }
        int q_size = queries.size();
        vector<double> res(q_size, -1.0);
        for (int i = 0; i < q_size; ++i) {
            string x = queries[i][0];
            string y = queries[i][1];
            if (xmap.count(x) && xmap.count(y)) {
                int id1 = xmap[x];
                int id2 = xmap[y];
                res[i] = uf.is_connected(id1, id2);
            }
        }
        return res;
    }
};
// @lc code=end

