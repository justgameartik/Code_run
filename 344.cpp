#include <iostream>
#include <vector>
#include <string>

int main() {
    int n, m;
    std::cin >> n >> m;

    int w, b;
    std::cin >> w;
    std::vector<std::vector<int>> table(n+1, std::vector<int>(m+1, -1));
    for (int i = 0; i < w; i++) {
        int x, y; std::cin >> x >> y;
        table[x][y] = 0;
    }
    std::cin >> b;
    for (int i = 0; i < b; i++) {
        int x, y; std::cin >> x >> y;
        table[x][y] = 1;
    }

    int turn = 1, opp;
    std::string s; std::cin >> s;
    if (s[0] == 'w')
        turn = 0;
    opp = (turn+1)%2;

    std::vector<std::vector<int>> dx = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
    bool res = false;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int k = 0; k < dx.size(); k++) {

                int cur_x = i+dx[k][0], cur_y = j+dx[k][1];
                int next_x = i+dx[k][0]*2, next_y = j+dx[k][1]*2;

                if (next_x < 1 || next_x > n || next_y < 1 || next_y > m)
                    continue;

                if (table[i][j] == turn && table[i][j] + table[cur_x][cur_y] == 1 && table[next_x][next_y] == -1)
                    res = true;
            }
        }
    }

    if (res)
        std::cout << "Yes";
    else
        std::cout << "No";
}



/*
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

int main() {
    int n, m;
    std::cin >> n >> m;

    int amount[2];
    std::vector<std::unordered_map<int, std::unordered_set<int>>> figure(2);
    for (int i = 0; i < 2; i++) {
        std::cin >> amount[i];
        for (int j = 0; j < amount[i]; j++) {
            int x, y; std::cin >> x >> y;
            figure[i][x].insert(y);
        }
    }

    std::string s;
    std::cin >> s;
    int turn, opp;
    switch(s[0]) {
        case 'w':
            turn = 0;
            break;
        case 'b':
            turn = 1;
            break;
    }
    opp = (turn+1)%2;

    std::vector<std::vector<int>> dx = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

    std::unordered_map<int, std::unordered_set<int>>::iterator it;
    bool res = false;
    for (it = figure[turn].begin(); it != figure[turn].end(); it++) {
        std::unordered_set<int>::iterator y_it;
        for (y_it = it->second.begin(); y_it != it->second.end(); y_it++) {
            for (int i = 0; i < 4; i++) {
                int cur_x = it->first + dx[i][0], cur_y = *y_it + dx[i][1];
                int next_x = it->first + 2*dx[i][0], next_y = *y_it + 2*dx[i][1];
                if (next_x < 1 || next_x > n || next_y < 0 || next_y > m)
                    continue;
                
                std::unordered_map<int, std::unordered_set<int>>::iterator find_it = figure[opp].find(cur_x),
                    next_find_opp_it = figure[opp].find(next_x), next_find_turn_it = figure[turn].find(next_x);
                
                bool opp_neig = find_it != figure[opp].end() && find_it->second.find(cur_y) != find_it->second.end();
                bool next_clear = next_find_opp_it == figure[opp].end() ||
                        next_find_opp_it->second.find(next_y) == next_find_opp_it->second.end();
                next_clear += next_find_turn_it == figure[turn].end() ||
                        next_find_turn_it->second.find(next_y) == next_find_turn_it->second.end();
                
                if (opp_neig && next_clear)
                    res = true;
            }
        }
    }

    if (res)
        std::cout << "Yes";
    else
        std::cout << "No";
}
*/