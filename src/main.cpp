#include <iostream>
#include <sstream>
#include <set>
#include <queue>
using namespace std;


int main(){

    return 0;
}

void check_word(){
    //5 5
    //HELLOWORLD
    //CPUCY
    //EKLQH
    //CHELL
    //LROWO
    //DGRBC
    int rows;
    int columns;
    std::cin>> rows >> columns;
    std::string target;
    std::cin>>target;
    std::vector<std::vector<char>> arr(rows,std::vector<char>(columns));
    for(int r = 0;r < rows;r++){
        for(int c = 0;c < columns;c++){
            char cc;
            std::cin>>cc;
            arr[r][c] = cc;
        }
    }
    std::vector<std::vector<int>> dirs{{-1,0},{1,0},{0,-1},{0,1}};
    std::function<bool( std::vector<std::vector<char>>& arr,int r,int c,int pre_r,int pre_c,int idx)> dfs_find;
    dfs_find = [&]( std::vector<std::vector<char>>& arr,int r,int c,int pre_r,int pre_c,int idx)->bool{
        if(target[idx] != arr[r][c])
            return false;
        if(idx == target.length() - 1){
            return true;
        }
        for(auto dir : dirs){
            int next_r = r + dir[0];
            int next_c = c + dir[1];
            if(next_r < 0 || next_r >= rows || next_c < 0 || next_c >= columns)
                continue;
            if(next_r == pre_r && next_c == pre_c){
                continue;
            }
            bool ret = dfs_find(arr,next_r,next_c,r,c,idx+1);
            if(ret){
                return true;
            }
        }
        return false;
    };
    bool find = false;
    for(int r = 0;r < rows;r++){
        for(int c = 0;c < columns;c++){
            bool ret = dfs_find(arr,r,c,-1,-1,0);
            if(ret){
                find = true;
                std::cout<<r + 1<<" "<<c + 1<<std::endl;
                break;
            }
        }
        if(find)
            break;
    }
    if(!find){
        std::cout<<"NO"<<endl;
    }
}

int dfs_cal(std::string& s){
    int start = 0;
    int end = s.length();
    int res = 0;
    int i = start;
    while(i < end){
        if(s[i] == ' ')
            break;
        i++;
    }
    std::string opt = s.substr(start,i - start);
    //find first num or recursive
    i++;
    int start2 = i;
    int num1 = 0;
    int tag = 0;
    if(s[i] == '('){
        i++;
        start2 = i;
        tag = 1;
    }
    while (i < end){
        if(tag > 0){
            if(s[i] == '(')
                tag++;
            else if(s[i] == ')'){
                tag--;
                if(tag == 0){
                    std::string s2 = s.substr(start2,i - start2);
                    num1 = dfs_cal(s2);
                    break;
                }
            }
        }else{
            if(s[i] == ' '){
                num1 = stoi(s.substr(start2,i - start2));
                i++;
                break;
            }
        }
        i++;
    }
    int start3 = i;
    int num2 = 0;
    //find second num
    if(s[i] == '(') {
        i++;
        start3 = i;
        tag = 1;
        std::string s3 = s.substr(start3,end - start3 - 1);
        num2 = dfs_cal(s3);
    }else{
        num2 = stoi(s.substr(start3,end - start3));
    }
    if(opt == "add"){
        res = num1 + num2;
    }else if(opt == "sub"){
        res = num1 - num2;
    }else if(opt == "mul"){
        res = num1 * num2;
    }else if(opt == "div"){
        if(num2 == 0){
            //std::cout<<"error"<<std::endl;
            exception ex;
            throw ex;
            return 0;
        }
        res = std::floor(num1/num2);
    }
    return res;
}

void calc_expression(){
    //(div 12 (sub 45 45))
    std::string line;
    std::getline(std::cin, line);
    std::string s = line.substr(1,line.length() - 2);
    int res = 0;
    bool fault = false;
    try {
        res = dfs_cal(s);
    }catch (exception ex){
        std::cout<<"error"<<std::endl;
        fault = true;
    }
    if(!fault)
        std::cout<<res<<std::endl;
}

