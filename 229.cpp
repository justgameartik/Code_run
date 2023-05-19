#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include <set>
#include <unordered_set>

bool comp(std::pair<long long, size_t>& a, std::pair<long long, size_t>& b) {
    if (a.first < b.first || a.first == b.first && a.second < b.second)
        return true;
    
    return false;
}

int main() {
    
    int n; std::cin >> n;
    std::vector<std::vector<long long>> useful(n, std::vector<long long>(2));
    std::vector<bool> type_use(n);
    for (int i = 0; i < n; i++)
        std::cin >> useful[i][0];
    for (int i = 0; i < n; i++)
        std::cin >> useful[i][1];

    std::vector<std::pair<long long, size_t>> dev_over_manage(n);
    for (int i = 0; i < n; i++) {
        dev_over_manage[i] = std::make_pair(useful[i][0] - useful[i][1], i);
    }

    sort(dev_over_manage.begin(), dev_over_manage.end(), comp);

    long long sum = 0;

    std::unordered_set<size_t> managers, devs;
    std::map<long long, std::set<size_t>> diff_manage, diff_dev;
    for (int i = 0; i < n/2; i++) {
        size_t cur_i = dev_over_manage[i].second;
        sum += useful[cur_i][1];
        managers.insert(cur_i);
        diff_manage[dev_over_manage[i].first].insert(cur_i);
    }
    for (int i = n/2; i < n; i++) {
        size_t cur_i = dev_over_manage[i].second;
        sum += useful[cur_i][0];
        devs.insert(cur_i);
        diff_dev[dev_over_manage[i].first].insert(cur_i);
    }

    int m; std::cin >> m;
    for (int i = 0; i < m; i++) {
        size_t num; int type, add;
        std::cin >> num >> type >> add;
        num -= 1; type -= 1;

        long long prev_diff = useful[num][0] - useful[num][1]; 
        useful[num][type] += add;
        long long cur_diff = useful[num][0] - useful[num][1];

        bool change_type = false;
        if (managers.find(num) != managers.end()) {
            if (type == 1)
                sum += add;
            else {
                size_t dev_min_i = *(diff_dev.begin()->second.begin());
                long long dev_min_diff = diff_dev.begin()->first;

                if (cur_diff > dev_min_diff || cur_diff == dev_min_diff && num > dev_min_i) {
                    sum += useful[num][0] - useful[num][1];
                    sum -= useful[dev_min_i][0] - useful[dev_min_i][1];
                    change_type = true;

                    devs.erase(dev_min_i);
                    diff_dev[dev_min_diff].erase(dev_min_i);
                    if (diff_dev[dev_min_diff].empty())
                        diff_dev.erase(dev_min_diff);
                    
                    managers.insert(dev_min_i);
                    diff_manage[dev_min_diff].insert(dev_min_i);
                }
            }

            diff_manage[prev_diff].erase(num);
            if (diff_manage[prev_diff].empty())
                diff_manage.erase(prev_diff);

            if (change_type) {
                managers.erase(num);
                devs.insert(num);
                diff_dev[cur_diff].insert(num);
            }else {
                diff_manage[cur_diff].insert(num);
            }
        }
        else {
            if (type == 0)
                sum += add;
            else {
                size_t manage_max_i = *next(next(diff_manage.end(),-1)->second.end(), -1);
                long long manage_max_diff = next(diff_manage.end(),-1)->first;

                if (cur_diff < manage_max_diff || cur_diff == manage_max_diff && num < manage_max_i) {
                    sum += useful[num][1] - useful[num][0];
                    sum -= useful[manage_max_i][1] - useful[manage_max_i][0];
                    change_type = true;

                    managers.erase(manage_max_i);
                    diff_manage[manage_max_diff].erase(manage_max_i);
                    if (diff_manage[manage_max_diff].empty())
                        diff_manage.erase(manage_max_diff);

                    devs.insert(manage_max_i);
                    diff_dev[manage_max_diff].insert(manage_max_i);
                }
            }

            diff_dev[prev_diff].erase(num);
            if (diff_dev[prev_diff].empty())
                diff_dev.erase(prev_diff);

            if (change_type) {
                devs.erase(num);
                managers.insert(num);
                diff_manage[cur_diff].insert(num);
            }
            else
                diff_dev[cur_diff].insert(num);
        }

        std::cout << sum << '\n';
    }
}