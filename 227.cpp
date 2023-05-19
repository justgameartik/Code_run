#include <iostream>

bool check(long long m, long long count, long long cur_amount) {
    long long sum = (2*count + m + 1) * m / 2;

    if (cur_amount < sum)
        return false;
    return true;
}

long long add_days(int d, long long left_s) {
    d -= 1;
    long long week_amount = left_s/7;
    int day_amount = left_s % 7;

    if (d+day_amount == 6) // 1 021 737
        day_amount -= 1;
    else if (d + day_amount > 6)
        day_amount -= 2;

    if (d % 6 == 0 &&  d != 0)
        day_amount += 1;
    
    return week_amount*5+day_amount; // d=6;day_amount=2;left_s=2; 1 2 3 4 5 6    7 1 
}

int main() {
    int k, m, d;
    std::cin >> k >> m >> d;

    long long cur_amount = m;
    long long count = 0;
    
    while(cur_amount >= 0) {
        long long left_s = 1, right_s = (cur_amount)/(count+1) + 1;
        while(left_s < right_s) {
            long long temp = (left_s + right_s) / 2;

            if (check(temp, count, cur_amount))
                left_s = temp + 1;
            else
                right_s = temp;
        }

        cur_amount -= (2*count + left_s + 1)*left_s/2;
        cur_amount += add_days(d, left_s) * k;
        count += left_s;
        d = (d+left_s) % 7;
        if (d == 0)
            d = 7;
    }

    std::cout << count-1;
}