void short_distance(){
    //3 3
    //1 2 11
    //2 3 13
    //1 3 50
    //1 3
    //djistra
    int n = 0;
    int edge_cnt = 0;
    std::cin >>n >> edge_cnt;
    std::vector<std::vector<std::vector<int>>> graph(n + 1);
    for(int i = 0;i < edge_cnt;i++){
        int src = 0;
        int dst = 0;
        int time = 0;
        cin >> src >> dst >> time;
        graph[src].push_back({dst,time});
    }
    int start ,end = 0;
    std::cin >> start >> end;
    std::vector<int> min_time_from_start(n + 1,(1 << 31) - 1);//从start到i的最短时间
    min_time_from_start[start] = 0;
    std::priority_queue<std::pair<int,int>,std::vector<std::pair<int,int>>,
            std::greater<std::pair<int,int>>> q;
    q.push({0,start});
    while (!q.empty()){
        auto cur = q.top();
        q.pop();
        for(int i = 0;i < graph[cur.second].size();i++){
            int next = graph[cur.second][i][0];
            int duration = graph[cur.second][i][1];
            if(cur.first + duration >= min_time_from_start[next])
                continue;
            min_time_from_start[next] = cur.first + duration;
            q.push({min_time_from_start[next],next});
        }
    }
    if(min_time_from_start[end] == (1 << 31) - 1){
        std::cout<<min_time_from_start[end];
    }
    std::cout<<min_time_from_start[end];
}

void perm(){
    std::function<void(std::vector<std::string>& v,int l,int idx,std::set<string>& res)> dfs_print_char;
    dfs_print_char = [&](std::vector<std::string>& v,int l,int idx,std::set<string>& res){
        if(idx == l){
            std::stringstream ss;
            for(int i = 0;i < l;i++){
                //s.push_back(v[i]);
                ss << v[i];
            }
            res.insert(ss.str());
            return;
        }
        for(int i = idx;i < l;i++){
            if(i > idx && v[i] == v[i - 1]) //skip same char
                continue;
            std::swap(v[i],v[idx]);
            dfs_print_char(v,l,idx+1,res);
            std::swap(v[i],v[idx]);
        }
    };
    int n = 0;
    std::cin >> n;
    std::string s;
    std::vector<std::string> v;
    while (n > 0){
        std::string word;
        std::cin >> word;
        v.push_back(word);
        n--;
    }
    std::sort(v.begin(),v.end());
    std:;set<std::string> res;
    dfs_print_char(v,v.size(),0,res);
    //std::sort(res.begin(),res.end());
    for(auto it = res.begin();it != res.end();it++){
        std::cout << *it << std::endl;
    }
}

void longest_queue(){
    //3,4
    //F,M,M,F
    //F,M,M,F
    //F,F,F,M
    int rows = 0;
    int columns = 0;
    std::string s;
    std::cin>> s;
    std::stringstream ss(s);
    std::string s_rows;
    std::string s_columns;
    getline(ss,s_rows,',');
    rows = std::stoi(s_rows);
    getline(ss,s_columns);
    columns = std::stoi(s_columns);
    std::vector<std::vector<std::string>> arr(rows,std::vector<std::string>(columns));
    for(int r = 0;r < rows;r++){
        std::cin>>s;
        ss.clear();
        ss.str(s);
        for(int c = 0;c < columns;c++){
            std::string val;
            std::getline(ss,val,',');
            arr[r][c] = val;
        }
    }
    //8个方向
    std::vector<std::vector<int>> dirs{{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}};
    int max_len = 0;
    for(int r = 0;r < rows;r++){
        for(int c = 0;c < columns;c++){
            if(arr[r][c] == "M")
                continue;

            for(int i = 0;i < dirs.size()/2;i++){
                int cur_r = r + dirs[i][0];
                int cur_c = c + dirs[i][1];
                int l1 = 0;
                while (cur_r >= 0 && cur_r < rows && cur_c >= 0 && cur_c < columns && arr[cur_r][cur_c] == "M"){
                    cur_r += dirs[i][0];
                    cur_c += dirs[i][1];
                    l1++;
                }
                cur_r = r + dirs[i + 3][0];
                cur_c = c + dirs[i + 3][1];
                int l2 = 0;
                while (cur_r >= 0 && cur_r < rows && cur_c >= 0 && cur_c < columns && arr[cur_r][cur_c] == "M"){
                    cur_r += dirs[i + 3][0];
                    cur_c += dirs[i + 3][1];
                    l2++;
                }
                max_len = max(max_len,l1 + l2 + 1);
            }
        }
    }
    std::cout<<max_len;
}

