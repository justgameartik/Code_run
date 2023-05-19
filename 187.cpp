#include <iostream>
#include <vector>
#include <set>

int main() {
    int T; std:: cin >> T;
    
    for (int i = 0; i < T; i++) {        
        int n; std::cin >> n;
        
        std::multiset<int> tree;
        for (int j = 0; j < n; j++) {
            int a; std::cin >> a;

            tree.insert(a);
        }

        std::multiset<int>::iterator it = next(tree.begin(), 1);
        int min = 2000000000;
        for (it; it != tree.end(); it++) {
            std::multiset<int>::iterator sec_it = next(it, -1);

            int xor_o = *it ^ *sec_it;
            if (xor_o < min)
                min = xor_o;
        }

        std::cout << min << '\n';
    }
}