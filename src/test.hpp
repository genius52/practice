#include <iostream>
#include <sstream>
#include <set>
#include <queue>
#include <map>
#include <unordered_set>
#include <unordered_map>
using namespace std;


void find101(){
    int n1,n2;
    while(cin >>n1 >> n2){
        int cnt = 0;
        for(int i = n1;i <= n2;i++){
            bitset<32> b(i);
            string s = b.to_string();
            if(s.find("101") == string::npos){
                cnt++;
            }
        }
        std::cout<<cnt<<endl;
    }
}

int union_find(int cur,vector<int>& groups){
    if(groups[cur] != cur){
        return union_find(groups[cur],groups);
    }
    return cur;
}

void linux_version(){
    int n = 0;
    while(cin >> n){
        vector<vector<int>> v(n,vector<int>(n));
        for(int i = 0;i < n;i++){
            for(int j = 0;j < n;j++){
                cin >> v[i][j];
            }
        }
        vector<int> groups(n);
        for(int i = 0;i < n;i++){
            groups[i] = i;
        }
        for(int i = 0;i < n;i++){
            for(int j = 0;j < n;j++){
                if(i == j)
                    continue;
                if(v[i][j] == 0)
                    continue;
                int group1 = union_find(i,groups);
                int group2 = union_find(j,groups);
                if(group1 != group2){
                    groups[group2] = group1;
                }
            }
        }
        unordered_map<int,int> m;
        int max_cnt = 0;
        for(int i = 0;i < n;i++){
            m[groups[i]]++;
            if(m[groups[i]] > max_cnt)
                max_cnt = m[groups[i]];
        }

        std::cout<<max_cnt<<endl;
    }
}

void max_profit(){
    //第一行输入商品的数量number。
    //第二行输入商品售货天数days。
    //第三行输入仓库限制每件商品的最大持有数量是 item[index]。 以下numbers行，输入每件商品每天的价格。
    //每种商品每天的价格是item-price[item_index][day]
    int cnt = 0;
    int days = 0;
    while(cin >> cnt >> days){
        vector<int> max_limit(cnt);
        vector<vector<int>> day_price(days,vector<int>(cnt));
        for(int i = 0;i < cnt;i++){
            cin>>max_limit[i];
        }
        for(int i = 0;i < cnt;i++){
            for(int j = 0;j < days;j++){
                cin >> day_price[i][j];
            }
        }
        int res = 0;
        for(int i = 0;i < cnt;i++){
            int profit = 0;
            for(int j = 1;j < days;j++){
                if(day_price[i][j] > day_price[i][j - 1]){
                    profit += (day_price[i][j] - day_price[i][j - 1]) * max_limit[i];
                }
            }
            res += profit;
        }
        std::cout<< res << endl;
    }
}

void choose_hotel(){
    //第一行是n、k、x，n表示在网上搜索的酒店数量，x表示心理价位，k表示最接近心理价位的酒店个数。
    //第二行是n个酒店的价格数组A[0] A[1] A[2]...A[n-1]
    int total,price,cnt;
    while(cin >> total >> cnt >>price){
        vector<int> v(total);
        for(int i = 0;i < total;i++){
            cin >> v[i];
        }
        v.push_back(price);
        sort(v.begin(),v.end());
        int idx = 0;
        while(v[idx] != price){
            idx++;
        }
        int left = idx - 1;
        int right = idx + 1;
        int l = v.size();
        vector<int> res;
        while(left >= 0 && right < l && res.size() < cnt){
            if(v[idx] - v[left] <= v[right] - v[idx]){
                res.push_back(v[left]);
                left--;
            }else{
                res.push_back(v[right]);
                right++;
            }
        }
        while(res.size() < cnt){
            if(left > 0){
                res.push_back(v[left]);
                left--;
            }
            if(right < l){
                res.push_back(v[right]);
                right++;
            }
        }
        sort(res.begin(),res.end());
        for(int i = 0;i < res.size();i++){
            if(i != 0)
                cout<< " ";
            std::cout<<res[i];
        }
    }
}

void report_cost(){
    int cache_cost = 0;
    while(cin >> cache_cost){
        cin.ignore();
        string line1,line2;
        getline(cin,line1);
        getline(cin,line2);
        stringstream ss1(line1);
        stringstream ss2(line2);
        int idx = 0;
        int num = 0;
        vector<int> nums;
        while(ss1 >>num){
            nums.push_back(num);
            idx++;
        }
        vector<int> costs;
        int cost;
        while(ss2 >> cost){
            costs.push_back(cost);
        }
        unordered_map<int,pair<int,int>> idx_cnt;
        for(int i = 0;i < nums.size();i++){
            idx_cnt[nums[i]].first++;
            idx_cnt[nums[i]].second = costs[i];
        }
        int res = 0;
        for(auto it : idx_cnt){
            int all_print_cost = it.second.first * it.second.second;
            int print_cache = it.second.second + cache_cost;
            res += min(all_print_cost,print_cache);
        }
        std::cout<<res<<endl;
    }
}

void errorcode(){
    int n = 0;
    while(cin >> n){
        vector<int> v(n);
        for(int i = 0;i < n;i++){
            cin >> v[i];
        }
        int max_freq = 0;
        unordered_map<int,int> cnt;
        for(int i = 0;i < n;i++){
            cnt[v[i]]++;
            if(cnt[v[i]] > max_freq){
                max_freq = cnt[v[i]];
            }
        }
        unordered_set<int> s;
        for(auto it : cnt){
            if(it.second == max_freq){
                s.insert(it.first);
            }
        }
        int min_len = n;
        for(auto it : s){
            int left = 0;
            int right = n - 1;
            while(v[left] != it){
                left++;
            }
            while(v[right] != it){
                right--;
            }
            int cur_len = right - left + 1;
            if(cur_len < min_len)
                min_len = cur_len;
        }
        std::cout<< min_len <<endl;
    }
}

void perfect_move(){
    string line;
    while(cin>>line){
        int l = line.length();
        int a_cnt = 0;
        int d_cnt = 0;
        int w_cnt = 0;
        int s_cnt = 0;
        for(int i = 0;i < l;i++){
            if(line[i] == 'A'){
                a_cnt++;
            }else if(line[i] == 'D'){
                d_cnt++;
            }else if(line[i] == 'W'){
                w_cnt++;
            }else if(line[i] == 'S'){
                s_cnt++;
            }
        }
        if(a_cnt == d_cnt == w_cnt == s_cnt){
            std::cout<< 0<<endl;
        }else{
            int target = l /4;
            int res = 0;
            if(a_cnt > target){
                res += a_cnt - target;
            }
            if(d_cnt > target){
                res += d_cnt - target;
            }
            if(w_cnt > target){
                res += w_cnt - target;
            }
            if(s_cnt > target){
                res += s_cnt - target;
            }
            std::cout<<res<<endl;
        }
    }
}

void version_cmp(){
    string line1,line2;
    while(getline(cin,line1) && getline(cin,line2)){
        int l1 = line1.length();
        int l2 = line2.length();
        string tmp1,tmp2;
        vector<string> v1,v2;
        for(int i = 0;i < l1;i++){
            if(line1[i] != '.'){
                tmp1.push_back(line1[i]);
            }else{
                v1.push_back(tmp1);
                tmp1.clear();
            }
        }
        v1.push_back(tmp1);
        string res;
        for(int i = 0;i < l2;i++){
            if(line2[i] != '.'){
                tmp2.push_back(line2[i]);
            }else{
                v2.push_back(tmp2);
                tmp2.clear();
            }
        }
        v2.push_back(tmp2);
        int len1 = v1.size();
        int len2 = v2.size();
        for(int i = 0;i < max(len1,len2);i++){
            if(i >= v1.size()){
                std::cout<< line2<<endl;
                break;
            }
            if(i >= v2.size()){
                std::cout<< line1<<endl;
                break;
            }
            if(i == max(len1,len2) - 1){
                int idx1 = v1[i].find('-');
                int idx2 = v2[i].find('-');
                if(idx1 == string::npos && idx2 == string::npos){
                    int n1 = stoi(v1[i]);
                    int n2 = stoi(v2[i]);
                    if(n1 >= n2){
                        std::cout<< line1 <<endl;
                    }else{
                        std::cout<< line2 <<endl;
                    }
                }else{
                    string sub1 = v1[i].substr(idx1 + 1,v1[i].size() - idx1 - 1);
                    string sub2 = v2[i].substr(idx2 + 1,v2[i].size() - idx2 - 1);
                    if(sub1 >= sub2){
                        std::cout<< line1<<endl;
                    }else{
                        std::cout<< line2<<endl;
                    }
                }
            }else{
                int n1 = stoi(v1[i]);
                int n2 = stoi(v2[i]);
                if(n1 == n2)
                    continue;

                if(n1 >= n2){
                    std::cout<< line1 <<endl;
                }else{
                    std::cout<< line2 <<endl;
                }
                break;
            }
        }
    }
}

void pixel(){
    string line;
    while(getline(cin,line)){
        stringstream ss(line);
        vector<int> v;
        int sum = 0;
        string s;
        while(getline(ss, s,' ')){
            v.push_back(stoi(s));
            sum += stoi(s);
        }
        int l = v.size();
        double cur_aver = double(sum) / (double)l;
        int increase = 0;

        if(cur_aver == 128){
            std::cout<< 0<<endl;
        }else if(cur_aver < 128){
            int k = 0;
            while(cur_aver <= 128){
                k++;
                int new_aver = double(sum + l * k)/double(l);
                if(abs(128 - new_aver) > abs(128 - cur_aver)){
                    k--;
                    break;
                }else{
                    cur_aver = new_aver;
                }
            }
            std::cout<<k<<endl;
        }else if(cur_aver >= 128){
            int k = 0;
            while(cur_aver >= 128){
                k--;
                int new_aver = double(sum + l * k)/double(l);
                if(abs(128 - new_aver) > abs(128 - cur_aver)){
                    break;
                }else{
                    cur_aver = new_aver;
                }
            }
            std::cout<<k<<endl;
        }
    }
}

pair<double,int> opt_1092(double value,int p10,int p92,int p5){
    int used_cnt = 0;
    double cur_value = value;
    if(value >= 100){
        int can_use = min(p10,int(cur_value/100));
        used_cnt += can_use;
        cur_value -= can_use * 10;
    }
    if(p92 > 0){
        used_cnt++;
        cur_value *= 0.92;
    }
    return {cur_value,used_cnt};
}

pair<double,int> opt_105(double value,int p10,int p92,int p5){
    int used_cnt = 0;
    double cur_value = value;
    if(value >= 100){
        int can_use = min(p10,int(cur_value/100));
        used_cnt += can_use;
        cur_value -= can_use * 10;
    }
    if(p5 > 0){
        int can_use = min(p5,int(cur_value)/ 5);
        used_cnt += can_use;
        cur_value -= can_use * 5;
    }
    return {cur_value,used_cnt};
}

pair<double,int> opt_925(double value,int p10,int p92,int p5){
    int used_cnt = 0;
    double cur_value = value;
    if(p92 > 0){
        used_cnt++;
        cur_value *= 0.92;
    }
    if(p5 > 0){
        int can_use = min(p5,int(cur_value)/ 5);
        used_cnt += can_use;
        cur_value -= can_use * 5;
    }
    return {cur_value,used_cnt};
}

pair<double,int> opt_9210(double value,int p10,int p92,int p5){
    int used_cnt = 0;
    double cur_value = value;
    if(p92 > 0){
        used_cnt++;
        cur_value *= 0.92;
    }
    if(value >= 100){
        int can_use = min(p10,int(cur_value/100));
        used_cnt += can_use;
        cur_value -= can_use * 10;
    }
    return {cur_value,used_cnt};
}

pair<double,int> opt_592(double value,int p10,int p92,int p5){
    int used_cnt = 0;
    double cur_value = value;
    if(p5 > 0){
        int can_use = min(p5,int(cur_value)/ 5);
        used_cnt += can_use;
        cur_value -= can_use * 5;
    }
    if(p92 > 0){
        used_cnt++;
        cur_value *= 0.92;
    }
    return {cur_value,used_cnt};
}

pair<double,int> opt_510(double value,int p10,int p92,int p5){
    int used_cnt = 0;
    double cur_value = value;
    if(p5 > 0){
        int can_use = min(p5,int(cur_value)/ 5);
        used_cnt += can_use;
        cur_value -= can_use * 5;
    }
    if(value >= 100){
        int can_use = min(p10,int(cur_value/100));
        used_cnt += can_use;
        cur_value -= can_use * 10;
    }
    return {cur_value,used_cnt};
}

void shopping(){
    //第一行：每个人拥有的优惠券数量（数量取值范围为[0, 10]），按满减、打折、无门槛的顺序输入。 第二行：表示购物的人数n（1 <= n <= 10000）。
    //最后n行：每一行表示某个人优惠前的购物总价格（价格取值范围(0, 1000]，都为整数）。
    //约定：输入都是符合题目设定的要求的。
    //每行输出每个人每次购物优惠后的最低价格以及使用的优惠券总数量，每行的输出顺序和输入的顺序保持一致。
    int p10,p92,p5;
    while(cin >> p10 >> p92 >> p5){
        int people = 0;
        cin >> people;
        vector<int> v(people);
        for(int i = 0;i < people;i++){
            cin >> v[i];
        }
        vector<std::function<pair<double,int>(double value,int p10,int p92,int p5)>> vf{opt_1092,opt_105, opt_510,
                                                                                        opt_592, opt_9210, opt_925};
        for(int i = 0;i < v.size();i++){
            int min_value = v[i];
            int min_used_cnt = p10 + p92 + p5;
            for(int j = 0;j < vf.size();j++){
                std::pair<double,int> p = vf[j](v[i],p10,p92,p5);
                if(static_cast<int>(p.first) < min_value){
                    min_value = p.first;
                    min_used_cnt = p.second;
                }else if(static_cast<int>(p.first) == min_value){
                    min_used_cnt = min(min_used_cnt,p.second);
                }
            }
            std::cout<< min_value << " "<<min_used_cnt<<endl;

        }
    }
}

void setbox(){
//AFG
//BE
//CD
    string s;
    int width = 0;
    while(cin >> s >> width){
        vector<vector<char>> v(width);
        int l = s.length();
        for(int i = 0;i < l;i++){
            int idx = i % width;
            v[idx].push_back(s[i]);
        }
        for(int i = 0;i < width;i++){
            for(int j = 0;j < v[i].size();j++){
                std::cout<< v[i][j];
            }
            if(i != width - 1)
                std::cout<<endl;
        }
    }
}

