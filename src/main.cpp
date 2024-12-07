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


class Solution2 {
public:
    int findMinimumTime(vector<int>& strength, int K) {
        //sort(strength.begin(), strength.end());
        //int time = 0;
        //int l = strength.size();
        //int cur_en = 0;
        //int X = 1;
        //for (int i = 0; i < l; i++) {
        //    while(cur_en < strength[i]){
        //        cur_en += X;
        //        time++;
        //    }
        //    //time++;
        //    X += K;
        //    cur_en = 0;
        //}
        //return time;
        std::multiset<int > s;
        for (auto it : strength) {
            s.insert(it);
        }
        int time = 0;
        int cur_en = 0;
        int X = 1;
        while (!s.empty()) {
            time++;
            cur_en += X;
            if (cur_en < *s.begin()) {
                continue;
            }
            auto it = s.lower_bound(cur_en);
            if (it != s.end()) {  // 先确保找到的迭代器是有效的，即确实找到了不小于cur_en的元素
                s.erase(it);
            }
            X += K;
            cur_en = 0;
        }
        return time;
    }
};

//输入：n = 10, m = 12
//
//输出：85
//
//解释：
//
//我们执行以下操作：
//
//增加第一个数位，得到 n = 20 。
//增加第二个数位，得到 n = 21 。
//增加第二个数位，得到 n = 22 。
//减少第一个数位，得到 n = 12 。

class Solution {
    bool is_prime(int n) {
        if (n == 1) {
            return false;
        }
        for (int i = 2; i <= int(sqrt(n)); i++) {
            if (n % i == 0) {
                return false;
            }
        }
        return true;
    }
public:
    int minOperations(int n, int m) {
        std::string s1 = to_string(n);
        std::string s2 = to_string(m);
        if (is_prime(n))
            return -1;
        if (s1 == s2)
            return stoi(s1);
        std::unordered_set<std::string> visited;
        //std::priority_queue<std::pair<int,string>> q;
        std::priority_queue<std::pair<int, string>, std::vector<std::pair<int, string>>,
            std::greater<std::pair<int, string>>> q;
        q.push({ stoi(s1),s1});
        visited.insert(s1);
        while (!q.empty()) {
            auto top = q.top();
            if (top.second == s2) {
                return top.first;
                break;
            }
            q.pop();
            std::string s = top.second;
            for (int i = 0; i < s.size(); i++) {
                if (s[i] == '0') {
                    string tmp = s;
                    tmp.replace(i, 1, to_string(s[i] - '0' + 1));
                    if (!is_prime(stoi(tmp)) && visited.find(tmp) == visited.end()) {
                        q.push({ top.first + stoi(tmp),tmp });
                        visited.insert(tmp);
                    }
                }
                else if (s[i] == '9') {
                    string tmp = s;
                    tmp.replace(i, 1, to_string(s[i] - '0' - 1));
                    if (!is_prime(stoi(tmp)) && visited.find(tmp) == visited.end()) {
                        q.push({ top.first + stoi(tmp),tmp });
                        visited.insert(tmp);
                    }
                }
                else {
                    string tmp = s;
                    tmp.replace(i, 1, to_string(s[i] - '0' - 1));
                    if (!is_prime(stoi(tmp)) && visited.find(tmp) == visited.end()) {
                        q.push({ top.first + stoi(tmp),tmp });
                        visited.insert(tmp);
                    }

                    string tmp2 = s;
                    tmp2.replace(i, 1, to_string(s[i] - '0' + 1));
                    if (!is_prime(stoi(tmp2)) && visited.find(tmp2) == visited.end()) {
                        q.push({ top.first + stoi(tmp2),tmp2 });
                        visited.insert(tmp2);
                    }
                }
            }
        }
        return -1;
    }
};

int main() {
    //int n = 5637;
    //int m = 2034;
    //Solution s;
    //auto res = s.minOperations(n, m);
    Solution2 s;
    std::vector<int> strength{ 3, 4, 1 };
    int K = 1;
    auto res = s.findMinimumTime(strength,K);
    std::cout << res << endl;
    return 0;
}

