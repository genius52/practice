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
#include <queue>
//#include <bits/stdc++.h>
using namespace std;


void test_tringle(){
    //1
    //7 3 4 5 6 5 12 13
    int lines = 0;
    while (cin >> lines){
        vector<vector<int>> v(lines);
        int idx = 0;
        while(idx > lines){
            idx++;
            int n = 0;
            cin >> n;
            v[idx].resize(n);
            for(int i = 0;i < n;i++){
                cin >> v[idx][i];
            }
            sort(v[idx].begin(),v[idx].end());
        }
        for(int i = 0;i < lines;i++){

        }
    }
}

int main() {

    return 0;
}