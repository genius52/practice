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

bool check_conflict(vector<vector<int>> arr,int r,int c,int n){
    for(int j = 0;j < 9;j++){//查找同一行的数据
        if(r != j){
            if(arr[r][j] == n){
                return false;
            }
        }
    }
    for(int i = 0;i < 9;i ++){//查找同一列的数据
        if(r != i){
            if(arr[i][c] == n){
                return false;
            }
        }
    }
    int rows_idx = r / 3;
    int columns_idx = c / 3;
    for(int i = 3 * rows_idx;i < 3 * rows_idx + 3 ;i++)
        for(int j = 3 * columns_idx;j < 3 * columns_idx + 3;j++){
            if(r != i && c != j){
                if(arr[i][j] == n)
                    return false;
            }
        }
    return true;
}

bool dfs_sudu(vector<vector<int>>& arr,int r,int c){
    if(r == 9){
        return true;
    }
    if(arr[r][c] != 0){
        c= (c + 1)%9;
        if(c == 0)
            r++;
        return dfs_sudu(arr,r,c);
    }else{
        for(int i = 1;i <= 9;i++){
            if(check_conflict(arr,r,c,i)){
                arr[r][c] = i;
                int next_c = (c+ 1)%9;
                int next_r = r;
                if(next_c == 0)
                    next_r++;
                bool ret = dfs_sudu(arr,next_r,next_c);
                if(ret){
                    return true;
                }else{
                    arr[r][c] = 0;
                    continue;
                }
            }
        }
    }
    return false;
}

void sudu(){
    //0 9 2 4 8 1 7 6 3
    //4 1 3 7 6 2 9 8 5
    //8 6 7 3 5 9 4 1 2
    //6 2 4 1 9 5 3 7 8
    //7 5 9 8 4 3 1 2 6
    //1 3 8 6 2 7 5 9 4
    //2 7 1 5 3 8 6 4 9
    //3 8 6 9 1 4 2 5 7
    //0 4 5 2 7 6 8 3 1
    vector<vector<int>> arr(9,vector<int>(9));
    for(int i = 0;i < 9;i++){
        for(int j = 0;j < 9;j++){
            cin >> arr[i][j];
        }
    }
    dfs_sudu(arr,0,0);
//    for(int i = 0;i < 9;i++){
//        for(int j = 0;j < 9;j++){
//            if(arr[i][j] == 0){
//                for(int guess = 1;guess <= 9;guess++){
//                    if(check_conflict(arr,i,j,guess)){
//                        arr[i][j] = guess;
//                        break;
//                    }
//                }
//            }
//        }
//    }
    for(int i = 0;i < 9;i++){
        for(int j = 0;j < 9;j++){
            if(j != 0)
                cout<< " ";
            cout << arr[i][j];
        }
        cout<<endl;
    }
}

int main() {
    sudu();
    return 0;
}