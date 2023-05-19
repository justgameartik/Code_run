#include <iostream>
#include <vector>
#include <math.h>

int main() {
    long long x, y, a = 2;
    std::cin >> x >> y;

    if (y % x == 0) {
        int count = 0;
        long long n = y / x;

        while(a*a <= n) {
            if (n % a == 0) {
                while(n % a == 0) 
                    n /= a;
                count += 1;
            }
            a += 1;
        }
        if (n > 1)
            count += 1;

        std::cout << pow(2, count);
    }
    else {
        std::cout << 0;
    }
}