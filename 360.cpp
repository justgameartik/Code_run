#include <iostream>
#include <unordered_map>

int main() {
    int n; std::cin >> n;
    std::unordered_map<int, int> numbers;
    for (int i = 0; i < n; i++) {
        int cur; std::cin >> cur;
        numbers[cur] += 1;
    }

    int max_num = -1, max_amount = 0;
    std::unordered_map<int, int>::iterator it = numbers.begin();
    for (it; it != numbers.end(); it++) {
        if (it->second >= max_amount) {
            if (it->second == max_amount && it->first < max_num)
                continue;
            
            max_num = it->first;
            max_amount = it->second;
        }
    }

    std::cout << max_num;
}