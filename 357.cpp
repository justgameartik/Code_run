#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <unordered_set>

int main() {
    int T; std::cin >> T;

    std::string word;
    std::unordered_map<std::string, int> e;
    std::unordered_set<std::string> v;
    for (int i = 0; i < T; i++) {
        std::cin >> word;

        std::string first, second;
        for (int j = 0; j < word.size() - 3; j++) {
            first = {word[j], word[j+1], word[j+2]};
            second = {word[j+1], word[j+2], word[j+3]};
            v.insert(first);
            v.insert(second);

            std::string total = first.append(second);
            e[total] += 1;
        } 
    }

    std::cout << v.size() << '\n' << e.size() << '\n';
    std::unordered_map<std::string,int>::iterator it = e.begin();
    for (it; it != e.end(); it++)
        std::cout << it->first.substr(0, 3) << ' ' << it->first.substr(3, 3) << ' ' << it->second << '\n';
}