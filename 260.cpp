#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

struct node{
    std::unordered_map<int, node*> val;
    std::unordered_map<int, std::pair<std::vector<std::string>, std::vector<int>>> len;

    node() {}

    node(int digit) {
        if (val.find(digit) == val.end()) {
            node* next = new node();
            val[digit] = next;
        }
    }
};

node* insert(node* cur, int digit) {
    if (cur->val.find(digit) == cur->val.end()) {
        node* next = new node();
        cur->val[digit] = next;
    }
    return cur->val[digit];
}

node* find(node* cur, int digit) {
    node* next = cur->val.find(digit)->second;
    return next;
}

int main() {
    int n; std::cin >> n;

    std::vector<std::string> number(n);
    getline(std::cin, number[0]);
    for (int i = 0; i < n; i++) {
        std::string str, num;
        getline(std::cin, str);
        for (size_t i = 0; i < str.size(); i++) {
            if (str[i] - '0' >= 0 && str[i] - '0' <= 9) {
                num.push_back(str[i]);
            }
        }
        number[i] = num;
    }
    
    int m; std::cin >> m;
    
    node* semen = new node();
    for (size_t i = 0; i < m; i++) {
        node* cur = semen;
        std::vector<int> len(3);

        std::string str; std::cin >> str;
        for (size_t j = 1; j < str.size(); j++) {
            cur = insert(cur, str[j] - '0');
        }
        len[0] = str.size() - 1;
        
        std::cin >> str;
        for (size_t j = 1; j < str.size() - 1; j++) {
            cur = insert(cur, str[j] - '0');
        }
        len[1] = str.size() - 2;
        
        std::cin >> str;
        size_t j = 0;
        while(str[j] != 'X' && j < str.size()) {
            cur = insert(cur, str[j] - '0');
            j += 1;
        }
        len[2] = str.size();

        std::vector<std::string> names(2);
        std::cin >> str >> str;
        names[0] = str;
        std::cin >> str;
        names[1] = str;
        cur->len[len[0]+len[1]+len[2]] = std::make_pair(names, len);
    }

    for (size_t i = 0; i < n; i++) {
        size_t j = 0;
        node* cur = semen;
        while(j < number[i].size() && (cur->len.empty() || 
            cur->len.find(number[i].size()) == cur->len.end() )) {
            
            cur = find(cur, number[i][j] - '0');
            j += 1;
        }
        
        std::vector<int> len = cur->len[number[i].size()].second;
        std::vector<std::string> names = cur->len[number[i].size()].first;
        std::string str = "";
        str.push_back('+');
        for (size_t k = 0; k < len[0]; k++) {
            str.push_back(number[i][k]);
        }
        str.append(" (");
        for (size_t k = len[0]; k < len[0] + len[1]; k++) {
            str.push_back(number[i][k]);
        }
        str.append(") ");
        for (size_t k = len[0] + len[1]; k < number[i].size(); k++) {
            str.push_back(number[i][k]);
        }
        str.append(" - ");
        str.append(names[0]);
        str.push_back(' ');
        str.append(names[1]);
        
        std::cout << str << '\n';
    }
}