#include <iostream>
#include <sstream>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <map>
#include <queue>
#include <algorithm>
//#include <bits/stdc++.h>
using namespace std;

void check_letter(){
    string line1;
    getline(cin,line1);
    std::stringstream ss(line1);
    std::string word;
    std::unordered_set<std::string> record;
    while (ss >> word){
        std::sort(word.begin(), word.end());
        record.insert(word);
    }
    string line2;
    getline(cin,line2);
    std::stringstream ss2(line2);
    bool find = true;
    while (ss2 >> word){
        std::sort(word.begin(), word.end());
        if(record.find(word) == record.end()){
            find = false;
            break;
        }
    }
    if(find)
        std::cout<<"true"<<endl;
    else
        std::cout<<"false"<<endl;
}

int main() {
    check_letter();
    //sort_letter();
    // int a, b;
    // while (cin >> a >> b) { // 注意 while 处理多个 case
    //     cout << a + b << endl;
    // }
}