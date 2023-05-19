#include <iostream>
#include <vector>

int main() {
    int n; std::cin >> n;
    std::vector<int> server(n);

    int err_amount = 0;
    for (int i = 0; i < n; i++) {
        int a, b;
        std::cin >> a >> b;

        int temp = a*b;
        server[i] = temp;
        err_amount += temp;
    }

    std::cout << std::fixed;
    std::cout.precision(12);
    std::vector<double> error(n);
    for (int i = 0; i < n; i++) {
        error[i] = double(server[i]) / err_amount;
        std::cout << error[i] << '\n'; 
    }
}