//端口合并
void merge_port(){
    int n = 0;
    while (cin >> n){
        cin.ignore();
        vector<set<string>> v(n);
        for(int i = 0;i < n;i++){
            string line;
            getline(cin,line);
            if(line.find(',') != string::npos){
                stringstream ss(line);
                string port;
                while (getline(ss,port,',')){
                    v[i].insert(port);
                }
            }else{
                v[i].insert(line);
            }
        }
        bool merge = true;
        while(merge) {
            merge = false;
            for (int i = 0; i < v.size(); i++) {
                if (v[i].size() <= 1)
                    continue;
                for (int j = 0; j < v.size(); j++) {
                    if (i == j) {
                        continue;
                    }
                    if (v[j].size() <= 1)
                        continue;
                    int same_cnt = 0;
                    for (auto it1 = v[i].cbegin(); it1 != v[i].end(); it1++) {
                        if (v[j].find(*it1) != v[j].end()) {
                            same_cnt++;
                            if (same_cnt >= 2)
                                break;
                        }
                    }
                    if (same_cnt >= 2) {
                        for (auto it2 = v[j].cbegin(); it2 != v[j].cend(); it2++) {
                            v[i].insert(*it2);
                        }
                        merge = true;
                        v.erase(v.begin() + j);
                    }
                }
            }
        }
        std::cout<<"[";
        for(int i = 0;i < v.size();i++){
            if(i != 0)
                cout<<",";
            std::cout<<"[";
            for(auto it = v[i].begin();it != v[i].end();it++){
                if(it != v[i].begin())
                    cout<<",";
                cout<<*it;
            }
            std::cout<<"]";
        }
        std::cout<<"]";
    }
}

void ride_bicycle(){
    int n ,m;
    while(cin>> m >> n){
        vector<int> v(n);
        for(int i = 0;i < n;i++){
            cin >> v[i];
        }
        sort(v.begin(),v.end());
        int left = 0;
        int right = n - 1;
        int cnt = 0;
        while(left < right){
            if(v[left]+v[right] <= m){
                cnt++;
                left++;
                right--;
            }else{
                cnt++;
                right--;
            }
        }
        if(left == right)
            cnt++;
        std::cout<<cnt<<endl;
    }
}

void new_word(){
    string s1,s2;
    while(cin >> s1 >> s2){
        int l1 = s1.length();
        int l2 = s2.length();
        if(l1 < l2){
            std::cout<<0<<endl;
            continue;
        }
        int left = 0;
        int cnt1[26] = {};
        int cnt2[26]={};
        for(int i = 0;i < l2;i++){
            cnt1[s1[i] - 'a']++;
        }
        for(auto c : s2){
            cnt2[c - 'a']++;
        }
        int res = 0;
        while((left + l2) <= l1){
            int meet = true;
            for(int i = 0;i < 26;i++){
                if(cnt1[i] != cnt2[i]){
                    meet = false;
                    break;
                }
            }
            if(meet)
                res++;
            cnt1[s1[left] - 'a']--;
            if(left + l2 < l1){
                cnt1[s1[left + l2] - 'a']++;
            }
            left++;
        }
        std::cout<<res<<endl;
    }
}

void guess_number_game(){
    int n;
    while(cin >> n){
        vector<int> v(n);
        for(int i = 0;i < n;i++){
            cin >> v[i];
        }
        unordered_map<int,int> m;
        int max_dis = -1;
        for(int i = 0;i < n;i++){
            if(m.find(v[i]) != m.end()){
                max_dis = max(max_dis,i - m[v[i]]);
            }else{
                m[v[i]] = i;
            }
        }
        std::cout<<max_dis<<endl;
    }
}

void check_queue(){
    //tail add 4
    //head add 5
    //remove
    int n = 0;
    while(cin >> n){
        cin.ignore();
        deque<int> q;
        int delete_num = 1;
        int opt_cnt = 0;
        for(int i = 0;i < n * 2;i++){
            string line;
            getline(cin,line);
            if(line.find("remove") != string::npos){
                if(q.front() == delete_num){
                    q.pop_front();
                }else{
                    std::vector<int> v;
                    while(!q.empty()){
                        v.push_back(q.front());
                        q.pop_front();
                    }
                    sort(v.begin(),v.end());
                    for(int i = 0;i < v.size();i++){
                        q.push_back(v[i]);
                    }
                    q.pop_front();
                    opt_cnt++;
                }
                delete_num++;
            }else if(line.find("head add") != string::npos){
                int idx = line.rfind(' ');
                int l = line.length();
                int num = stoi(line.substr(idx + 1,l - idx - 1));
                q.push_front(num);
            }else if(line.find("tail add") != string::npos){
                int idx = line.rfind(' ');
                int l = line.length();
                int num = stoi(line.substr(idx + 1,l - idx - 1));
                q.push_back(num);
            }
        }
        std::cout<<opt_cnt<<endl;
    }
}


int cal_mark(vector<vector<char>>& v,int rows,int columns,int r,int c,int pre_r,int pre_c,char mark,int& edge_cnt){
    if(v[r][c] == 'X'){
        return 0;
    }
    if(v[r][c] == mark)
        return 0;
    v[r][c] = mark;
    if(r == 0 || r == rows - 1||c == 0 || c == columns - 1){
        edge_cnt++;
        if(edge_cnt > 1)
            return -1;
    }
    vector<vector<int>> dirs{{-1,0},{1,0},{0,-1},{0,1}};
    int total = 1;
    for(auto dir : dirs){
        int next_r = r + dir[0];
        int next_c = c + dir[1];
        if(next_r == pre_r && next_c == pre_c)
            continue;
        if(next_r < 0 || next_r >= rows || next_c < 0 || next_c >= columns)
            continue;
        int ret = cal_mark(v,rows,columns,next_r,next_c,r,c,mark,edge_cnt);
        if(ret == -1)
            return -1;
        total += ret;
    }
    return total;
}

void dfs_mark(vector<vector<char>>& v,int rows,int columns,int r,int c,int pre_r,int pre_c,char mark){
    if(v[r][c] == 'X'){
        return;
    }
    if(v[r][c] == mark){
        return;
    }
    v[r][c] = mark;
    vector<vector<int>> dirs{{-1,0},{1,0},{0,-1},{0,1}};
    for(auto dir : dirs){
        int next_r = r + dir[0];
        int next_c = c + dir[1];
        if(next_r == pre_r && next_c == pre_c){
            continue;
        }
        if(next_r < 0 || next_r >= rows || next_c < 0 || next_c >= columns)
            continue;
        dfs_mark(v,rows,columns,next_r,next_c,r,c,mark);
    }
}

void check_area(){
//查找单入口空闲区域
    int rows,columns;
    while (cin >> rows >> columns){
        vector<vector<char>> v(rows,vector<char>(columns));
        for(int r = 0;r < rows;r++){
            for(int c = 0;c < columns;c++){
                cin>> v[r][c];
            }
        }
        int max_area = 0;
        int max_cnt = 0;
        int ret_r = 0;
        int ret_c = 0;
        char mark1 = 'A';
        char mark2 = 'C';
        for(int r = 0;r < rows;r++){
            if(v[r][0] != 'O')
                continue;
            dfs_mark(v,rows,columns,r,0,-1,-1,mark1);
            int edge_cnt = 0;
            int ret = cal_mark(v,rows,columns,r,0,-1,-1,mark2,edge_cnt);
            if(ret > max_area){
                max_area = ret;
                ret_r = r;
                ret_c = 0;
                max_cnt = 1;
            }else if (ret == max_area){
                max_cnt++;
            }
        }
        for(int r = 0;r < rows;r++){
            if(v[r][columns - 1] != 'O')
                continue;
            int edge_cnt = 0;
            dfs_mark(v,rows,columns,r,columns - 1,-1,-1,mark1);
            int ret = cal_mark(v,rows,columns,r,columns - 1,-1,-1,mark2,edge_cnt);
            if(ret > max_area){
                max_area = ret;
                ret_r = r;
                ret_c = columns - 1;
                max_cnt = 1;
            }else if (ret == max_area){
                max_cnt++;
            }
        }
        for(int c = 0;c < columns;c++){
            if(v[0][c] != 'O')
                continue;
            int edge_cnt = 0;
            dfs_mark(v,rows,columns,0,c,-1,-1,mark1);
            int ret = cal_mark(v,rows,columns,0,c,-1,-1,mark2,edge_cnt);
            if(ret > max_area){
                max_area = ret;
                ret_r = 0;
                ret_c = c;
                max_cnt = 1;
            }else if (ret == max_area){
                max_cnt++;
            }
        }
        for(int c = 0;c < columns;c++){
            if(v[rows - 1][c] != 'O')
                continue;
            int edge_cnt = 0;
            dfs_mark(v,rows,columns,rows - 1,c,-1,-1,mark1);
            int ret = cal_mark(v,rows,columns,rows - 1,c,-1,-1,mark2,edge_cnt);
            if(ret > max_area){
                max_area = ret;
                ret_r = rows - 1;
                ret_c = c;
                max_cnt = 1;
            }else if (ret == max_area){
                max_cnt++;
            }
        }
        if(max_area == 0)
            std::cout<<"NULL"<<endl;
        else if(max_cnt > 1){
            std::cout<< max_area<<endl;
        }
        else{
            std::cout<<ret_r << " "<< ret_c << " "<< max_area<<endl;
        }
    }
}

