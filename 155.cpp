#include <iostream>
#include <unordered_map>

int main() {
    int n; std::cin >> n;
    std::unordered_map<int, int> dict;
    for (int i = 0; i < n; i++) {
        int cur; std::cin >> cur;
        dict[cur] += 1;
    }

    int res = 0;
    std::unordered_map<int, int>::iterator it;
    for (it = dict.begin(); it != dict.end(); it++)
    {
        if (it->second == 1)
            res += 1;
    }

    std::cout << res;
}