void visit_matrix(){
//6 4
//5
//0 2
//1 2
//2 2
//4 1
//5 1
    int rows = 0;
    int columns = 0;
    std::cin >> rows >> columns;
    int block_cnt = 0;
    std::cin >> block_cnt;
    std::vector<std::vector<int>> pos(block_cnt);
    std::vector<std::vector<int>> arr(rows,std::vector<int>(columns));
    std::vector<std::vector<int>> arr2(rows,std::vector<int>(columns));
    for(int i = 0;i < block_cnt;i++){
        int r = 0,c = 0;
        std::cin >> r >> c;
        pos[i]= {r,c};
        arr[r][c] = -1;
        arr2[r][c] = -1;
    }
    std::vector<std::vector<int>> dir1{{1,0},{0,1}};
    std::queue<std::pair<int,int>> q;
    q.push({0,0});
    arr[0][0] = 1;
    while (!q.empty()){
        auto cur = q.front();
        q.pop();
        for(auto dir : dir1){
            int next_r = cur.first + dir[0];
            int next_c = cur.second + dir[1];
            if(next_r < 0 || next_r >= rows || next_c < 0 || next_c >= columns){
                continue;
            }
            if(arr[next_r][next_c] == -1 || arr[next_r][next_c] == 1){
                continue;
            }
            arr[next_r][next_c] = 1;
            q.push({next_r,next_c});
        }
    }
    std::vector<std::vector<int>> dir2{{-1,0},{0,-1}};
    std::queue<std::pair<int,int>> q2;
    q2.push({rows - 1,columns  - 1});
    arr2[rows - 1][columns - 1] = 1;
    while (!q2.empty()){
        auto cur = q2.front();
        q2.pop();
        for(auto dir : dir2){
            int next_r = cur.first + dir[0];
            int next_c = cur.second + dir[1];
            if(next_r < 0 || next_r >= rows || next_c < 0 || next_c >= columns){
                continue;
            }
            if(arr2[next_r][next_c] == -1 || arr2[next_r][next_c] == 1){
                continue;
            }
            arr2[next_r][next_c] = 1;
            q2.push({next_r,next_c});
        }
    }
    int trape_cnt = 0;
    int cannot_reach_cnt = 0;
    for(int r = 0;r < rows;r++){
        for(int c = 0;c < columns;c++){
            if(arr[r][c] == 1 && arr2[r][c] == 0){
                trape_cnt++;
            }
            //if(arr[r][c] == 0 && arr2[r][c] == 1){
            if(arr[r][c] == 0){
                cannot_reach_cnt++;
            }
        }
    }
    std::cout<< trape_cnt << " "<<cannot_reach_cnt;
}

void guess_number(){
//2,3,4
//2
    std::string s;
    std::cin >> s;
    stringstream ss(s);
    std::vector<int> v;
    std::string s_num;
    while(getline(ss,s_num,',')){
        v.push_back(atoi(s_num.c_str()));
    }
    int n;
    std::cin >> n;
    std::sort(v.begin(),v.end());
    std::function<void (std::vector<int>& nums,int idx, std::vector<int>& cur,int k)> dfs;
    dfs = [&](std::vector<int>& nums,int idx, std::vector<int>& cur,int k)->void{
        if(idx >= nums.size())
            return;
        cur.push_back(nums[idx]);
        if(cur.size() >= k){
            std::string s;
            for(int i = 0;i < cur.size();i++){
                if(!s.empty()){
                    s.push_back(',');
                }
                s += std::to_string(cur[i]);
            }
            std::cout<<s<<std::endl;
        }
        //print current
        dfs(nums,idx + 1,cur,k);
        cur.pop_back();
        //skip current
        dfs(nums,idx + 1,cur,k);
    };
    std::vector<int> cur;
    dfs(v,0,cur,n);
}

//01110101011110001010
void check01(){
    std::string s;
    std::cin >> s;
    int l = s.length();
    int start = 0;
    for(int i = 0;i < l;i++){
        if(s[i] == '1'){
            start = i;
            break;
        }
    }

    int max_length = 0;
    for(int i = start + 1;i < l;){
        if ((i == l - 1 && s[i] == '0') || (s[i] == '0' && s[i + 1] == '0')){
            int cur_len = i - start + 2;
            bool meet = true;
            for(int j = start - 1;j < i - 1;j += 2){
                if((s[j] != '0') || (s[j + 1] != '1')){
                    meet = false;
                    break;
                }
            }
            if(meet)
                max_length = max(max_length,cur_len);
            while(i < l && s[i] == '0'){
                i++;
            }
            start = i;
        }
        i++;
    }
    std::string ss;
    bool zero = true;
    while (max_length > 0){
        if(zero)
            ss.push_back('0');
        else
            ss.push_back('1');
        zero = !zero;
        max_length--;
    }
    std::cout << ss<<std::endl;
}