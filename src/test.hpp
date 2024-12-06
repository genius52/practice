#include <iostream>
#include <sstream>
#include <set>
#include <queue>
#include <map>
#include <unordered_set>
#include <unordered_map>
using namespace std;


void error_log(){
    //1、 记录最多8条错误记录，循环记录，最后只用输出最后出现的八条错误记录。对相同的错误记录只记录一条，但是错误计数增加。最后一个斜杠后面的带后缀名的部分（保留最后16位）和行号完全匹配的记录才做算是“相同”的错误记录。
    //2、 超过16个字符的文件名称，只记录文件的最后有效16个字符；
    //3、 输入的文件可能带路径，记录文件名称不能带路径。也就是说，哪怕不同路径下的文件，如果它们的名字的后16个字符相同，也被视为相同的错误记录
    //4、循环记录时，只以第一次出现的顺序为准，后面重复的不会更新它的出现时间，仍以第一次为准
    //D:\zwtymj\xccb\ljj\cqzlyaszjvlsjmkwoqijggmybr 645
    //E:\je\rzuwnjvnuz 633
    //C:\km\tgjwpb\gy\atl 637
    //F:\weioj\hadd\connsh\rwyfvzsopsuiqjnr 647
    //E:\ns\mfwj\wqkoki\eez 648
    //D:\cfmwafhhgeyawnool 649
    //E:\czt\opwip\osnll\c 637
    //G:\nt\f 633
    //F:\fop\ywzqaop 631
    //F:\yay\jc\ywzqaop 631
    //D:\zwtymj\xccb\ljj\cqzlyaszjvlsjmkwoqijggmybr 645
    std::deque<std::string> q;
    std::unordered_map<std::string,int> content_cnt;
    std::string line;
    std::unordered_set<std::string> delete_record;
    while(getline(cin,line)){
        int l = line.size();
        int right_space = line.rfind(' ');
        int right_tag = line.rfind('\\');
        int filename_len = right_space - right_tag - 1;
        std::string key_name;
        if(filename_len > 16){
            key_name = line.substr(right_space-16, 16+ l - right_space+1);
        }else{
            key_name = line.substr(right_tag + 1,l - right_tag - 1);
        }
        if(delete_record.find(key_name) != delete_record.end()){
            continue;
        }
        if(content_cnt.find(key_name) == content_cnt.end()){
            if(q.size() == 8){
                std::string to_del = q.front();
                q.pop_front();
                content_cnt.erase(to_del);
                delete_record.insert(to_del);
            }
            q.push_back(key_name);
        }
        content_cnt[key_name]++;
    }
    while(!q.empty()){
        auto key = q.front();
        q.pop_front();
        std::cout<<key<<" "<< content_cnt[key]<<std::endl;
    }
//    rzuwnjvnuz 633 1
//    atl 637 1
//    rwyfvzsopsuiqjnr 647 1
//    eez 648 1
//    fmwafhhgeyawnool 649 1
//    c 637 1
//    f 633 1
//    ywzqaop 631 2
}

std::vector<int> dfs_min_leaf(std::vector<int>& v,int idx){
    if(v[idx] == -1){
        return std::vector<int>{};
    }
    int child1 = idx * 2;
    int child2 = idx * 2 + 1;
    if(child1 >= v.size() && child2 >= v.size() || (v[child1] == -1 && v[child2] == -1)){
        return std::vector<int>{v[idx]};
    }
    if(child1 >= v.size() || v[child1] == -1){
        auto ret = dfs_min_leaf(v,child2);
        ret.push_back(v[idx]);
        return ret;
    }
    if(child2 >= v.size() || v[child2] == -1){
        auto ret = dfs_min_leaf(v,child1);
        ret.push_back(v[idx]);
        return ret;
    }
    auto ret1 = dfs_min_leaf(v,child2);
    auto ret2 = dfs_min_leaf(v,child1);
    if(ret1[0] < ret2[0]){
        ret1.push_back(v[idx]);
        return ret1;
    }else{
        ret2.push_back(v[idx]);
        return ret2;
    }
}

void min_leaf(){
//3 5 7 -1 -1 2 4
    int n;
    std::vector<int> v{-1};
    std::string input;
    getline(std::cin,input);
    std::stringstream ss(input);
    std::string s_n;
    while (getline(ss,s_n,' ')){
        int n = stoi(s_n);
        v.push_back(n);
    }

    std::vector<int> trace = dfs_min_leaf(v,1);
    for(int i =  trace.size() - 1;i >= 0;i--){
        if(i != trace.size() - 1)
            std::cout<<" ";
        std::cout<< trace[i];
    }
}

