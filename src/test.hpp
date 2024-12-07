#include <iostream>
#include <sstream>
#include <set>
#include <queue>
#include <map>
#include <unordered_set>
#include <unordered_map>
using namespace std;


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