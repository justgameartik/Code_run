#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> seller(n), buyer(m);
    for (int i = 0; i < n; i++)
        std::cin >> seller[i];
    for (int i = 0; i < m; i++)
        std::cin >> buyer[i];

    sort(seller.begin(), seller.end());
    sort(buyer.begin(), buyer.end(), std::greater<int>());
    
    int ptr = 0;
    long long sum = 0;
    while(ptr < n && ptr < m && buyer[ptr] - seller[ptr] > 0) {
        sum += buyer[ptr] - seller[ptr];
        ptr += 1;
    }

    std::cout << sum;
}