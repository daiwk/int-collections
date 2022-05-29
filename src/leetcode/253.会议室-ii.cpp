class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        struct MyStruct {
            bool operator() (int a, int b) {
                return a > b;
            }
        };
        sort(intervals.begin(), intervals.end(), 
            [](const vector<int>& a, const vector<int>& b){
                return a[0] < b[0];
            });
        // for (auto& i: intervals) {
        //     cout << i[0] << " " << i[1] << endl;
        // }
        priority_queue<int, vector<int>, MyStruct> q;
        for (int i = 0; i < intervals.size(); i++) {
            if (!q.empty() && q.top() <= intervals[i][0]) {
                q.pop();
            }
            q.push(intervals[i][1]);
        }
        return q.size();
    }
};