int dfs_delete_city(std::vector<std::vector<int>> graph,int cur,int last){
    int cnt = 1;
    for(int i = 0;i < graph[cur].size();i++){
        int next = graph[cur][i];
        if(next == last)
            continue;
        int sum = dfs_delete_city(graph,next,cur);
        cnt += sum;
    }
    return cnt;
}

int delete_city(std::vector<std::vector<int>> graph,int city,int pre_min_degree){
    int cur_dp = 0;
    for(int i = 0;i < graph[city].size();i++){
        cur_dp = max(cur_dp, dfs_delete_city(graph,graph[city][i],city));
        if(cur_dp > pre_min_degree){
            return cur_dp;
        }
    }
    return cur_dp;
}

void calc_city_degree(){
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> graph(n + 1);
    int n2 = n;
    while(n2 > 1){
        int city1,city2;
        std::cin >>city1 >> city2;
        graph[city1].push_back(city2);
        graph[city2].push_back(city1);
        n2--;
    }
    int min_degree = 1 << 31 - 1;
    std::vector<int> min_city;
    for(int i = 1;i <= n;i++){
        int ret = delete_city(graph,i,min_degree);
        if(ret < min_degree){
            min_degree = ret;
            min_city.clear();
            min_city.push_back(i);
        }else if(ret == min_degree){
            min_city.push_back(i);
        }
    }
    for(int i = 0;i < min_city.size();i++){
        if(i > 0){
            std::cout<<" ";
        }
        std::cout<< min_city[i];
    }
}

void print_number(){
    //    XXXX1***
//    3***XXXX2***
    int n;
    std::cin >> n;
    int space_cnt = 4 * (n - 1);
    int cur_num = 1;
    for(int i = 1;i <= n;i++){
        std::string line;
        int cur_space = space_cnt;
        while (cur_space > 0){
            line = " " + line;
            cur_space--;
        }
        int num_cnt = i;
        while (num_cnt > 0){
            if(num_cnt != i){
                line += "    ";
            }
            std::string s_n = std::to_string(cur_num);
            if(i %2 == 1){
                while (s_n.length() < 4){
                    s_n.push_back('*');
                }
            }else{
                while (s_n.length() < 4){
                    s_n = "*" + s_n;
                }
            }
            line += s_n;
            num_cnt--;
            cur_num++;
        }
        std::cout<< line<<std::endl;
        space_cnt -= 4;
    }
}

