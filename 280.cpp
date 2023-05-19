#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>

int main() {
    int n; std::cin >> n;

    std::vector<std::pair<int, int>> poddon(n);
    for (size_t i = 0; i < n; i++) {
        int w, h; std::cin >> w >> h;
        
        if (h > w) {
            int temp = h;
            h = w;
            w = temp;
        }

        poddon[i] = {w, h};
    }
    std::sort(poddon.begin(), poddon.end());

    std::vector<std::pair<int, int>> max_len(n);
    std::pair<int, int> max = {0, 0}, prev_max = max;
    int cur_max = 0;
    for (size_t i = n; i > 0; i--) {
        if (poddon[i-1].first != max.first)
            max_len[i-1] = max;
        else
            max_len[i-1] = prev_max;
        
        cur_max = std::max(cur_max, poddon[i-1].second);
        if (poddon[i-1].second > max.second && poddon[i-1].first != max.first) {
            prev_max = max;
            max = std::make_pair(poddon[i-1].first, cur_max);
        }
    }

    int count = 0;
    for (size_t i = 0; i < n; i++) {
        if (poddon[i].second >= max_len[i].second) {
            count += 1;
        }
    }
    
    std::cout << count;
}