void charge(){
    //查找充电设备组合
    //输入为三行：
    //
    //第一行是充电设备个数n。
    //第二行是每个充电设备的输出功率。
    //第三行是充电站最大输出功率p_max。
    int n;
    while(cin >> n){
        vector<int> v(n);
        for(int i = 0;i < n;i++){
            cin >> v[i];
        }
        int p_max;
        cin >> p_max;
        vector<vector<int>> dp(n,vector<int>(p_max + 1));//dp[i][j]; 在前i个充电设备中， 限额j时的最大输出功率
        for(int i = 0;i <= p_max;i++){
            if(i >= v[0]){
                dp[0][i] = v[0];
            }
        }
        for(int i = 1;i < n;i++){
            for(int j = 0;j <= p_max;j++){
                if(j >= v[i])
                    dp[i][j] = max(dp[i - 1][j],v[i] + dp[i][j - v[i]]);
                else{
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
        std::cout<<dp[n - 1][p_max]<<endl;
    }
}

void muban(){
    //最小木板长度
    int n = 0;
    int length = 0;
    while(cin >> n >> length){
        vector<int> v(n);
        for (int i = 0; i < n; ++i) {
            cin >> v[i];
        }
        sort(v.begin(),v.end());
        int res = v[0];
        int l = v.size();
        for(int i = 1;i < l;i++){
            int diff = v[i] - v[i - 1];
            if((diff * i) <= length){
                length -= diff * i;

                res = v[i];
            }else{
                v[i - 1] += length/i;
                res = v[i - 1];
                length = 0;
                break;
            }
        }
        if(length > 0){
            res += length / l;
        }
        std::cout<<res << endl;
    }
}

void cover_substring(){
    string s1,s2;
    int k;
    while(cin >> s1 >> s2){
        cin >> k;
        int l1 = s1.length();
        int l2 = s2.length();
        int find_idx = -1;
        int cnt1[26]={};
        int cnt2[26]={};
        for(int i = 0;i < l1;i++){
            cnt1[s1[i] - 'a']++;
        }
        for(int i = 0;i < min(l2,l1 + k);i++){
            cnt2[s2[i] - 'a']++;
        }
        bool fail = false;
        for(int i = 0;i < 26;i++){
            if(cnt1[i] > cnt2[i]){
                fail = true;
                break;
            }
        }
        if(!fail)
            std::cout<<"0"<<endl;
        else{
            int find_idx = -1;
            for(int i = l1 + k;i < l2;i++){
                cnt2[s2[i - l1 - k] - 'a']--;
                cnt2[s2[i] - 'a']++;
                bool fail2 = false;
                for(int j = 0;j < 26;j++){
                    if(cnt1[j] > cnt2[j]){
                        fail2 = true;
                        break;
                    }
                }
                if(!fail2){
                    find_idx = i;
                    break;
                }
            }
            std::cout<< find_idx<<endl;
        }
    }
}

bool check_shifei(vector<int>& v,int k,int days){
    int total = 0;
    for(int i = 0;i < v.size();i++){
        total += v[i]/k;
        if(v[i] % k != 0)
            total++;
    }
    return total <= days;
}

void shifei(){
    int n,days;
    while(cin >> n >> days){
        vector<int> v(n);
        int sum = 0;
        for(int i = 0;i < n;i++){
            cin >> v[i];
            sum += v[i];
        }
        sort(v.begin(),v.end());
        int low = v[0];
        int high = v[n - 1];
        int res = -1;
        while (low < high){
            int mid = (low + high)/2;
            bool ret = check_shifei(v,mid,days);
            if(!ret){
                low = mid + 1;
                res = mid + 1;
            }else{
                res = mid;
                high = mid - 1;
            }
        }
        std::cout<<res<<endl;
    }
}


//01背包问题
void workpay(){
    //输入的第一行为两个正整数T和n。其中，T代表工作时长（单位：h，0 <T < 1000000），n代表工作数量（1 < n <= 3000）。
    //接下来是n行，每行包含两个整数t和w，其中，t代表该工作消耗的时长（单位：h，t > 0），w代表该项工作的报酬。
    int total_time,n;
    while(cin>>total_time>>n){
        vector<pair<int,int>> time_pay;
        for(int i = 0;i < n;i++){
            int t,pay;
            cin >> t >> pay;
            time_pay.push_back({t,pay});
        }
        vector<vector<int>> dp(n,vector<int>(total_time + 1)); //dp[i][j] 前i个工作中，花费j的时间的最大收益
        for(int i = 0;i <= total_time;i++){
            if(i >= time_pay[0].first){
                dp[0][i] = time_pay[0].second;
            }
        }
        for(int i = 1;i < n;i++){
            for(int j = 0;j <= total_time;j++){
                if(j >= time_pay[i].first){
                    dp[i][j] = max(dp[i - 1][j],time_pay[i].second + dp[i - 1][j - time_pay[i].first]);
                }
            }
        }
        std::cout<< dp[n - 1][total_time]<<endl;
    }
}

bool find_sub(string s1,int idx1,int l1,string s2,int idx2,int l2,vector<bool>& used){
    while(idx1 < l1 && idx2 < l2){
        while(idx1 < l1 && used[idx1]){
            idx1++;
        }
        if(s1[idx1] == s2[idx2]){
            used[idx1] = true;
            idx1++;
            idx2++;
        }else{
            idx1++;
        }
    }
    return idx2 == l2;
}

void substring(){
    string a,b;
    while(cin >> a >> b){
        int l1 = a.length();
        int l2 = b.length();

        vector<bool> used(l1);
        int cnt = 0;
        int idx1 = 0;
        int idx2 = 0;

        while (true){
            bool ret = find_sub(a,0,l1,b,0,l2,used);
            if(ret)
                cnt++;
            else{
                break;
            }
        }
        std::cout<<cnt<<endl;
    }
}

//backtrace
bool dfs_basketball(vector<int>& v,int cnt,int cur_score,int target_score){
    if(cnt == 0)
        return true;
    for(int i = 0;i < v.size();i++){
        if(cur_score + v[i] > target_score){
            continue;
        }
        int tmp = v[i];
        v.erase(v.begin() + i);
        cur_score += tmp;
        if(cur_score == target_score){
            bool cur = dfs_basketball(v,cnt - 1,0,target_score);
            if(cur)
                return true;
        }else{
            bool cur = dfs_basketball(v,cnt,cur_score,target_score);
            if(cur)
                return true;
        }
        cur_score -= tmp;
        v.push_back(tmp);
    }
    return false;
}

void basketball(){
    int n;
    while (cin >> n){
        vector<int> v(n);
        for (int i = 0; i < n; ++i) {
            cin >> v[i];
        }
        sort(v.begin(),v.end());
        int sum = 0;
        for(auto i : v){
            sum += i;
        }
        for(int i = n;i >= 1;i--){
            if(sum % i != 0){
                continue;
            }
            bool ret = dfs_basketball(v,i,0,sum/i);
            if(ret){
                std::cout<<sum/i<<endl;
                break;
            }
        }
    }
}

void score_sort(){
    //给定一些同学的信息（名字，成绩）序列，请你将他们的信息按照成绩从高到低或从低到高的排列,相同成绩
    //都按先录入排列在前的规则处理。
    int n = 0;
    int increase = 0;
    while(cin >> n){
        //cin.ignore();
        cin>>increase;
        int idx = 0;
        vector<pair<int,string>> v;
        for(int i = 0;i < n;i++){
//            string line;
//            getline(cin ,line);
//            stringstream ss(line);
            string name;
            int score;
            cin >> name>> score;
            v.push_back({score,name});
            idx++;
        }
        stable_sort(v.begin(),v.end(),[&](const pair<int,string>& v1,const pair<int,string>& v2)->bool{
            if(increase == 1){
                return v1.first < v2.first;
            }else{
                return v1.first > v2.first;
            }
        });
        for(int i = 0;i < n;i++){
            std::cout<< v[i].second<<" " << v[i].first << endl;
        }
    }
}


int calc_score(vector<int>& v,int idx){
    int total_cnt = 0;
    int score = 0;
    for(int i = 0;i <= idx;i++){
        if (total_cnt + v[i] > 100){ //必须上传了
            score += 100 - total_cnt;
            score -= total_cnt;
            return score;
        }else{
            score += v[i];
            score -= total_cnt;
            total_cnt += v[i];
        }
    }
    return score;
}

void log_score(){
    string input;
    while (getline(cin,input)){
        stringstream ss(input);
        vector<int> v;
        int n;
        while(ss >> n){
            v.push_back(n);
        }
        int l = v.size();
        int max_score = 0;
        for(int i = 0;i < l;i++){
            int cur = calc_score(v,i);
            max_score = max(max_score,cur);
        }
        std::cout<<max_score<<endl;
    }
}

void car_color(){
    string line;
    while(getline(cin, line)){
        stringstream ss(line);
        int seconds = 0;
        cin>>seconds;
        int color;
        deque<int> q;
        int cnt[3]{};
        int max_cnt = 0;
        while(ss >> color){
            if(q.size() < seconds){
                q.push_back(color);
                cnt[color]++;
                if(cnt[color] > max_cnt)
                    max_cnt = cnt[color]++;
            }else{
                cnt[q.front()]--;
                q.pop_front();
                q.push_back(color);
                cnt[color]++;
                if(cnt[color] > max_cnt)
                    max_cnt = cnt[color]++;
            }
        }
        std::cout<< max_cnt<<endl;
    }
}

void print_task(){
    //7
    //IN 1 1
    //IN 1 2
    //IN 1 3
    //IN 2 1
    //OUT 1
    //OUT 2
    //OUT 2
    int n = 0;
    while(cin >> n){
        //优先级、时间
        std::function<bool(const pair<int,int>& p1,pair<int,int>& p2)> my_cmp = [](const pair<int,int>& p1,pair<int,int>& p2)->bool{
            if(p1.first != p2.first)
                return p1.first < p2.first;
            else{
                return p1.second > p2.second;
            }
        };
        vector<std::priority_queue<pair<int,int>,std::vector<pair<int,int>>, decltype(my_cmp)>> q(n,decltype(q)::value_type(my_cmp));
        int time_index = 1;
        vector<int> out_task;
        for(int i = 0;i < n;i++){
            string status;

            cin>>status;
            if(status == "IN"){
                int p_no = 0;
                int priority = 0;
                cin>>p_no>>priority;
                q[p_no].push({priority,time_index});
                time_index++;
            }else if(status == "OUT"){
                int p_no = 0;
                cin>>p_no;
                out_task.push_back(p_no);
            }
        }
        for(int i = 0;i < out_task.size();i++){
            int p_no = out_task[i];
            if(q[p_no].empty()){
                std::cout<<"NULL"<<endl;
            }else{
                std::cout<< q[p_no].top().second<<endl;
                q[p_no].pop();
            }
        }
    }
}

int dfs_server(vector<vector<int>>& v,int n,int cur){
    int res = 0;
    for(int i = 0;i < n;i++){
        if(i == cur){
            continue;
        }
        if(v[cur][i] == 0)
            continue;

        auto ret = dfs_server(v,n,i);
        res = max(res,ret);
    }
    return res + v[cur][cur];
}

void server(){
    int n = 0;
    while (cin >> n){
        vector<vector<int>> v(n,vector<int>(n));
        for(int i = 0;i < n;i++){
            for(int j = 0;j < n;j++){
                cin >> v[i][j];
            }
        }
        int k = 0;
        cin >> k;
        //vector<bool> visited(n);
        auto res = dfs_server(v,n,k - 1);
        std::cout<< res<<endl;
    }
}

string recrusive_rb(long n,long k){
    if(n == 1){
        return "red";
    }
    if(n == 2){
        if(k == 0)
            return "blue";
        else
            return "red";
    }
    long total_len = long(pow(2,n - 1));
    if(k >= total_len/2){
        long pos = k - total_len/2;
        return recrusive_rb(n - 1,pos);
    }else{
        auto ret = recrusive_rb(n - 1,k);
        if(ret == "red")
            return "blue";
        else
            return "red";
    }
}

void rb_issue(){
    //第1个字符串：R
    //第2个字符串：BR
    //第3个字符串：RBBR
    //第4个字符串：BRRBRBBR
    //第5个字符串：RBBRBRRBBRRBRBBR
    int cnt;
    while(cin >> cnt){
        vector<pair<long,long>> record(cnt);
        for(int i = 0;i < cnt;i++){
            long n,k;
            cin >> n >> k;
            record[i] = {n,k};
        }
        for(int i = 0;i < cnt;i++){
            auto res = recrusive_rb(record[i].first,record[i].second);
            std::cout<<res<<endl;
        }
    }
}

void sort_string(){
    //给定一个字符串s，包含以空格分隔的若干个单词，请对s进行如下处理后输出：
    //
    //单词内部调整：对每个单词字母重新按字典序排序；
    //单词间顺序调整：
    //统计每个单词出现的次数，并按次数降序排列
    //次数相同时，按单词长度升序排列
    //次数和单词长度均相同时，按字典序升序排列
    string input;
    while(getline(cin,input)){
        stringstream ss(input);
        vector<string> v;
        map<string,int> m;
        string word;
        while(getline(ss,word,' ')){
            std::sort(word.begin(), word.end());
            m[word]++;
            v.push_back(word);
        }
        std::sort(v.begin(),v.end(), [&](const string& s1,const string& s2)->bool{
            if(m[s1] == m[s2]){
                if(s1.length() == s2.length()){
                    return s1 < s2;
                }else{
                    return s1.length() < s2.length();
                }
            }else{
                return m[s1] > m[s2];
            }
        });
        stringstream ss2;
        bool first = true;
        for(int i = 0;i < v.size();i++){
            if(!first)
                ss2 << " ";
            ss2 << v[i];
            first = false;
        }
        std::cout<< ss2.str() << endl;
    }
}

int backtrace_short_distance(vector<vector<int>>& graph,int n,int cur_node,vector<bool>& visited){
    bool pass = true;
    for(int i = 0;i < n;i++){
        if(!visited[i]){
            pass = false;
            break;
        }
    }
    if(pass){
        return graph[cur_node][0];
    }
    int res = 1 << 31 - 1;
    for(int i = 0;i < graph[cur_node].size();i++){
        if(visited[i]){
            continue;
        }
        visited[i] = true;
        int ret = graph[cur_node][i] + backtrace_short_distance(graph,n,i,visited);
        res = min(res,ret);
        visited[i] = false;
    }
    return res;
}

void short_distance(){
    int n = 0;
    while(cin >> n){
        vector<vector<int>> graph(n,vector<int>(n));
        for(int i = 0;i < n;i++){
            for(int j = 0;j < n;j++){
                cin >> graph[i][j];
            }
        }
        vector<bool> visited(n);
        visited[0] = true;
        int res = backtrace_short_distance(graph,n,0,visited);
        std::cout<<res<<endl;
    }
}

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
    for(int i = 0;i < 9;i++){
        for(int j = 0;j < 9;j++){
            if(j != 0)
                cout<< " ";
            cout << arr[i][j];
        }
        cout<<endl;
    }
}

//void print_money(){
//    //151121.15
//
//    //壹、贰、叁、肆、伍、陆、柒、捌、玖、拾、 佰、仟、万、亿、元、角、分、零、整
//    vector<string> num{"零","壹","贰","叁","肆","伍","陆","柒","捌","玖"};
//    vector<string> unit{"","拾","佰","仟","万","拾","佰","仟","亿","拾","佰","仟","万",};
//
//    string s;
//    while(cin>>s){
//        int tag = s.find('.');
//        int l = s.length();
//        string prefix = s.substr(0,tag);
//        string suffix = s.substr(tag + 1,l - tag);
//        int l1 = prefix.length();
//        string output1;
//        int offset = 0;
//        for(int i = l1 - 1;i >= 0;i--){
//            int n = prefix[i] - '0';
//
//            int idx = offset % 12;
//            output1 = num[n] + unit[idx] + output1;
//
//            offset++;
//        }
//        string output2;
//        if(suffix == "00"){
//            output2 += "整";
//        }else{
//            if(suffix[0] == '0'){
//                output2 += "零";
//            }else{
//                output2 += num[suffix[0] - '0'] + "角";
//            }
//            if(suffix[1] != '0'){
//                output2 += num[suffix[1] - '0'] + "分";
//            }
//        }
//        output1 = "人民币" + output1 +"元";
//        std::cout<<output1<<output2<<endl;
//    }
//}


int recursive_calc2(string s){
    stack<int> st;
    int l = s.length();
    int i = 0;
    char pre_opt = '+';
    int pre_num = 0;
    while(i < l){
        while(i < l && isdigit(s[i])){
            pre_num *= 10;
            pre_num += s[i] - '0';
            i++;
        }
        if(s[i] == '(' || s[i] == '[' || s[i] == '{'){
            char find_tag = 0;
            if(s[i] == '('){
                find_tag = ')';
            }else if(s[i] == '['){
                find_tag = ']';
            }else if(s[i] == '{'){
                find_tag = '}';
            }
            int j = i + 1;
            int cnt = 1;
            while(j < l){
                if(s[j] == s[i]){
                    cnt++;
                }else if(s[j] == find_tag){
                    cnt--;
                }
                if(cnt == 0)
                    break;
                j++;
            }
            int ret = recursive_calc2(s.substr(i + 1,j - i - 1));
            if(pre_opt == '+'){
                st.push(ret);
            }else if(pre_opt == '-'){
                st.push(-ret);
            }else if(pre_opt == '*'){
                int val = st.top() * ret;
                st.pop();
                st.push(val);
            }else if(pre_opt == '/'){
                int val = st.top() / ret;
                st.pop();
                st.push(val);
            }
            i = j + 1;
            if(i < l){
                pre_opt = s[i];
                i++;
            }
        }else{
            if(i != 0){
                if(pre_opt == '+'){
                    st.push(pre_num);
                }else if(pre_opt == '-'){
                    st.push(-pre_num);
                }else if(pre_opt == '*'){
                    int val = st.top() * pre_num;
                    st.pop();
                    st.push(val);
                }else if(pre_opt == '/'){
                    int val = st.top() / pre_num;
                    st.pop();
                    st.push(val);
                }
                pre_num = 0;
            }
            pre_opt = s[i];
            i++;
        }
    }
    if(pre_num != 0){
        if(pre_opt == '+'){
            st.push(pre_num);
        }else if(pre_opt == '-'){
            st.push(-pre_num);
        }else if(pre_opt == '*'){
            int val = st.top() * pre_num;
            st.pop();
            st.push(val);
        }else if(pre_opt == '/'){
            int val = st.top() / pre_num;
            st.pop();
            st.push(val);
        }
    }
    int sum = 0;
    while (!st.empty()){
        sum += st.top();
        st.pop();
    }
    return sum;
}

void calc2(){
    string s;
    while(cin >> s){
        int res = recursive_calc2(s);
        std::cout<<res<<endl;
    }
}


void money_rate(){
    //1CNY=100fen（1元=100分）
    //1HKD=100cents（1港元=100港分）
    //1JPY=100sen（1日元=100仙）
    //1EUR=100eurocents（1欧元=100欧分）
    //1GBP=100pence（1英镑=100便士）

    //CNY	JPY	HKD	EUR	GBP
    //100	1825	123	14	12
    int n = 0;
    map<string,double> m;
    m["CNY"] = 100.0;
    m["JPY"] = 1825.0;
    m["HKD"] = 123.0;
    m["EUR"] = 14.0;
    m["GBP"] = 12.0;

    set<string> s_big{"CNY","JPY","HKD","EUR","GBP"};
    set<string> s_small{"fen","sen","cents","eurocents","pence"};

    map<string,double> m2;
    m2["fen"] = 100.0;
    m2["sen"] = 1825.0;
    m2["cents"] = 123.0;
    m2["eurocents"] = 14.0;
    m2["pence"] = 12.0;
    while(cin>>n){
        double sum = 0;
        for(int i = 0;i < n;i++){
            string s;
            cin >> s;
            string s_num;
            string s_unit;
            int l = s.length();
            double big_num = 0;
            double small_num = 0;
            for(auto it :s_big){
                int ret = s.find(it);
                if(ret != string::npos){
                    big_num = stoi(s.substr(0,ret));
                    big_num = big_num * double(100)/ double(m[it]) * 100;
                    break;
                }
            }
            for(auto it : s_small){
                int ret = s.find(it);
                if(ret != string::npos){
                    int find_idx = ret - 1;
                    while(find_idx >= 0){
                        if(!isdigit(s[find_idx])){
                            break;
                        }
                        find_idx--;
                    }
                    small_num = stoi(s.substr(find_idx + 1,ret));
                    small_num = small_num * double(100)/ double(m2[it]);
                    break;
                }
            }
            sum += big_num + small_num;
        }
        std::cout<<int(sum)<<endl;
    }
}

void divide_group(){
    int n;
    while(cin >> n){
        if(n == 1){
            int only = 0;
            cin >> only;
            if(only == 0)
                std::cout<<"true"<<endl;
            else
                std::cout<<"true"<<endl;
            continue;
        }

        std::vector<int> v;
        for(int i = 0;i < n;i++){
            int n2 = 0;
            cin>>n2;
            v.push_back(n2);
        }
        //vector<int> five;
        vector<int> other;
        int sum_five = 0;
        int sum_three = 0;
        int sum_other = 0;
        for(auto i : v){
            if(i % 5 == 0){
                sum_five += i;
            }else if(i % 3 == 0){
                sum_three += i;
            }else{
                sum_other += i;
                other.push_back(i);
            }
        }
        int diff = abs(sum_five - sum_three);
        if(diff == sum_other){
            std::cout<<"true"<<endl;
            continue;
        }
        //枚举所有和的可能行，能使得 abs(sum_other - cur_sum * 2) == diff
        unordered_set<int> s;
        bool find = false;
        for(int i = 0;i < other.size();i++){
            unordered_set<int> s2;
            s2.insert(other[i]);
            if(abs(sum_other - other[i] * 2) == diff){
                find = true;
                break;
            }
            for(auto it : s){
                int cur_sum = it + other[i];
                if(abs(sum_other - cur_sum * 2)  == diff){
                    find = true;
                    break;
                }
                s2.insert(cur_sum);
            }
            for(auto it : s2){
                s.insert(it);
            }
            if(find)
                break;
        }
        if(find)
            std::cout<<"true"<<endl;
        else
            std::cout<<"false"<<endl;
    }
}

void walk_step(){
    //6
    //2 5 1 5 4 5
    int n = 0;
    while(cin>> n){
        vector<int> height;
        for(int i = 0;i < n;i++){
            int h;
            cin>> h;
            height.push_back(h);
        }
        //sort(height.begin(),height.end());
        vector<int> dp(n,1);
        int max_len = 1;
        for(int i = 1;i < n;i++){
            for(int j = i - 1;j >= 0;j--){
                if(height[i] > height[j]){
                    dp[i] = max(dp[i],1 + dp[j]);
                    max_len = max(max_len,dp[i]);
                }
            }
        }
        std::cout<<max_len<<endl;
    }
}

void longest_numstring(){
    //abcd12345ed125ss123058789
    //a8a72a6a5yy98y65ee1r2
    string input;
    while(cin>>input){
        int l = input.length();
        int left = -1;
        int max_len = 0;
        vector<string> v;
        for(int i = 0;i < l;i++){
            if(input[i] >= '0' && input[i] <= '9'){
                if(left == -1){
                    left = i;
                }
            }else{
                if(left != -1){
                    int cur_len = i - left;
                    if(cur_len > max_len){
                        max_len = cur_len;
                        v = {input.substr(left,cur_len)};
                    }else if(cur_len == max_len){
                        v.push_back(input.substr(left,cur_len));
                    }
                    left = -1;
                }
            }
        }
        if(left != -1){
            int cur_len = l - left;
            if(cur_len > max_len){
                max_len = cur_len;
                v = {input.substr(left,cur_len)};
            }else if(cur_len == max_len){
                v.push_back(input.substr(left,cur_len));
            }
        }
        for(int i = 0;i < v.size();i++){
            std::cout<<v[i];
        }
        std::cout<<","<<max_len<<endl;
    }
}


void ip_addr(){
    //255.255.255.1000
    std::string input;
    while(getline(cin,input)){
        if(input.find('.') == string::npos || input.find(' ') != string::npos){
            std::cout<<"NO"<<endl;
            continue;
        }
        stringstream ss(input);
        string s_num;
        bool find = true;
        int cnt = 0;
        while(getline(ss,s_num,'.')){
            try{
                for(auto c : s_num){
                    if(!isdigit(c)){
                        find = false;
                        break;
                    }
                }
                if(!find)
                    break;
                if(s_num.length() > 1 && s_num[0] == '0'){
                    find = false;
                    break;
                }
                int ret = stoi(s_num);
                string check = to_string(ret);
                if(s_num != check){
                    find = false;
                    break;
                }
                cnt++;
                if(ret >= (1 << 8) || ret < 0){
                    find = false;
                    break;
                }
            }catch (exception ex){
                find = false;
                break;
            }
        }
        if(cnt != 4){
            find = false;
        }
        if(find)
            std::cout<<"YES"<<endl;
        else{
            std::cout<<"NO"<<endl;
        }
    }
}

void compare_poker(){
    string input;
    map<std::string,int> m{{"3",3},{"4",4},{"5",5 },{"6",6},{"7",7},{"8",8},{"9", 9},
                           {"10",10},{"J",11},{"Q",12},{"K",13},{"A",1},{"2",2},{"joker",20},{"JOKER",30}};
    while(getline(cin,input)){
        int tag = input.find('-');
        string s1 = input.substr(0,tag);
        string s2 = input.substr(tag + 1,input.length() - tag);
        int space1 = 0;
        int space2 = 0;
        for(auto c : s1){
            if(c == ' '){
                space1++;
            }
        }
        for(auto c : s2){
            if(c == ' '){
                space2++;
            }
        }
        if(space1 != space2){
            if(s1.find("JOKER") != string::npos && s1.find("joker") != string::npos){
                std::cout<<s1<<endl;
            }else if(s2.find("JOKER") != string::npos && s2.find("joker") != string::npos){
                std::cout<<s2<<endl;
            }else{
                if(space1 == 3){
                    std::cout<<s1<<endl;
                }else if(space2 == 3){
                    std::cout<<s2<<endl;
                }else{
                    std::cout<<"ERROR"<<endl;
                }
            }
        }else{
            //个数一样是同类型的牌，不会有杂牌
            s1 += " ";
            s2 += " ";
            int score1 = m[s1.substr(0,s1.find(' '))];
            int score2 = m[s2.substr(0,s2.find(' '))];
            if(score1 > score2){
                std::cout<<s1<<endl;
            }else{
                std::cout<<s2<<endl;
            }
        }
    }
}

double cal_24(double n1,double n2,string opt){
    if(opt == "+"){
        return n1 + n2;
    }else if(opt == "-"){
        return n1 - n2;
    }else if(opt == "*"){
        return n1 * n2;
    }else if(opt == "/"){
        return n1/n2;
    }
    return 0;
}

void poker24(){
    map<string,double> m{{"A",1},{"2",2},{"3",3},{"4",4},{"5",5},
                         {"6",6},{"7",7},{"8",8},{"9",9},{"10",10},
                         {"J",11},{"Q",12},{"K",13}};
    map<double,string> m_reverse{{1,"A"},{2,"2"},{3,"3"},{4,"4"},{5,"5"},
                                 {6,"6"},{7,"7"},{8,"8"},{9,"9"},{10,"10"},
                                 {11,"J"},{12,"Q"},{13,"K"}};
    string opt[4] ={"+","-","*","/"};
    string n1,n2,n3,n4;
    while(cin >>n1 >> n2>>n3>>n4){
        if(n1 == "joker" || n1 == "JOKER" || n2 == "joker" || n2 == "JOKER" ||
           n3 == "joker" || n3 == "JOKER" || n4 == "joker" || n4 == "JOKER"){
            std::cout<<"ERROR";
            continue;
        }
        std::vector<double> nums{m[n1],m[n2],m[n3],m[n4]};
        for(int i = 0;i < 4;i++){
            for(int j = 0;j < 4;j++){
                if(i == j)
                    continue;
                for(const auto & opt_1 : opt){
                    double ret1 = cal_24(nums[i],nums[j],opt_1);
                    for(int m = 0;m < 4;m++){
                        if(m == i || m == j)
                            continue;
                        for(const auto & opt_2 : opt){
                            double ret2 = cal_24(ret1,nums[m],opt_2);
                            for(int n = 0;n < 4;n++){
                                if( n == m || n == i || n == j)
                                    continue;
                                for(const auto & opt_3 : opt){
                                    double ret3 = cal_24(ret2,nums[n],opt_3);
                                    if(abs(ret3 - 24) < 0.001){
                                        std::cout<<m_reverse[nums[i]] <<opt_1<<m_reverse[nums[j]] << opt_2<<m_reverse[nums[m]] << opt_3<<m_reverse[nums[n]]<<endl;
                                        return;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        std::cout<<"NONE"<<endl;
    }
}

void dfs_train(vector<int>& in,int idx,int n,std::stack<int>& st,std::vector<int>& leave,std::vector<std::vector<int>>& res){
    if(leave.size() == n){
        res.push_back(leave);
    }else{
        //出站
        if(!st.empty()){
            //auto leave2 = leave;
            int tmp = st.top();
            leave.push_back(st.top());
            st.pop();
            dfs_train(in,idx,n,st,leave,res);
            st.push(tmp);
            leave.pop_back();
        }
        //进站
        if(idx < n){
            st.push(in[idx]);
            dfs_train(in,idx + 1,n,st,leave,res);
            st.pop();
        }
    }
}

void train(){
    int n = 0;
    while(cin >> n){
        //std::vector<int> v(n);
        vector<int> in;
        for(int i = 0;i < n;i++){
            //cin >> v[i];
            int train;
            cin >> train;
            in.push_back(train);
        }
        std::vector<std::vector<int>> res;
        std::stack<int> station;
        std::vector<int> leave;
        dfs_train(in,0,n,station,leave,res);
        sort(res.begin(),res.end());
        for(int i = 0;i < res.size();i++){
            for(int j = 0;j < res[i].size();j++){
                if(j != 0)
                    std::cout<<" ";
                std::cout << res[i][j];
            }
            std::cout<<std::endl;
        }
    }
}


void longest_substr(){
    string s1,s2;
    while(cin >> s1 >> s2){
        int l1 = s1.length();
        int l2 = s2.length();
        if(l1 == 0 || l2 == 0){
            std::cout<< 0<<endl;
            continue;
        }
        vector<vector<int>> dp(l1,vector<int>(l2));//dp[i][j]:最大公共长度
        int max_len = 0;
        for(int i = 0;i < l1;i++){
            if(s1[i] == s2[0]){
                dp[i][0] = 1;
                max_len = 1;
            }
        }
        for(int j = 0;j < l2;j++){
            if(s1[0] == s2[j]){
                dp[0][j] = 1;
                max_len = 1;
            }
        }
        for(int i = 1;i < l1;i++){
            for(int j = 1;j < l2;j++){
                if(s1[i] == s2[j]){
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                    max_len = max(max_len,dp[i][j]);
                }
            }
        }
        std::cout<< max_len<<endl;
    }
}

//5
//23 61
//61 59
//59 34
//34 56
//56 35
//(A(((BC)D)E))
std::pair<int, std::pair<int, int>>  calc_maza(string s, std::unordered_map<char, std::pair<int, int>>& m) {
    int l = s.length();
    stack<int> st;
    int i = 0;
    int sum = 0;
    int pre_rows = 0;
    int pre_columns = 0;
    while (i < l) {
        if (s[i] >= 'A' && s[i] <= 'Z') {
            if (pre_rows == 0 && pre_columns == 0) {
                //st.push(s[i]);
                pre_rows = m[s[i]].first;
                pre_columns = m[s[i]].second;
            }
            else {
                int cur_rows = m[s[i]].first;
                int cur_columns = m[s[i]].second;
                int opt_cnt = pre_rows * cur_columns * pre_columns;
                pre_columns = cur_columns;
                sum += opt_cnt;
            }
            i++;
        }
        else if (s[i] == '(') {
            int j = i + 1;
            int tag = 1;
            while (j < l) {
                if (s[j] == '(') {
                    tag++;
                }
                else if (s[j] == ')') {
                    tag--;
                }
                if (tag == 0) {
                    break;
                }
                j++;
            }
            auto ret = calc_maza(s.substr(i + 1, j - i - 1), m);
            sum += ret.first;

            if (pre_rows == 0 && pre_columns == 0) {
                pre_rows = ret.second.first;
                pre_columns = ret.second.second;
            }
            else {
                int cur_rows = ret.second.first;
                int cur_columns = ret.second.second;
                int opt_cnt = pre_rows * cur_columns * pre_columns;
                pre_columns = cur_columns;
                sum += opt_cnt;
            }
            i = j + 1;
        }
    }
    return { sum, {pre_rows,pre_columns} };
}

void maza_express() {
    //输入多行，先输入要计算乘法的矩阵个数n，每个矩阵的行数，列数，总共2n的数，最后输入要计算的法则
    //计算的法则为一个字符串，仅由左右括号和大写字母（'A'~'Z'）组成，保证括号是匹配的且输入合法！
    int n = 0;
    while (cin >> n) {
        std::unordered_map<char, std::pair<int, int>> m;
        char c = 'A';
        int rows = 0;
        int columns = 0;
        for (int i = 0; i < n; i++) {
            cin >> rows >> columns;
            m[c] = { rows,columns };
            c++;
        }
        string exp;
        cin >> exp;
        if (exp[0] == '(') {
            exp = exp.substr(1, exp.length() - 2);
        }
        auto res = calc_maza(exp, m);
        std::cout << res.first << endl;
    }

}

void cal_maza() {
    ////输入描述：
    //第一行包含一个正整数x，代表第一个矩阵的行数
    //    第二行包含一个正整数y，代表第一个矩阵的列数和第二个矩阵的行数
    //    第三行包含一个正整数z，代表第二个矩阵的列数
    //    之后x行，每行y个整数，代表第一个矩阵的值
    //    之后y行，每行z个整数，代表第二个矩阵的值
    int first_rows, first_columns, second_columns;
    while (cin >> first_rows) {
        cin >> first_columns;
        cin >> second_columns;
        std::vector<std::vector<int>> first(first_rows, std::vector<int>(first_columns));
        for (int r = 0; r < first_rows; r++) {
            for (int c = 0; c < first_columns; c++) {
                cin >> first[r][c];
            }
        }
        std::vector<std::vector<int>> second(first_columns, std::vector<int>(second_columns));
        for (int r = 0; r < first_columns; r++) {
            for (int c = 0; c < second_columns; c++) {
                cin >> second[r][c];
            }
        }
        std::vector<std::vector<int>> res(first_rows, std::vector<int>(second_columns));
        for (int r = 0; r < first_rows; r++) {
            for (int c = 0; c < second_columns; c++) {
                for (int c2 = 0; c2 < first_columns; c2++) {
                    res[r][c] += first[r][c2] * second[c2][c];
                }
            }
        }
        for (int r = 0; r < first_rows; r++) {
            for (int c = 0; c < second_columns; c++) {
                if (c != 0)
                    std::cout << " ";
                std::cout << res[r][c];
            }
            std::cout << endl;
        }
    }
}

void game24() {
    std::string input;
    while (getline(cin, input)) {
        stringstream ss(input);
        float n1, n2, n3, n4;
        ss >> n1 >> n2 >> n3 >> n4;
        std::vector<float> nums{ n1,n2,n3,n4 };
        unordered_set<string> visited;
        std::queue<std::vector<float>> q;
        q.push(nums);
        bool find = false;
        while (!q.empty()) {
            int len = q.size();
            for (int i = 0; i < len; i++) {
                auto cur = q.front();
                q.pop();
                int l = cur.size();
                if (l == 1) {
                    if (abs(cur[0] - 24) < 0.001) {
                        find = true;
                        break;
                    }
                    else {
                        continue;
                    }
                }
                for (int m = 0; m < l; m++) {
                    for (int n = 0; n < l; n++) {
                        if (m == n)
                            continue;
                        float opt1 = cur[m] + cur[n];
                        float opt2 = cur[m] - cur[n];
                        float opt3 = cur[m] * cur[n];
                        float opt4 = cur[m] / cur[n];
                        if (l > 2) {
                            std::vector<float> next1;
                            next1.push_back(opt1);
                            std::vector<float> next2;
                            next2.push_back(opt2);
                            std::vector<float> next3;
                            next3.push_back(opt3);
                            std::vector<float> next4;
                            next4.push_back(opt4);
                            for (int x = 0; x < l; x++) {
                                if (x != m && x != n) {
                                    next1.push_back(cur[x]);
                                    next2.push_back(cur[x]);
                                    next3.push_back(cur[x]);
                                    next4.push_back(cur[x]);
                                }
                            }
                            q.push(next1);
                            q.push(next2);
                            q.push(next3);
                            q.push(next4);
                        }
                        else {
                            q.push({ opt1 });
                            q.push({ opt2 });
                            q.push({ opt3 });
                            q.push({ opt4 });
                        }
                    }
                }
            }
            if (find)
                break;
        }
        if (find)
            std::cout << "true" << endl;
        else
            std::cout << "false" << endl;
    }
}

void command() {
    //reset
    //reset board
    //board add
    //board delet
    //reboot backplane
    //backplane abort

    //命   令	执   行
    //reset	reset what
    //    reset board	board fault
    //    board add	where to add
    //    board delete	no board at all
    //    reboot backplane	impossible
    //    backplane abort	install first
    //    he he	unknown command

    std::unordered_map<string, string> cmd_exec;
    cmd_exec["reset"] = "reset what";
    cmd_exec["reset board"] = "board fault";
    cmd_exec["board add"] = "where to add";
    cmd_exec["board delete"] = "no board at all";
    cmd_exec["reboot backplane"] = "impossible";
    cmd_exec["backplane abort"] = "install first";

    //std::unordered_map<string, string> one_key;

    std::vector<std::vector<std::string>> cmd{ {"reset"},{"reset", "board"},{"board", "add"} ,{"board", "delete"} ,{"reboot", "backplane"} ,{"backplane","abort"} };
    std::string input;
    while (getline(cin, input)) {
        auto ret = input.find(' ');
        std::string s1, s2;
        int word_cnt = 0;
        if (ret == string::npos) {
            s1 = input;
            word_cnt = 1;
        }
        else {
            s1 = input.substr(0, ret);
            int l = s1.length();
            s2 = input.substr(ret + 1, l - ret - 1);
            word_cnt = 2;
        }
        int find_cnt = 0;
        int find_index = -1;
        for (int i = 0; i < cmd.size(); i++) {
            if (word_cnt != cmd[i].size())
                continue;
            if (word_cnt == 2) {
                if (cmd[i][0].find(s1) == 0 && cmd[i][1].find(s2) == 0) {
                    find_cnt++;
                    find_index = i;
                }
            }
            else if (word_cnt == 1) {
                if (cmd[i][0].find(s1) == 0) {
                    find_cnt++;
                    find_index = i;
                }
            }
        }
        if (find_cnt == 1) {
            if (word_cnt == 1)
                std::cout << cmd_exec[cmd[find_index][0]] << endl;
            else {
                std::cout << cmd_exec[cmd[find_index][0] + " " + cmd[find_index][1]] << endl;
            }
        }

        if (find_cnt == 0 || find_cnt > 1)
            std::cout << "unknown command" << endl;
    }
}


void common_substring(){
    std::string s1,s2;
    while(cin >> s1 >> s2){
        if(s1.length() > s2.length())
            swap(s1,s2);
        int l1 = s1.length();
        int l2 = s2.length();

        if(l1 == 0 || l2 == 0){
            std::cout<<-1<<endl;
            continue;
        }
        //dp[i][j]: s1[i - 1],s2[j - 1]相同子字符串的长度
        std::vector<std::vector<int>> dp(l1,std::vector<int>(l2));
        for(int i = 0;i < l1;i++){
            if(s1[i] == s2[0]){
                dp[i][0] = 1;
            }
        }
        for(int j = 0;j < l2;j++){
            if(s1[0] == s2[j]){
                dp[0][j] = 1;
            }
        }
        int max_len = 0;
        int max_len_idx = max(l1,l2);
        for(int i = 1;i < l1;i++){
            for(int j = 1;j < l2;j++){
                if(s1[i] == s2[j]){
                    dp[i][j] = max(dp[i][j],1 + dp[i - 1][j - 1]);
                    if(dp[i][j] > max_len){
                        max_len = dp[i][j];
                        max_len_idx = i - max_len + 1;
                    }
                }
            }
        }
        if(max_len == 0){
            std::cout<<-1<<endl;
        }else{
            std::string sub = s1.substr(max_len_idx,max_len);
            std::cout<<sub<<endl;
        }
    }
}

class player{
public:
    int total_ = 0;
    int cur_song_ = 0;
    int cur_list_ = 0;

    player(int total){
        total_ = total;
        cur_song_ = 1;
        cur_list_ = 1;
    }
    void up(){
        cur_song_--;
        if(cur_song_ < cur_list_){
            cur_list_--;
            if(cur_list_ <= 0){
                if(total_ > 4)
                    cur_list_ = total_ - 3;
                else{
                    cur_list_ = 1;
                }
            }
        }
        if(cur_song_ == 0){
            cur_song_ = total_;
        }
    }
    void down(){
        cur_song_++;
        if(cur_song_ > total_){
            cur_song_ = 1;
            if(total_ > 4){
                cur_list_ = 1;
            }
        }else{
            if(cur_song_ > cur_list_ + 3){
                cur_list_++;
            }
        }
    }
};

void mp3(){
    int n = 0;
    std::string cmd;
    while (cin >> n >> cmd){
        player obj(n);
        for(int i = 0;i < cmd.size();i++){
            if(cmd[i]=='U')
                obj.up();
            else{
                obj.down();
            }
        }
        for(int i = obj.cur_list_;i <= min(obj.cur_list_ + 3,obj.total_);i++){
            if(i != obj.cur_list_)
                std::cout<<" ";
            std::cout<<i;
        }
        std::cout<< std::endl;
        std::cout<<obj.cur_song_<<std::endl;
    }
}


//sliding window
void dna(){
    std::string s;
    while(cin >> s){
        int target_len;
        cin >> target_len;
        int g_cnt = 0;
        int c_cnt = 0;
        std::string max_s;
        double max_ratio = 0;
        int l = s.length();
        int left = 0;
        int right = left;
        int cnt = 0;
        while(right < l && right - left + 1 < target_len){
            if(s[right] == 'G' || s[right] == 'C'){
                cnt++;
            }
            right++;
        }
        double ratio = double(cnt)/double(target_len);
        if(ratio > max_ratio){
            max_ratio = ratio;
            max_s = s.substr(left,right - left + 1);
        }
        while(left + target_len <= l){
            if(s[left] == 'G' || s[left] == 'C'){
                cnt--;
            }
            left++;
            right++;
            if(s[right] == 'G' || s[right] == 'C'){
                cnt++;
            }
            double ratio = double(cnt)/double(target_len);
            if(ratio > max_ratio){
                max_ratio = ratio;
                max_s = s.substr(left,right - left + 1);
            }
        }
        std::cout<<max_s<<endl;
    }
}

void one_char(){
    std::string s;
    while(cin>>s){
        std::unordered_map<char,int> m;
        int l = s.length();
        for(int i = 0;i < l;i++){
            m[s[i]]++;
        }
        char c = -1;
        bool find = false;
        for(int i = 0;i < l;i++){
            if(m[s[i]] == 1){
                find = true;
                c = s[i];
                break;
            }
        }
        if(find)
            std::cout<<c<<endl;
        else{
            std::cout<<-1<<endl;
        }
    }
}

void string_add(){
    std::string s1,s2;
    while(cin >> s1 >> s2){
        int l1 = s1.size();
        int l2 = s2.size();
        bool upgrade = false;
        int idx1 = l1 - 1;
        int idx2 = l2 - 1;
        std::vector<char> v;
        while(idx1 >= 0 && idx2 >= 0){
            int cur = s1[idx1] - '0' + s2[idx2] - '0';
            if(upgrade){
                cur++;
            }
            if(cur >= 10){
                upgrade = true;
                cur %= 10;
            }else{
                upgrade = false;
            }
            v.push_back(cur + '0');
            idx1--;
            idx2--;
        }
        while (idx1 >= 0){
            int cur = s1[idx1] - '0';
            if(upgrade){
                cur++;
            }
            if(cur >= 10){
                upgrade = true;
                cur %= 10;
            }else{
                upgrade = false;
            }
            v.push_back(cur + '0');
            idx1--;
        }
        while (idx2 >= 0){
            int cur = s2[idx2] - '0';
            if(upgrade){
                cur++;
            }
            if(cur >= 10){
                upgrade = true;
                cur %= 10;
            }else{
                upgrade = false;
            }
            v.push_back(cur + '0');
            idx2--;
        }
        if(upgrade)
            v.push_back('1');
        std::reverse(v.begin(), v.end());
        std::string res(v.begin(),v.end());
        std::cout<<res<<endl;
    }
}

void seven(){
    int n = 0;
    while(cin >> n){
        int cnt = 0;
        for(int i = 7;i <= n;i++){
            if(i % 7 == 0){
                cnt++;
            }else{
                string s = to_string(i);
                if(s.find('7') != string::npos){
                    cnt++;
                }
            }
        }
        std::cout<<cnt<<endl;
    }
}

int recursive_calc(std::string& s) {
    int l = s.length();
    int i = 0;
    int sum = 0;
    std::stack<int> st;
    int cur_num = 0;
    char last_opt = '+';
    while (i < l) {
        while (i < l && s[i] >= '0' && s[i] <= '9') {
            cur_num *= 10;
            cur_num += s[i] - '0'; s[0] = 'd';
            i++;
        }
        if (s[i] == '(') {
            int j = i + 1;
            int tag = 1;
            while (j < l) {
                if (s[j] == '(') {
                    tag++;
                }
                else if (s[j] == ')') {
                    tag--;
                }
                if (tag == 0)
                    break;
                j++;
            }
            std::string s2 = s.substr(i + 1, j - i - 1);
            cur_num = recursive_calc(s2);
            i = j + 1;
        }
        else if (last_opt == '+') {
            st.push(cur_num);
            last_opt = s[i];
            cur_num = 0;
            i++;
        }
        else if (last_opt == '-') {
            st.push(-cur_num);
            last_opt = s[i];
            cur_num = 0;
            i++;
        }
        else if (last_opt == '*') {
            st.top() *= cur_num;
            last_opt = s[i];
            cur_num = 0;
            i++;
        }
        else if (last_opt == '/') {
            st.top() /= cur_num;
            last_opt = s[i];
            cur_num = 0;
            i++;
        }
    }
    if (cur_num != 0) {
        if (last_opt == '+') {
            st.push(cur_num);
        }
        else if (last_opt == '-') {
            st.push(-cur_num);
        }
        else if (last_opt == '*') {
            st.top() *= cur_num;
        }
        else if (last_opt == '/') {
            st.top() /= cur_num;
        }
    }
    while (!st.empty()) {
        sum += st.top();
        st.pop();
    }
    return sum;
}

void calc() {
    //输入字符串长度不超过 100 ，合法的字符包括 ”+, -, *, /, (, )” ， ”0-9” 
    std::string input;
    while (getline(cin, input)) {
        int ret = recursive_calc(input);
        std::cout << ret << endl;
    }
}

int dp_word_distance(string& word1, string& word2, int idx1, int idx2, int l1, int l2, std::vector<std::vector<int>>& memo) {
    if (idx1 == l1)
        return l2 - idx2;
    if (idx2 == l2)
        return l1 - idx1;
    if (memo[idx1][idx2] != -1)
        return memo[idx1][idx2];

    int res = 1 << 31 - 1;
    if (word1[idx1] == word2[idx2]) {
        res = min(res, dp_word_distance(word1, word2, idx1 + 1, idx2 + 1, l1, l2, memo));
    }
    res = min(res, 1 + dp_word_distance(word1, word2, idx1 + 1, idx2, l1, l2, memo));
    res = min(res, 1 + dp_word_distance(word1, word2, idx1 + 1, idx2, l1, l2, memo));
    res = min(res, 1 + dp_word_distance(word1, word2, idx1, idx2 + 1, l1, l2, memo));
    //res = min(res, 2 + dp_word_distance(word1, word2, idx1 + 1, idx2 + 1, l1, l2, memo));
    memo[idx1][idx2] = res;
    return res;
}

void word_distance() {
    //许可的编辑操作包括将一个字符替换成另一个字符，插入一个字符，删除一个字符
    std::string word1, word2;
    while (cin >> word1 >> word2) {
        int l1 = word1.length();
        int l2 = word2.length();
        //std::vector<std::vector<int>> memo(l1, std::vector<int>(l2));
        //auto res = dp_word_distance(word1, word2, 0, 0, l1, l2, memo);
        //std::cout << res << endl;
        std::vector<std::vector<int>> dp(l1 + 1, std::vector<int>(l2 + 1));//dp[i][j] 字符串word1的i个字符串 变成word2的j个字符串要的最小编辑距离
        for (int i = 1; i <= l2; i++) {//只能执行添加,针对word1
            dp[0][i] = i;
        }
        for (int i = 1; i <= l1; i++) {//只能执行删除,针对word1
            dp[i][0] = i;
        }
        for (int i = 1; i <= l1; i++) {
            for (int j = 1; j <= l2; j++) {
                int opt_del_word1 = 1 + dp[i - 1][j];//删除和插入是一回事
                int opt_del_word2 = 1 + dp[i][j - 1];
                int opt_replace = dp[i - 1][j - 1];//修改
                if (word1[i] != word2[j])//如果相等，就等于dp[i - 1][j - 1]
                    opt_replace++;

                dp[i][j] = min(min(opt_del_word1, opt_del_word2), opt_replace);
            }
        }
    std:; cout << dp[l1][l2] << endl;

    }
}


struct listnode {
    int val = 0;
    listnode* next = nullptr;
};

listnode* deletenode(listnode* node, int val) {
    listnode* dummy = new listnode;
    dummy->next = node;
    listnode* pre = dummy;
    //std::vector<listnode*> to_del;
    while (node != nullptr) {
        while (node != nullptr && node->val == val) {
            node = node->next;
        }
        pre->next = node;
        pre = node;
        node = node->next;
    }
    //auto new_haed = dummy->next;
    //delete(dummy);
    //dummy = nullptr;
    return dummy->next;
}

void delete_list() {
    // 6 2 1 2 3 2 5 1 4 5 7 2 2
//则第一个参数6表示输入总共6个节点，第二个参数2表示头节点值为2，剩下的2个一组表示第2个节点值后面插入第1个节点值，为以下表示:
//    1 2 表示为
//        2->1
//        链表为2->1
    int n;
    //std::string input;
    int head_val;
    std::unordered_map<int, listnode*> m;
    //while(getline(std::cin, input)) {
    while (cin >> n >> head_val) {
        //stringstream ss(input);
        //ss >> n;

        //ss >> head_val;
        std::unordered_map<int, listnode*> m;
        listnode* head = new listnode();
        head->val = head_val;
        m[head_val] = head;
        for (int i = 0; i < n - 1; i++) {
            int from = 0;
            int to = 0;
            cin >> to;
            cin >> from;
            listnode* node1 = nullptr;
            if (m.find(from) == m.end()) {
                node1 = new listnode();
                node1->val = from;
                m[from] = node1;
            }
            else {
                node1 = m[from];
            }
            listnode* node2 = nullptr;
            if (m.find(to) == m.end()) {
                node2 = new listnode();
                node2->val = to;
                m[to] = node2;
            }
            else {
                node2 = m[to];
            }
            //node2->next = node1;
            auto oldto = node1->next;
            node2->next = oldto;
            node1->next = node2;
        }
        int delete_val = 0;
        cin >> delete_val;
        auto new_head = deletenode(head, delete_val);
        auto visit = new_head;
        while (visit != nullptr) {
            if (visit != new_head) {
                std::cout << " ";
            }
            std::cout << visit->val;
            visit = visit->next;
        }
    }
}

void beauty() {
    //2
    //zhangsan
    //    lisi
    int n;
    while (cin >> n) {
        std::vector<int> res(n);
        for (int i = 0; i < n; i++) {
            std::string word;
            cin >> word;
            int cnt[26]{};
            for (auto c : word) {
                cnt[c - 'a']++;
            }
            std::vector<int> record;
            for (int i = 0; i < 26; i++) {
                if (cnt[i] != 0)
                    record.push_back(cnt[i]);
            }
            sort(record.begin(), record.end());
            int sum = 0;
            int score = 26;
            for (int i = record.size() - 1; i >= 0; i--) {
                sum += record[i] * score;
                score--;
            }
            res[i] = sum;
        }
        for (int i = 0; i < n; i++) {
            std::cout << res[i] << std::endl;
        }
    }
}

void maza() {
    int rows, columns;
    while (cin >> rows >> columns) {
        //cin.ignore();
        std::vector<std::vector<int>> data(rows, std::vector<int>(columns));
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                int val = 0;
                cin >> val;
                if (val == 1)
                    data[i][j] = -1;
            }
        }

        std::queue<std::pair<int, int>> q;
        q.push({ 0,0 });
        data[0][0] = 1;
        std::vector<std::vector<int>> dirs{ {-1,0},{1,0},{0,-1},{0,1} };
        int steps = 2;
        while (!q.empty()) {
            int len = q.size();
            bool find = false;
            for (int i = 0; i < len; i++) {
                auto cur = q.front();
                if (cur.first == rows - 1 && cur.second == columns - 1) {
                    find = true;
                    break;
                }
                q.pop();
                for (auto dir : dirs) {
                    int next_r = cur.first + dir[0];
                    int next_c = cur.second + dir[1];
                    if (next_r < 0 || next_r >= rows || next_c < 0 || next_c >= columns) {
                        continue;
                    }
                    if (data[next_r][next_c] == -1) {
                        continue;
                    }
                    if (data[next_r][next_c] == 0) {
                        data[next_r][next_c] = steps;
                        q.push({ next_r,next_c });
                    }
                }
            }
            if (find)
                break;
            steps++;
        }
        std::vector<std::pair<int, int>> trace{ { rows - 1,columns - 1} };
        std::queue<std::pair<int, int>> q2;
        q2.push({ rows - 1,columns - 1 });
        steps = data[rows - 1][columns - 1] - 1;
        while (!q2.empty()) {
            auto cur = q2.front();
            if (cur.first == 0 && cur.second == 0)
                break;
            q2.pop();
            for (auto dir : dirs) {
                int last_r = cur.first + dir[0];
                int last_c = cur.second + dir[1];
                if (last_r < 0 || last_r >= rows || last_c < 0 || last_c >= columns) {
                    continue;
                }
                if (data[last_r][last_c] == -1) {
                    continue;
                }
                if (data[last_r][last_c] == steps)
                {
                    q2.push({ last_r,last_c });
                    trace.push_back({ last_r,last_c });
                }
            }
            steps--;
        }
        for (int i = trace.size() - 1; i >= 0; i--) {
            std::cout << "(" << trace[i].first << "," << trace[i].second << ")" << endl;
        }
    }
}

void recr_weight(std::vector<std::pair<int, int>>& data, int l, int idx, int weight, std::unordered_set<int>& s) {
    if (idx == l) {
        s.insert(weight);
        return;
    }
    for (int i = 0; i <= data[idx].second; i++) {
        recr_weight(data, l, idx + 1, weight + data[idx].first * i, s);
    }
}

void weight() {
    //对于每组测试数据：
    //第一行：n-- - 砝码的种数(范围[1, 10])
    //    第二行：m1 m2 m3 ... mn-- - 每种砝码的重量(范围[1, 2000])
    //    第三行：x1 x2 x3 ....xn-- - 每种砝码对应的数量(范围[1, 10])
    int cnt;
    while (cin >> cnt) {
        cin.ignore();
        std::string line1, line2;
        getline(cin, line1);
        getline(cin, line2);
        std::stringstream ss1(line1);
        int weight = 0;
        std::vector<std::pair<int, int>> data(cnt);
        int idx = 0;
        while (ss1 >> weight) {
            data[idx].first = weight;
            idx++;
        }
        std::stringstream ss2(line2);
        int num = 0;
        idx = 0;
        while (ss2 >> num) {
            data[idx].second = num;
            idx++;
        }
        std::unordered_set<int> s;
        s.insert(0);
        //recr_weight(data, data.size(), 0, 0, s);
        for (int i = 0; i < cnt; i++) {
            std::unordered_set<int> s2 = s;
            for (int j = 1; j <= data[i].second; j++) {
                for (auto it = s2.begin(); it != s2.end(); it++) {
                    s.insert(*it + data[i].first * j);
                }
            }
        }
        std::cout << s.size() << endl;
    }
}


void fall_ball() {
    double height = 0;
    cin >> height;
    height *= 100000;
    int n = 5;
    double sum = height;
    height /= 2;
    do {
        sum += height * 2;
        height /= 2;
        n--;
    } while (n > 1);
    double d = double(sum) / double(100000);
    std::cout << d << std::endl;
    std::cout << double(height) / double(100000) << std::endl;
}

void crypt2() {
    //TRAILBLAZERS
    //A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
    //T R A I L B Z E S C D F G H J K M N O P Q U V W X Y(实际需建立小写字母的字母表，此字母表仅为方便演示）
    std::string key;
    getline(cin, key);
    std::string word;
    getline(cin, word);
    char arr[26];
    std::vector<bool> visited(26);
    int l = key.size();
    std::string new_key;
    for (int i = 0; i < l; i++) {
        if (!visited[key[i] - 'a']) {
            visited[key[i] - 'a'] = true;
            new_key.push_back(key[i]);
        }
    }
    char new_letter[26];
    int index = 0;
    int l2 = new_key.length();
    for (int i = 0; i < l2; i++) {
        new_letter[index] = new_key[i];
        index++;
    }
    for (int i = 0; i < 26; i++) {
        if (!visited[i]) {
            new_letter[index] = i + 'a';
            index++;
        }
    }
    std::string res;
    for (int i = 0; i < word.size(); i++) {
        res.push_back(new_letter[word[i] - 'a']);
    }
    std::cout << res << endl;

}

void ip_change() {
    //39.66.68.72
    //3868643487

    //658654280
    //230.150.208.159
    std::string line1;
    getline(cin, line1);
    stringstream ss1(line1);

    std::string line2;
    getline(cin, line2);
    //stringstream ss2(line2);

    int num;
    std::string s_num;
    std::vector<int> v;
    while (getline(ss1, s_num, '.')) {
        int i = stoi(s_num);
        v.push_back(i);
    }
    long long total = 0;
    int num_cnt = 0;
    for (int i = v.size() - 1; i >= 0; i--) {
        int n = v[i];
        long long offset = 0;
        for (int j = 0; j < 8; j++) {
            if ((n | (static_cast <long long>(1) << offset)) == n) {
                total |= static_cast<long long>(1) << (offset + (num_cnt * 8));
            }
            offset++;
        }
        num_cnt++;
    }

    //second line
    long long num2 = stoll(line2);
    int n1 = 0;
    int n2 = 0;
    int n3 = 0;
    int n4 = 0;
    for (int i = 0; i < 8; i++) {
        long long offset = static_cast<long long>(1) << i;
        if ((num2 | offset) == num2) {
            n4 |= 1 << i;
        }
    }
    for (int i = 8; i < 16; i++) {
        long long offset = static_cast<long long>(1) << i;
        if ((num2 | offset) == num2) {
            n3 |= 1 << (i - 8);
        }
    }
    for (int i = 16; i < 24; i++) {
        long long offset = static_cast<long long>(1) << i;
        if ((num2 | offset) == num2) {
            n2 |= 1 << (i - 16);
        }
    }
    for (int i = 24; i < 32; i++) {
        long long offset = static_cast<long long>(1) << i;
        if ((num2 | offset) == num2) {
            n1 |= 1 << (i - 24);
        }
    }
    std::cout << total << endl;
    std::cout << n1 << "." << n2 << "." << n3 << "." << n4 << endl;
}


void check_letter() {
    string line1;
    getline(cin, line1);
    std::stringstream ss(line1);
    std::string word;
    std::unordered_set<std::string> record;
    while (ss >> word) {
        std::sort(word.begin(), word.end());
        record.insert(word);
    }
    string line2;
    getline(cin, line2);
    std::stringstream ss2(line2);
    bool find = true;
    while (ss2 >> word) {
        std::sort(word.begin(), word.end());
        if (record.find(word) == record.end()) {
            find = false;
            break;
        }
    }
    if (find)
        std::cout << "true" << endl;
    else
        std::cout << "false" << endl;
}

void check_area(){
    //2 5 2 6
    //1 3 4 5 8
    //2 3 6 7 1

    int rows,columns,edge_len,ele_num;
    cin >> rows >> columns >> edge_len >> ele_num;
    cin.ignore();
    int n2 = rows;
    std::vector<std::vector<int>> graph(rows,std::vector<int>(columns));
    std::vector<std::vector<int>> dp(rows,std::vector<int>(columns));
    int r = 0;
    while (n2 > 0){
        std::string line;
        getline(cin,line);
        stringstream ss(line);
        int val;
        int c = 0;
        while (ss >> val){
            graph[r][c] = val;
            c++;
        }
        r++;
        n2--;
    }
    dp[0][0] = graph[0][0];
    for(int r = 1;r < rows;r++){
        dp[r][0] =  dp[r - 1][0] + graph[r][0];
    }
    for(int c = 1;c < columns;c++){
        dp[0][c] = dp[0][c - 1] + graph[0][c];
    }
    for(int r = 1;r < rows;r++){
        for(int c = 1;c < columns;c++){
            dp[r][c] = graph[r][c] + dp[r-1][c] + dp[r][c - 1] - dp[r-1][c - 1];
        }
    }
    int res = 0;
    for(int r = edge_len - 1;r < rows;r++){
        for(int c = edge_len - 1;c < columns;c++){
            int pre_r = r - edge_len;
            int pre_c = c - edge_len;
            int sum = dp[r][c];
            if(pre_r >= 0){
                sum -= dp[pre_r][c];
            }
            if(pre_c >= 0){
                sum -= dp[r][pre_c];
            }
            if(pre_r >= 0 && pre_c >= 0){
                sum += dp[pre_r][pre_c];
            }
            if(sum >= ele_num){
                res++;
            }
        }
    }
    std::cout<< res << endl;
}


int check_password(std::string s,int l,int mid1,int mid2){
    int left = mid1 - 1;
    int right = mid2 + 1;
    while (left >= 0 && right < l){
        if(s[left] != s[right]){
            break;
        }
        left--;
        right++;
    }
    int cur_len = right - left - 1;
    return cur_len;
}

void get_password(){
//12HHHHA
    std::string s;
    while(cin>>s){
        int max_len = 0;
        int l = s.length();
        for(int i = 0;i < l - 1;i++){
            int ret1 = check_password(s,l,i,i);
            max_len = max(max_len,ret1);
            if(s[i] == s[i + 1]){
                int ret2 = check_password(s,l,i,i + 1);
                max_len = max(max_len,ret2);
            }
        }
        std::cout<<max_len<<std::endl;
    }
}

void reverse_sentence(){
    //$bo*y gi!r#l
    std::string line;
    std::vector<std::string> v;
    while(getline(cin,line)){
        int l = line.size();
        int left = 0;
        int right = 0;
        while (left < l){
            while(left < l){
                if((line[left] >= 'a' && line[left] <= 'z') || (line[left] >= 'A' && line[left] <= 'Z')){
                    break;
                }
                left++;
            }
            right = left + 1;
            while (right < l && ((line[right] >= 'a' && line[right] <= 'z') || (line[right] >= 'A' && line[right] <= 'Z'))){
                right++;
            }
            int cur_len = right - left;
            v.push_back(line.substr(left,cur_len));
            left = right + 1;
        }
        for(int i = v.size() - 1;i >= 0;i--){
            if(i != v.size() - 1){
                std::cout<< " ";
            }
            std::cout<<v[i];
        }
        std::cout<<endl;
    }
}

void merge_string(){
    std::string s1,s2;
    while(cin>> s1 >> s2) {
        std::string s = s1 + s2;
        int l = s.length();
        std::vector<char> data_odd(l / 2);
        std::vector<char> data_even(l / 2 + l % 2);
        int odd_idx = 0;
        int even_idx = 0;
        for (int i = 0; i < l; i++) {
            if (i % 2 == 0) {
                data_even[even_idx] = s[i];
                even_idx++;
            } else {
                data_odd[odd_idx] = s[i];
                odd_idx++;
            }
        }
        std::sort(data_odd.begin(), data_odd.end());
        std::sort(data_even.begin(), data_even.end());
        //如字符 'C'，代表的十进制是 12 ，其二进制为 1100 ，则翻转后为 0011，也就是3。转换后的字符是 '3'。
        std::string s_new;
        even_idx = 0;
        odd_idx = 0;
        for (int i = 0; i < l; i++) {
            char c;
            if (i % 2 == 0) {
                c = data_even[even_idx];
                even_idx++;
            } else {
                c = data_odd[odd_idx];
                odd_idx++;
            }
            int num = 0;
            bool change = false;
            if (c >= '0' && c <= '9') {
                num = c - '0';
                change = true;
            } else if (c >= 'a' && c <= 'f') {
                num = c - 'a' + 10;
                change = true;
            } else if (c >= 'A' && c <= 'F') {
                num = c - 'A' + 10;
                change = true;
            } else {
                s_new += c;
            }

            if (change) {
                std::bitset<4> b(num);
                auto get = b.to_string();
                std::reverse(get.begin(), get.end());
                int num2 = 0;
                int offset = 0;
                for (int i = get.length() - 1; i >= 0; i--) {
                    if (get[i] - '0' == 1) {
                        num2 += 1 << offset;
                    }
                    offset++;
                }
                char next_num;;
                if (num2 >= 0 && num2 <= 9) {
                    next_num = num2 + '0';
                } else if (num2 >= 10) {
                    next_num = 'A' + num2 - 10;
                }
                //char next_num = reverse_bits(num);
                s_new += next_num;
            }
        }
        std::cout << s_new << endl;
    }
}

void brother(){
    //3 abc bca cab abc 1
    int n;
    cin>>n;
    int n2 = n;
    std::vector<std::string> v;
    while (n2 > 0){
        std::string word;
        cin >> word;
        v.push_back(word);
        n2--;
    }
    std::string target;
    std::cin>>target;
    int k;
    cin >> k;
    std::sort(v.begin(),v.end());
    int l = target.length();
    int target_cnt[26]{};
    for(int i = 0;i < l;i++){
        target_cnt[target[i] - 'a']++;
    }
    std::string res;
    int total = 0;
    for(int i = 0;i < n;i++){
        int l1 = v[i].length();
        if(l != l1){
            continue;
        }
        if(v[i] == target)
            continue;
        int cnt[26]{};
        for(int j = 0;j < l;j++){
            cnt[v[i][j] - 'a']++;
        }
        bool find = true;
        for(int j = 0;j < 26;j++){
            if(target_cnt[j] != cnt[j]){
                find = false;
                break;
            }
        }
        if(find){
            total++;
            k--;
            if(k == 0){
                res = v[i];
                //break;
            }
        }
    }
    std::cout<<total << endl;
    std::cout<< res<<endl;
}

void crypt(){
    //加密方法为：
    //当内容是英文字母时则用该英文字母的后一个字母替换，同时字母变换大小写,如字母a时则替换为B；字母Z时则替换为a；
    //当内容是数字时则把该数字加1，如0替换1，1替换2，9替换0；
    //第一行输入一串要加密的密码
    //第二行输入一串加过密的密码
    //
    //输出描述：
    //第一行输出加密后的字符
    //第二行输出解密后的字符
    std::string line1;
    getline(cin , line1);
    int l1 = line1.length();
    std::string s1;
    for(int i = 0;i < l1;i++){
        if(line1[i] >= '0'&& line1[i] <= '9'){
            int next_n = (line1[i] - '0' + 1) % 10;
            s1 += (char(next_n + '0'));
        }else if(line1[i] >= 'a'&& line1[i] <= 'z'){
            int offset = line1[i] - 'a';
            offset = (offset + 1)%26;
            s1 += char('A' + offset);
        }else if(line1[i] >= 'A'&& line1[i] <= 'Z'){
            int offset = line1[i] - 'A';
            offset = (offset + 1)%26;
            s1 += char('a' + offset);
        }
    }
    std::string line2;
    getline(cin , line2);
    int l2 = line2.length();
    std::string s2;
    for(int i = 0;i < l2;i++){
        if(line2[i] >= '0'&& line2[i] <= '9'){
            int last_n = (line2[i] - '0' + 10 - 1) % 10;
            s2 += (char(last_n + '0'));
        }else if(line2[i] >= 'a'&& line2[i] <= 'z'){
            int offset = line2[i] - 'a';
            offset = (offset + 26 - 1)%26;
            s2 += char('A' + offset);
        }else if(line2[i] >= 'A'&& line2[i] <= 'Z'){
            int offset = line2[i] - 'A';
            offset = (offset + 26 - 1)%26;
            s2 += char('a' + offset);
        }
    }
    std::cout<<s1<<endl;
    std::cout<<s2<<endl;
}

void sort_letter(){
//A Famous Saying: Much Ado About Nothing (2012/8).
//A aaAAbc dFgghh: iimM nNn oooos Sttuuuy (2012/8).
    std::string line;
    std::getline(cin,line);
    int l = line.size();
    std::vector<std::vector<char>> data(26);
    std::unordered_map<int,char> m;
    for(int i = 0;i < l;i++){
        if((line[i] >= 'a' && line[i] <= 'z') ){
            data[line[i] - 'a'].push_back(line[i]);
        }else if(line[i] >= 'A' && line[i] <= 'Z'){
            data[line[i] - 'A'].push_back(line[i]);
        }else{
            m[i] = line[i];
        }
    }
    int index = 0;
    int char_index = 0;
    int offset_index = 0;
    while (data[char_index].size() == 0){
        char_index++;
    }
    char add[l + 1];
    for(int i = 0;i < l;i++){
        if(m.find(i) != m.end()){
            add[i] = m[i];
        }else{
            add[i] = data[char_index][offset_index];
            offset_index++;
            if (offset_index >= data[char_index].size()){
                char_index++;
                offset_index = 0;
            }
            while (char_index <= 26 && data[char_index].size() == 0){
                char_index++;
            }
        }
    }
    add[l] = '\0';
    std::string str(add,l);
    std::cout<< str << endl;
}

void singing_queue(){
    //8
    //186 186 150 200 160 130 197 200
    int n;
    cin>> n;
    int cnt = n;
    std::vector<int> height;
    while (cnt > 0){
        int h;
        cin >>h;
        height.push_back(h);
        cnt--;
    }
    std::vector<int> dp_prefix(n);
    std::vector<int> dp_suffix(n);
    dp_prefix[0] = 1;
    dp_suffix[n - 1] = 1;
    for(int i = 1;i < n;i++){
        dp_prefix[i] = 1;
        for(int j = i - 1;j >= 0;j--){
            if(height[i] > height[j]){
                dp_prefix[i] = max(dp_prefix[i],dp_prefix[j] + 1);
            }
        }
    }
    for(int i = n - 2;i >= 0;i--){
        dp_suffix[i] = 1;
        for(int j = i + 1;j < n;j++){
            if(height[i] > height[j]){
                dp_suffix[i] = max(dp_suffix[i],dp_suffix[j] + 1);
            }
        }
    }
    int max_len = 0;
    for(int i = 0;i < n;i++){
        if(i == 0){
            max_len = max(max_len,dp_suffix[i]);
        }else if(i == n - 1){
            max_len = max(max_len,dp_prefix[i]);
        }else{
            max_len = max(max_len,dp_prefix[i] + dp_suffix[i] - 1);
        }
    }
    std::cout<< n - max_len;
}

void check_password(){
    //1.长度超过8位
    //2.包括：大写字母/小写字母/数字/其它符号，以上四种至少三种
    //3.不能分割出两个相等的长度大于 2 的子串，例如 abcabc 可以分割出两个 abc，不合法，ababa 则无法分割出2个aba。
    //注：其他符号不含空格或换行
    std::string line;
    while(getline(cin,line)){
        //std::stringstream ss(line);
        int l = line.length();
        if(l <= 8){
            std::cout<<"NG"<<endl;
            continue;
        }
        bool small_letter = false;
        bool big_letter = false;
        bool digital = false;
        bool special = false;
        bool fail = false;
        for(int i = 0;i < l;i++){
            if(line[i] >= 'a' && line[i] <= 'z'){
                small_letter = true;
            }else if(line[i] >= 'A' && line[i] <= 'Z'){
                big_letter = true;
            }else if(line[i] >= '0' && line[i] <= '9'){
                digital = true;
            }else if(line[i] == ' ' || line[i] == '\n'){
                fail = true;
                break;
            }else{
                special = true;
            }
        }
        for(int i = 0;i + 2 < l;i++){
            std::string target = line.substr(i,3);
            for(int j = i + 3;j < l;j++){
                if(target == line.substr(j,3)){
                    fail = true;
                    break;
                }
            }
            if(fail)
                break;
        }
        if(fail){
            std::cout<<"NG"<<endl;
            continue;
        }
//        if(l/2 == 0 && line.substr(0,l/2) == line.substr(l/2,l/2)){
//            std::cout<<"NG"<<endl;
//            continue;
//        }
        int scores = 0;
        if(small_letter)
            scores++;
        if(big_letter)
            scores++;
        if(digital)
            scores++;
        if(special)
            scores++;
        if(scores >= 3) {
            std::cout << "OK" << endl;
        }else{
            std::cout << "NG" << endl;
        }
    }
}

class shaizi{
    int left_ = 1;
    int right_ = 2;
    int forward_ = 3;
    int back_ = 4;
    int up_ = 5;
    int down_ = 6;
public:
    void left(){
        int tmp = left_;
        left_ = up_;
        up_ = right_;
        right_ = down_;
        down_ = tmp;
    }
    void right(){
        int tmp = right_;
        right_ = up_;
        up_ = left_;
        left_ = down_;
        down_ = tmp;
    }
    void forward(){
        int tmp = up_;
        up_ = back_;
        back_ = down_;
        down_ = forward_;
        forward_ = tmp;
    }
    void backward(){
        int tmp = up_;
        up_ = forward_;
        forward_ = down_;
        down_ = back_;
        back_ = tmp;
    }
    void clockwise(){
        int tmp = forward_;
        forward_ = left_;
        left_ = back_;
        back_ = right_;
        right_ = tmp;
    }
    void countclockwise(){
        int tmp = forward_;
        forward_ = right_;
        right_ = back_;
        back_ = left_;
        left_ = tmp;
    }
    void print(){
        std::cout<<to_string(left_) + to_string(right_)+ to_string(forward_)+
                   to_string(back_)+ to_string(up_)+ to_string(down_) << std::endl;
    }
};

void rotate(){
//骰子是一个正方体，每个面有一个数字，初始为左 1，右 2，前 3，后 4，上 5，下 6，
//可以向左翻转（用 L 表示向左翻转 1 次）；
//可以向右翻转（用 R 表示向右翻转 1 次）；
//可以向前翻转（用 F 表示向前翻转 1 次）；
//可以向后翻转（用 B 表示向后翻转 1 次）；
//可以逆时针翻转（用 A 表示向逆时针翻转 1 次）；
//可以向顺时针翻转（用 C 表示向顺时针翻转 1 次）；
    std::string line;
    std::getline(cin,line);
    shaizi obj;
    for(int i = 0;i < line.length();i++){
        if(line[i] == 'L'){
            obj.left();
        }else if(line[i] == 'R'){
            obj.right();
        }else if(line[i] == 'F'){
            obj.forward();
        }else if(line[i] == 'B'){
            obj.backward();
        }else if(line[i] == 'A'){
            obj.countclockwise();
        }else if(line[i] == 'C'){
            obj.clockwise();
        }
    }
    obj.print();
}

void count_good(){
//第一行输入为新员工数量N，表示新员工编号为0到N-1，N的范围为[1,100]
//第二行输入为30个整数，表示每天打卡的员工数量，每天至少有1名员工打卡
//之后30行表示每天打开的员工id集合，id不会重复

    int n;
    std::cin>> n;
    std::vector<int> days_cnt(30);
    int everyday_cnt;
    int days = 0;
    int read_cnt = 30;
    while (read_cnt > 0){
        cin>>everyday_cnt;
        days_cnt[days] = everyday_cnt;
        days++;
        read_cnt--;
    }
    std::vector<std::vector<int>> id_cnt_firsttime(n);
    //每天打卡的id号
    for(int i = 0;i < 30;i++){//天
        for(int j = 0;j < days_cnt[i];j++){ //id
            int id_no;
            std::cin >> id_no;
            if(id_cnt_firsttime[id_no].size() == 0){
                id_cnt_firsttime[id_no] = {1,i,id_no};
            }else{
                id_cnt_firsttime[id_no][0]++;
            }
        }
    }
    std::sort(id_cnt_firsttime.begin(),id_cnt_firsttime.end(),[&](const std::vector<int>& p1,const std::vector<int>& p2)->bool{
        if(p1.size() == 0)
            return false;
        if(p2.size() == 0)
            return true;
        if(p1[0] == p2[0]){
            if(p1[1] == p2[1]){
                return p1[2] < p2[2];
            }
            return p1[1] < p2[1];
        }else{
            return p1[0] > p2[0];
        }
    });
    std::string res;
    for(int i = 0;i < 5 && i < id_cnt_firsttime.size();i++){
        if(id_cnt_firsttime[i].size() > 0){
            if(res.length() != 0){
                res += " ";
            }
            res += to_string(id_cnt_firsttime[i][2]);
        }
    }
    std::cout << res << std::endl;
}

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


void move(){
//A10;S20;W10;D30;X;A1A;B10A11;;A10;
//A表示向左移动，D表示向右移动，W表示向上移动，S表示向下移动
    std::string line;
    std::getline(cin,line);
    std::stringstream ss(line);
    std::string ele;
    int x_pos = 0;
    int y_pos = 0;
    while (getline(ss,ele,';')){
        int step = 0;
        try{
            if(ele.length() == 2){
                step = stoi(ele.substr(1,1));
                auto check = std::to_string(step);
                if(check != ele.substr(1,1))
                    continue;
            }else if(ele.length() == 3){
                step = stoi(ele.substr(1,2));
                auto check = std::to_string(step);
                if(check != ele.substr(1,2))
                    continue;
            }else{
                continue;
            }
        }catch(std::exception ex) {
            continue;
        }
        if(ele[0]=='A'){
            x_pos -= step;
        }else if(ele[0]=='D'){
            x_pos += step;
        }else if(ele[0]=='W'){
            y_pos += step;
        }else if(ele[0]=='S'){
            y_pos -= step;
        }
    }
    std::cout<<x_pos<<","<<y_pos<<std::endl;
}

int union_find(std::vector<int> groups,int cur){
    if(groups[cur] != cur){
        groups[cur] = union_find(groups,groups[cur]);
    }
    return groups[cur];
}

void broadcast(){
    //1 0 0
    //0 1 0
    //0 0 1
    std::string line;
    std::getline(std::cin,line);
    std::stringstream ss(line);
    std::string s_num;
    std::vector<int> first;
    while(getline(ss,s_num,' ')){
        first.push_back(stoi(s_num));
    }
    std::vector<std::vector<int>> graph(first.size());
    graph[0] = first;
    int graph_idx = 1;
    int rows = first.size() - 1;
    while (rows > 0){
        std::getline(std::cin,line);
        std::stringstream ss2(line);
        std::vector<int> v2;
        while(getline(ss2,s_num,' ')){
            v2.push_back(stoi(s_num));
        }
        graph[graph_idx] = v2;
        graph_idx++;
        rows--;
    }
    int cnt = 0;
    int l = graph.size();
    std::vector<int> groups(l);
    for(int i = 0;i < l;i++){
        groups[i] = i;
    }
    for(int i = 0;i < graph.size();i++){
        for(int j = 0;j < graph[i].size();j++){
            if(i == j)
                continue;
            if(graph[i][j] == 1){
                int group1 = union_find(groups,i);
                int group2 = union_find(groups,j);
                if(group1 != group2){
                    groups[group2] = group1;
                }
            }
        }
    }
    std::unordered_set<int> set;
    for(int i = 0;i < l;i++){
        set.insert(groups[i]);
    }
    std::cout<<set.size() << std::endl;
}

void poker(){
    //4 H
    //5 S
    //6 C
    //7 D
    //8 D
    std::map<std::string,int> color_val;
    color_val["H"] = 1;
    color_val["S"] = 2;
    color_val["C"] = 3;
    color_val["D"] = 4;
    std::vector<std::unordered_set<int>> num_color(15);
    int n = 5;
    while(n > 0){
        std::string line;
        getline(cin,line);
        std::stringstream ss(line);
        std::string s_num;
        std::string color;
        ss>>s_num>>color;
        if(s_num == "A"){
            num_color[1].insert(color_val[color]);
        }else if(s_num == "J"){
            num_color[11].insert(color_val[color]);
        }else if(s_num == "Q"){
            num_color[12].insert(color_val[color]);
        }else if(s_num == "K"){
            num_color[13].insert(color_val[color]);
        }else{
            num_color[stoi(s_num)].insert(color_val[color]);
        }
        n--;
    }
    //同花顺
    int left = 1;
    bool find = false;
    while(left <= 14){
        while(left <= 14){
            if(num_color[left].size() != 0)
                break;
            left++;
        }
        int right = left+1;
        int color = *num_color[left].begin();
        while(right <= 14){
            if(num_color[right].size() == 0){
                break;
            }
            int right_color =  *(num_color[right].begin());
            if(right_color != color)
                break;
            right++;
        }
        int cur_len = right - left;
        if(cur_len == 5){
            find = true;
            std::cout<<"1"<<std::endl;
            return;
        }
        break;
    }
    if(num_color[10].size() > 0 && num_color[11].size() > 0 && num_color[12].size() > 0 &&
       num_color[13].size() > 0 && num_color[1].size() > 0 &&
       *num_color[10].begin() == *num_color[11].begin() && *num_color[10].begin() == *num_color[12].begin() &&
       *num_color[10].begin() == *num_color[13].begin() &&  *num_color[10].begin() == *num_color[1].begin()){
        std::cout<<"1"<<std::endl;
        return;
    }
    //炸弹
    for(int i = 0;i <= 14;i++){
        if(num_color[i].size() == 4){
            std::cout<<"2"<<std::endl;
            return;
        }
    }
    //葫芦
    bool find_3 = false;
    bool find_2 = false;
    for(int i = 0;i <= 14;i++){
        if(num_color[i].size() == 3){
            find_3 = true;
        }
        if(num_color[i].size() == 2){
            find_2 = true;
        }
    }
    if(find_2 && find_3){
        std::cout<<"3"<<std::endl;
        return;
    }
    //同花
    int cnt[5] = {0};
    for(int i = 0;i <= 14;i++){
        if(!num_color[i].empty()){
            cnt[*num_color[i].begin()]++;
        }
    }
    for(int i = 1;i <= 4;i++){
        if(cnt[i] == 5){
            std::cout<<"4"<<std::endl;
            return;
        }
    }
    //普通顺子
    left = 1;
    find = false;
    while(left <= 14){
        while (left<=14 && num_color[left].size() == 0){
            left++;
        }
        int right = left + 1;
        while(right <= 14){
            if(num_color[right].size() != 1)
                break;
            right++;
        }
        int cur_len = right - left;
        if(cur_len == 5) {
            std::cout << "5" << endl;
            return;
        }
        break;
    }
    if(num_color[10].size() == 1 && num_color[11].size() == 1 && num_color[12].size() == 1 &&
       num_color[13].size() == 1 && num_color[1].size() == 1){
        std::cout<<"5"<<std::endl;
        return;
    }
    //三条
    find_3 = false;
    for(int i = 1;i <= 4;i++){
        if(num_color[i].size() == 3){
            find_3 = true;
        }
    }
    if(find_3){
        std::cout<<"6"<<std::endl;
        return;
    }
    //其他
    std::cout<< 7<<std::endl;
}

void dfs_delete_folder(std::unordered_map<int,std::vector<int>>& graph,int del_node,std::set<int>& del_list){
    if(del_list.find(del_node) != del_list.end()){
        del_list.erase(del_node);
    }
    for(auto it = graph[del_node].begin();it != graph[del_node].end();it++){
        dfs_delete_folder(graph,*it,del_list);
    }
}

void delete_folder(){
    //5
    //8 6
    //10 8
    //6 0
    //20 8
    //2 6
    //8
    int n;
    std::string s_n;
    getline(cin,s_n);
    n = stoi(s_n);
    std::unordered_map<int,std::vector<int> > graph;
    std::set<int> num_set;
    while(n > 0){
        std::string line;
        getline(cin,line);
        std::stringstream ss(line);
        int cur,parent;
        ss>>cur>>parent;
        graph[parent].push_back(cur);
        num_set.insert(cur);
        num_set.insert(parent);
        n--;
    }
    int delete_node;
    cin>>delete_node;
    //std::unordered_set<int> del_list;
    dfs_delete_folder(graph,delete_node,num_set);
    for(auto it = num_set.begin();it != num_set.end();it++){
        if(it != num_set.begin()){
            std::cout << " ";
        }
        if(*it != 0)
            std::cout << *it;
    }
}

void combine_divide_group(std::vector<int>& v,int idx,int choose_cnt,int cur_sum,int sum,int& min_diff){
    if(idx == v.size()){
        if(choose_cnt == 5){
            int cur_diff = abs(sum - cur_sum - cur_sum);
            min_diff = min(min_diff,cur_diff);
        }
        return;
    }
    //choose current
    combine_divide_group(v,idx + 1,choose_cnt + 1,cur_sum + v[idx],sum,min_diff);
    //skip current
    combine_divide_group(v,idx + 1,choose_cnt,cur_sum,sum,min_diff);
}

void divide_group(){
    //10 9 8 7 6 5 4 3 2 1
    int n;
    std::vector<int> v;
    int sum = 0;
    std::string line;
    std::getline(cin,line);
    std::stringstream ss(line);
    while (ss >> n){
        sum += n;
        v.push_back(n);
    }
    int res = 1 << 31 - 1;
    combine_divide_group(v,0,0,0,sum,res);
    std::cout<< res;
}

void longest_string(){
    //asdbuiodevauufgh
    std::string s;
    std::cin>>s;
    int l = s.length();
    int left = 0;
    int right = 0;
    std::unordered_set<char> set{'a','e','i','o','u','A','E','I','O','U'};
    int max_len = 0;
    while(left < l && right < l){
        while(right < l && set.find(s[right]) != set.end()){
            right++;
        }
        int cur_len = right - left;
        max_len = max(max_len,cur_len);
        left = right + 1;
        right = left;
    }
    std::cout<<max_len<<std::endl;
}

void mars_calculate(){
    //x$y = 3*x+y+2
    //x#y = 2*x+3*y+4
    //火星人公式中，$的优先级高于#，相同的运算符，按从左到右的顺序计算
//7#6$5#12 = =7#(3*6+5+2)#12
    std::string s;
    std::cin >> s;
    std::deque<int> st_num;
    std::deque<char> st_opt;
    int l = s.length();
    for(int i = 0;i < l;){
        if(s[i] == '#'){
            st_opt.push_back('#');
            i++;
        }else if(s[i] == '$'){
            int find_next = i + 1;
            while (find_next < l){
                if(s[find_next] >= '0' && s[find_next] <= '9'){
                    find_next++;
                }else{
                    break;
                }
            }
            int n1 = st_num.back();
            st_num.pop_back();
            int n_len = find_next - i;
            int n2 = stoi(s.substr(i + 1,n_len));
            int n3 = 3 * n1 + n2 + 2;
            st_num.push_back(n3);
            i = find_next;
        }else{
            int find_next = i + 1;
            while (find_next < l){
                if(s[find_next] >= '0' && s[find_next] <= '9'){
                    find_next++;
                }else{
                    break;
                }
            }
            int n_len = find_next - i;
            int n1 = stoi(s.substr(i,n_len));
            st_num.push_back(n1);
            i = find_next;
        }
    }
    //int sum = 0;
    while (!st_opt.empty()){
        int n1 = st_num.front();
        st_num.pop_front();
        int n2 = st_num.front();
        st_num.pop_front();
        st_opt.pop_front();
        //x#y = 2*x+3*y+4
        int n3 = 2 * n1 + 3 * n2 + 4;
        st_num.push_front(n3);
    }
    std::cout<< st_num.front()<<std::endl;
}

void press_key(){
    //1(,.)   2(abc)  3(def)
    //4(ghi)  5(jkl)  6(mno)
    //7(pqrs) 8(tuv)  9(wxyz)
    //#       0(空格)  /
    std::vector<std::vector<char>> num_char(10);
    num_char[1].push_back({','});
    num_char[1].push_back({'.'});
    num_char[2].push_back({'a'});
    num_char[2].push_back({'b'});
    num_char[2].push_back({'c'});

    num_char[3].push_back({'d'});
    num_char[3].push_back({'e'});
    num_char[3].push_back({'f'});

    num_char[4].push_back({'g'});
    num_char[4].push_back({'h'});
    num_char[4].push_back({'i'});

    num_char[5].push_back({'j'});
    num_char[5].push_back({'k'});
    num_char[5].push_back({'l'});

    num_char[6].push_back({'m'});
    num_char[6].push_back({'n'});
    num_char[6].push_back({'o'});

    num_char[7].push_back({'p'});
    num_char[7].push_back({'q'});
    num_char[7].push_back({'r'});
    num_char[7].push_back({'s'});

    num_char[8] = {'t','u','v'};
    num_char[9] = {'w','x','y','z'};

    std::string s;
    std::cin>>s;
    bool digtal_mode = true;
    char pre_c = 0;
    int l = s.length();
    for(int i = 0;i < l;i++){
        if(s[i] == '#'){
            digtal_mode = !digtal_mode;
        }else if(s[i] >= '0' && s[i] <= '9'){
            if(digtal_mode){
                std::cout<< s[i] - '0';
            }else{//英文模式
                if(i == l - 1)
                    std::cout<<s[i];
                if(s[i] != s[i + 1])
                    std::cout<<s[i];
                else{//往后找/
                    int cnt = 0;
                    char c = s[i];
                    while(i < l - 1){
                        if(s[i] != s[i + 1]){
                            break;
                        }
                        i++;
                        cnt++;
                    }
                    std::cout<<num_char[c - '0'][cnt%num_char[c - '0'].size()];
                    if(i < l - 1 && s[i + 1] == '/'){ //跳过
                        i++;
                    }
                }
            }
        }else if(s[i] == '/'){
            if(!digtal_mode){

            }
        }
    }
}

bool perm(std::vector<int>& nums,int l,int idx,int& cnt){
    if(idx == l){
        cnt--;
        if(cnt == 0){
            for(int i = 0;i < l;i++){
                std::cout<< nums[i];
            }
            return false;
        }else{
            return true;
        }
    }
    for(int i = idx;i < l;i++){
        swap(nums[i],nums[idx]);
        bool ret = perm(nums,l,idx + 1,cnt);
        if(!ret){
            return false;
        }
        swap(nums[i],nums[idx]);
    }
    return true;
}

void n_perm(){
    int n;
    std::cin >> n;
    int cnt;
    std::cin>>cnt;
    std::vector<int> v;
    for(int i = 0;i < n;i++){
        v.push_back(i + 1);
    }
    perm(v,n,0,cnt);
}

void check_stack(){
    //5 10 20 50 85 1
    std::string s;
    getline(std::cin,s);
    std::stringstream ss(s);
    std::string s_num;
    std::vector<int> v;
    //std::vector<int> prefix_sum;
    std::unordered_map<int,int> m;//sum,index
    m[0] = -1;
    int sum = 0;
    while (getline(ss,s_num,' ')){
        int n = stoi(s_num);
        if(sum >= n){
            int target = sum - n;
            if(m.find(target) != m.end()) {
                int pre_idx = m[target];
                //delete from prefix + 1 --- len - 1
                int del_cnt = v.size() - pre_idx - 1;
                v.resize(v.size() - del_cnt);
                v.push_back(n * 2);
            }else{
                v.push_back(n);
            }
            sum += n;
            m[sum] = v.size() - 1;
        }else{
            v.push_back(n);
            sum += n;
            m[sum] = v.size() - 1;
        }
    }
    for(int i = v.size() - 1;i >= 0;i--){
        if(i != v.size() - 1)
            std::cout<<" ";
        std::cout<< v[i];
    }
}