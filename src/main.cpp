#include <iostream>
#include <sstream>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <map>
#include <queue>
#include <vector>
#include <algorithm>
#include <bitset>
#include <stack>
//#include <bits/stdc++.h>
using namespace std;



//对于每个下标 i（其中 0 <= i < nums.length），独立执行以下操作：
//如果 nums[i] > 0：从下标 i 开始，向 右 移动 nums[i] 步，在循环数组中落脚的下标对应的值赋给 result[i]。
//如果 nums[i] < 0：从下标 i 开始，向 左 移动 abs(nums[i]) 步，在循环数组中落脚的下标对应的值赋给 result[i]。
//    如果 nums[i] == 0：将 nums[i] 的值赋给 result[i]。
class Solution1 {
public:
    vector<int> constructTransformedArray(vector<int>& nums) {
        int l = nums.size();
        std::vector<int> res(l);
        for (int i = 0; i < l; i++) {
            if (nums[i] > 0) {
                int next_idx = (i + nums[i] ) % l;
                res[i] = nums[next_idx];
            }
            else if (nums[i] < 0) {
                int next_idx = (i + nums[i] + l) % l;
                if (next_idx < 0) {
                    next_idx = (next_idx + l) % l;
                }
                res[i] = nums[next_idx];
            }
        }
        return res;
    }
};

class Solution2 {
public:
    int maxRectangleArea(vector<vector<int>>& points) {
        int l = points.size();
        int res = -1;
        std::sort(points.begin(), points.end());
        for (int i = 0; i < l-3; i++) {
            for (int j = i+1; j < l - 2; j++) {
                if (points[i][0] != points[j][0]) {
                    break;
                }
                for (int m = j + 1; m < l - 1; m++) {
                    for (int n = m + 1; n < l; n++) {
                        if (points[m][0] != points[n][0]) {
                            break;
                        }

                        if ((points[i][1] == points[m][1] && points[j][1] == points[n][1]) || (points[i][1] == points[n][1] && points[j][1] == points[m][1])) {

                            int min_x = points[i][0];
                            int max_x = points[m][0];

                            int min_y = min(points[i][1], points[j][1]);
                            int max_y = max(points[i][1], points[j][1]);
                            bool fail = false;
                            for (int x = 0; x < l; x++) {
                                if (x == i || x == j || x == m || x == n)
                                    continue;
                                if ((points[x][1] >= min_y && points[x][1] <= max_y) && (points[x][0] >= min_x && points[x][0] <= max_x) ){
                                    fail = true;
                                    break;
                                }
                            }
                            if (!fail) {
                                int cur = abs(points[i][1] - points[j][1]) * abs(points[i][0] - points[m][0]);
                                res = max(res, cur);
                            }

                        }
                    }
                }
            }
        }
        return res;
    }
};


class Solution3 {
public:
    long long maxSubarraySum(vector<int>& nums, int k) {
        int l = nums.size();
        std::vector<long long > prefix_sum(l);
        prefix_sum[0] = nums[0];
        for (int i = 1; i < l; i++) {
            prefix_sum[i] = prefix_sum[i - 1] + nums[i];
        }
        std::vector<std::set<long long >> record(k);
        record[0].insert(0);
        long long res = -9223372036854775808;
        for (int i = 0; i < l; i++) {
            int offset = (i + 1) % k;
            if (record[offset].size() > 0) {
                long long cur_val = prefix_sum[i] - *record[offset].begin();
                if (cur_val > res) {
                    res = cur_val;
                }
            }
            record[offset].insert(prefix_sum[i]);
        }
        return res;
    }
};

class Solution {
public:
    long long maxRectangleArea(vector<int>& xCoord, vector<int>& yCoord) {
        int l = xCoord.size();
        std::vector<std::pair<int, int>> record(l);
        std::set<int> x_s;
        std::set<int> y_s;
        for (int i = 0; i < l; i++) { 
            record[i] = { xCoord[i],yCoord[i] };
        }
        long long res = -1;
        std::sort(record.begin(), record.end(), [](const std::pair<int, int>& p1, const std::pair<int, int>& p2) -> bool{
            if (p1.first == p2.first)
                return p1.second < p2.second;
            return p1.first < p2.first;
        });
        for (int i = 0; i < l; i++) {
            for (int j = i + 1; j < l; j++) {
                if (record[i].first != record[j].first)
                    break;
                bool find = false;
                for (int m = j + 1; m < l; m++) {
                    if ((record[m].second == record[i].second || record[m].second == record[j].second)) {
                        for (int n = m + 1; n < l; n++) {
                            if (record[m].first != record[n].first) {
                                break;
                            }

                            if ((record[m].second == record[i].second && record[n].second == record[j].second) || (record[m].second == record[j].second && record[n].second == record[i].second)) {
                                long long cur = (long long)(record[m].first - record[i].first) * static_cast<long long>(abs(record[i].second - record[j].second));
                                if (cur > res)
                                    res = cur;
                                find = true;
                            }
                        }
                    }
                }
                if (find)
                    break;
            }
        }
        return res;
    }
};


int main() {
    std::vector<int> xCoord{ 1,1,3,3 };
    std::vector<int> yCoord{ 1,3,1,3 };
    Solution s;
    auto res = s.maxRectangleArea(xCoord, yCoord);
   std::cout << res << endl;
    return 0;
}

