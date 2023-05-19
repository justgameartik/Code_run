#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <deque>

int main() {
    std::string s, c;
    std::cin >> s >> c;

    std::unordered_set<char> need;
    int need_size = c.size();
    for (int i = 0; i < need_size; i++) 
        need.insert(c[i]);

    int min_len = s.size() + 1;
    std::unordered_map<char, int> dict;
    std::deque<int> indexes;
    std::unordered_set<int> to_delete;
    for (int i = 0; i < s.size(); i++) {
        if (need.find(s[i]) != need.end()) {
            if (dict.find(s[i]) != dict.end()) {
                to_delete.insert(dict[s[i]]);
            }

            dict[s[i]] = i;
            indexes.push_back(i);

            while(to_delete.find(indexes.front()) != to_delete.end())
                indexes.pop_front();

            int cur_len = indexes.back() - indexes.front() + 1;
            if (dict.size() == need_size && cur_len < min_len)
                min_len = cur_len;
        }
        else {
            std::unordered_map<char,int> temp; std::deque<int> temp_deque;
            dict = temp; indexes = temp_deque;
        }
    }

    if (min_len == s.size() + 1)
        min_len = 0;

    std::cout << min_len;
}