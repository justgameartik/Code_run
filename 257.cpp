#include <iostream>
#include <vector>
#include <string>
#include <vector>
#include <utility>
#include <sstream>

int main() {
    std::string s;
    std::cin >> s;

    std::vector<int> str;
    char ch; int amount = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] - 'a' >= 0 && s[i] - 'a' < 26) {
            ch = s[i];

            if (amount == 0)
                amount = 1;
            str.push_back(amount);

            amount = 0;
        }
        else {
            amount = amount*10 + (s[i] - '0');
        }
    }

    std::vector<long long> pref_sum(str.size()+1);
    pref_sum[0] = 0;
    for (int i = 0; i < str.size(); i++) {
        pref_sum[i+1] = pref_sum[i] + str[i];
    }

    std::vector<int> pref_len_of_substr(str.size()+1);
    pref_len_of_substr[0] = 0;
    for (int i = 1; i < pref_sum.size(); i++) {
        int num = pref_sum[i] - pref_sum[i-1];
        int cur_len = 0;

        if (num != 1) {
            std::stringstream ss;
            ss << num;
            std::string cur_str;
            ss >> cur_str;
            cur_len = cur_str.size();
        }

        pref_len_of_substr[i] = pref_len_of_substr[i-1] + cur_len + 1;
    }

    int q; std::cin >> q;
    for (int j = 0; j < q; j++) {
        long long left, right;
        std::cin >> left >> right;
        left -= 1;

        size_t l=0, r=pref_sum.size()-1;
        while(l < r) { // первый индекс prefix_sum, где больше left 
            size_t m = (l+r)/2;

            if (pref_sum[m] > left) {
                r = m;
            }
            else {
                l = m+1;
            }
        }

        size_t l_2 = 0, r_2 = pref_sum.size() - 1;
        while(l_2 < r_2) {
            size_t m = (l_2+r_2+1)/2;

            if (pref_sum[m] < right) {
                l_2 = m;
            }
            else {
                r_2 = m - 1;
            }
        }
        int len = 0;
        if (l <= l_2) {
            len += pref_len_of_substr[l_2] - pref_len_of_substr[l];
        
            {
                int cur_num = pref_sum[l] - left;
                int cur_len = 0;
                std::stringstream ss;
                
                if (cur_num != 1) {
                    std::stringstream ss;
                    ss << cur_num;
                    std::string cur_str;
                    ss >> cur_str;
                    cur_len = cur_str.size();
                }

                len += cur_len + 1;
            }
            {
                int cur_num = right - pref_sum[l_2];
                int cur_len = 0;
                std::stringstream ss;
                
                if (cur_num != 1) {
                    std::stringstream ss;
                    ss << cur_num;
                    std::string cur_str;
                    ss >> cur_str;
                    cur_len = cur_str.size();
                }

                len += cur_len + 1;
            }
        }
        else {
            int cur_num = right - left;
            int cur_len = 0;
            std::stringstream ss;
            
            if (cur_num != 1) {
                std::stringstream ss;
                ss << cur_num;
                std::string cur_str;
                ss >> cur_str;
                cur_len = cur_str.size();
            }

            len += cur_len + 1;
        }

        std::cout << len << '\n';
    }
    
}