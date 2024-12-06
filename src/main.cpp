#include <iostream>
#include <sstream>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <map>
#include <queue>
using namespace std;

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


int main() {
    rotate();
    //broadcast();
    //delete_folder();
    //mars_calculate();
    // int a, b;
    // while (cin >> a >> b) { // 注意 while 处理多个 case
    //     cout << a + b << endl;
    // }
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