#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
#include <math.h>

long double add(long double left, long double right, int a, int b, int c) {
    return abs(a*(pow(right,3) - pow(left,3))/3 + b*(pow(right,2) - pow(left,2))/2 + c*(right - left));
}

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> l(n+1), r(m+1);
    std::map<int, std::vector<int>> coeff_l, coeff_r;
    for (size_t i = 0; i < n+1; i++) {
        int temp;
        std::cin >> temp;
        l[i] = temp;
    }
    for (size_t i = 0; i < n; i++) {
        int a, b, c;
        std::cin >> a >> b >> c;
        coeff_l[l[i+1]] = {a, b, c};
    }

    for (size_t i = 0; i < m+1; i++) {
        int temp;
        std::cin >> temp;
        r[i] = temp;
    }
    for (size_t i = 0; i < m; i++) {
        int a, b, c;
        std::cin >> a >> b >> c;
        coeff_r[r[i+1]] = {a, b, c};
    }

    size_t l_index = 0, r_index = 0;
    int left = std::max(l[0], r[0]);
    int mx = std::min(l[n], r[n]);

    while(l_index < l.size() && l[l_index] <= left) {
        l_index += 1;
    }
    while(r_index < r.size() && r[r_index] <= left) {
        r_index += 1;
    }

    long double S = 0;
    int right = std::min(l[l_index], r[r_index]);
    while(l_index < l.size() && r_index < r.size() && right <= mx) {
        int a = coeff_l[l[l_index]][0] - coeff_r[r[r_index]][0],
            b = coeff_l[l[l_index]][1] - coeff_r[r[r_index]][1],
            c = coeff_l[l[l_index]][2] - coeff_r[r[r_index]][2];
        
        if (a != 0) {
            long double D = b*b-4*a*c;
            if (D <= 0)        
                S += add(left, right, a, b, c);
            else {
                long double x1 = (-b - std::sqrt(D))/(2*a),
                    x2 = (-b + std::sqrt(D))/(2*a);

                if (left >= x1 && right <= x2 || left >= x2 || right <= x1) {
                    S += add(left, right, a, b, c);
                }
                else if (left <= x1 && right <= x2 || left >= x1 && right >= x2) {
                    if (left <= x1){
                        S += add(left, x1, a, b, c);
                        S += add(x1, right, a, b, c);
                    }
                    else {
                        S += add(left, x2, a, b, c);
                        S += add(x2, right, a, b, c);
                    }
                }
                else if (left <= x1 && right >= x2) {
                    S += add(left, x1, a, b, c);
                    S += add(x1, x2, a, b, c);
                    S += add(x2, right, a, b, c);
                }
            }
        }
        else if (b != 0) {
            long double d_c = c;
            long double x = -d_c/b;

            if (left <= x && right <= x || left >= x && right >= x)
                S += add(left, right, a, b, c);
            else {
                S += add(left, x, a, b, c);
                S += add(x, right, a, b, c);
            }
        }
        else {
            S += add(left, right, a, b, c);
        }

        if (l[l_index] < r[r_index]) {
            l_index += 1;
        }
        else if (r[r_index] < l[l_index]) {
            r_index += 1;
        }
        else if (r[r_index] == l[l_index]) {
            r_index += 1;
            l_index += 1;
        }
        left = right;
        right = std::min(l[l_index], r[r_index]);
    }

    std::cout << std::fixed;
    std::cout.precision(6);
    std::cout << S;
}