void crime_time(){
    //23:59
    std::string s_num;
    std::cin>>s_num;
    std::set<int> s;
    s.insert(s_num[0] - '0');
    s.insert(s_num[1] - '0');
    s.insert(s_num[3]- '0');
    s.insert(s_num[4]- '0');
    std::vector<int> v;
    for(auto it = s.begin();it != s.end();it++){
        v.push_back(*it);
    }
    std::vector<int> cur;
    std::vector<std::vector<int>> total;
    std::function<void(std::vector<int>& v,int idx,std::vector<int>& cur,std::vector<std::vector<int>>& total)> combine;
    combine = [&](std::vector<int>& v,int idx,std::vector<int>& cur,std::vector<std::vector<int>>& total) ->void{
        if(cur.size() == 4) {
            total.push_back(cur);
            return;
        }
        if(idx >= 4)
            return;
        //choose current
        cur.push_back(v[idx]);
        combine(v,idx,cur,total);
        cur.pop_back();
        cur.push_back(v[idx]);
        combine(v,idx + 1,cur,total);
        cur.pop_back();
        //skip current
        combine(v,idx + 1,cur,total);
    };
    combine(v,0,cur,total);

    std::map<int,string> m;
    int target_timestamp = stoi(s_num.substr(0,2)) * 60 + stoi(s_num.substr(3,2));
    std::function<void(std::vector<int>& nums,int idx,std::map<int,string>& m)> perm;
    perm = [&](std::vector<int>& nums,int idx,std::map<int,string>& m)->void{ //返回时间差
        if(idx == nums.size()){
            if(nums[0] >= 3)
                return;
            if(nums[0] == 2 && nums[1] >= 4){
                return;
            }
            if(nums[2] >= 6){
                return;
            }
            std::cout<<nums[0]<<nums[1]<<nums[2]<<nums[3]<<std::endl;
            int timestamp = (nums[0] * 10 + nums[1])*60 + nums[2] * 10 + nums[3];
            if(timestamp < target_timestamp){
                m[timestamp + 24 * 60 - target_timestamp] = std::to_string(nums[0]) + std::to_string(nums[1]) + ":"
                                                            +  std::to_string(nums[2]) + std::to_string(nums[3]);
            }else if(timestamp > target_timestamp) {
                m[timestamp - target_timestamp] = std::to_string(nums[0]) + std::to_string(nums[1]) + ":"
                                                  +  std::to_string(nums[2]) + std::to_string(nums[3]);
            }
            return;
        }
        for(int i = idx;i < nums.size();i++){
            std::swap(nums[i],nums[idx]);
            perm(nums,idx + 1,m);
            std::swap(nums[i],nums[idx]);
        }
    };
    for(auto cur: total){
        //std::cout<<cur[0]<<cur[1]<<cur[2]<<cur[3]<<std::endl;
        //std::cout<<cur.size()<<std::endl;
        perm(cur,0,m);
        //std::cout<<m.begin()->second<<std::endl;
    }
    std::cout<<m.begin()->second<<std::endl;
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


int dp_bill(std::vector<std::vector<int>>& num_detail,int idx,int total_money,int cur_money,std::unordered_set<int>& choose,int& max_val,std::vector<std::vector<int>>& memo){
    if(idx == num_detail.size()){
        int cur_val = 0;
        for(auto it : choose){
            if(num_detail[it][2] != 0) {
                if (choose.find(num_detail[it][2]) == choose.end()) {
                    return 0;
                }
            }
            cur_val += num_detail[it][0] * num_detail[it][1];
        }
        max_val = max(max_val,cur_val);
        return max_val;
    }
//    if(memo[idx][choose.size()] != -1){
//        return memo[idx][choose.size()];
//    }
    int res = 0;
    //choose current
    if(cur_money + num_detail[idx][0] <= total_money){
        choose.insert(idx);
        res = max(res,dp_bill(num_detail,idx + 1,total_money,cur_money + num_detail[idx][0],choose,max_val,memo));
        choose.erase(idx);
    }
    //skip current
    res = max(res,dp_bill(num_detail,idx + 1,total_money,cur_money,choose,max_val,memo));
    memo[idx][choose.size()] = res;
    return res;
}

void bill(){
    //1000 5
    //800 2 0
    //400 5 1
    //300 5 1
    //400 3 0
    //500 2 0
    //满意度 = 价格 * 重要度
    std::string line;
    std::getline(cin,line);
    std::stringstream ss(line);
    int total_money,cnt;
    ss >> total_money >> cnt;
    int n = cnt;
    std::vector<std::vector<int>> num_detail(cnt + 1); // 价格，欢乐，主见
    int num = 1;
    //std::vector<bool> is_main(cnt + 1);
    while(n > 0){
        std::getline(cin,line);
        std::stringstream ss2(line);
        int money,happy,parent;
        ss2 >>money >> happy >> parent;
//        if(parent != 0){
//            is_main[num] = false;
//        }
        num_detail[num] = {money,happy,parent};
        num++;
        n--;
    }
    //dp[i][j]花i的钱，在前j个商品里获取的最大快乐值
//    std::vector<std::vector<int>> dp(cnt + 1,std::vector<int>(total_money + 1));
//    //std::vector<int> dp(cnt + 1);
//    for(int i = 1;i <= cnt;i++){ //买一件商品
//        for(int j = total_money;j >= 0;j--){
//
//        }
//    }

    //std::vector<bool> choose(cnt);
    int max_val = 0;
//    std::sort(num_detail.begin(),num_detail.end(),[&](const std::vector<int>& p1,const std::vector<int>& p2)->bool{
//        return p1[2] < p2[2];
//    });
    //1 << cnt - 1
    std::unordered_set<int> choose;
    std::vector<std::vector<int>> memo(cnt + 1,std::vector<int>(cnt + 1));
    for(int i = 0;i <= cnt;i++){
        for(int j = 0;j <= cnt;j++){
            memo[i][j] = -1;
        }
    }
    auto res = dp_bill(num_detail,1,total_money,0,choose,max_val,memo);
    std::cout<< res<<std::endl;
}