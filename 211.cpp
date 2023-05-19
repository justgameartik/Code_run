#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <utility>
using namespace::std;

bool check_name_on_cross(vector<pair< pair<int, int>, pair<unordered_set<string>, vector<string>> >>* day,
    string name, pair<int, int> time, vector<string>* bad_names) 
{
    
    bool cross = false;

    for (int i = 0; i < day->size(); i++) {
        bool cross_meeting = time.first > day->at(i).first.first && time.first < day->at(i).first.second ||
            time.second > day->at(i).first.first && time.second < day->at(i).first.second ||
            time.first <= day->at(i).first.first && time.second > day->at(i).first.first;

        if (cross_meeting && day->at(i).second.first.find(name) != day->at(i).second.first.end()) {
            cross = true;
            bad_names->push_back(name);
        }
    }

    return cross;
}

bool comp(pair< pair<int, int>, pair<unordered_set<string>, vector<string>> > a,
    pair< pair<int, int>, pair<unordered_set<string>, vector<string>> > b)
{
    return a.first.first < b.first.first;
}

int main() {

    vector<vector<pair< pair<int, int>, pair<unordered_set<string>, vector<string>> >>> table(366);    
    int n; cin >> n;
    
    string line = "";
    getline(cin, line);
    for (int i = 0; i < n; i++) {
        getline(cin, line);
        
        stringstream ss(line);
        string command;
        ss >> command;

        if (command[0] == 'A') {
            int day, duration, k; string time_beg_str;
            ss >> day >> time_beg_str >> duration >> k;
            int time_beg = stoi(time_beg_str.substr(0, 2)) * 60 + stoi(time_beg_str.substr(3, 2));
            pair<int, int> time = {time_beg, time_beg + duration};

            vector<string> name(k);
            bool cross = false;
            vector<string> bad_names;
            for (int j = 0; j < k; j++) {
                ss >> name[j];

                for (int l = 0; l < table[day].size(); l++) {
                    cross += check_name_on_cross(&table[day], name[j], time, &bad_names);
                }
            }

            unordered_set<string> name_set;
            if (!cross) {
                cout << "OK\n";
                for (int j = 0; j < k; j++) {
                    name_set.insert(name[j]);
                }
                table[day].push_back(make_pair( time, make_pair(name_set, name) ));
            } 
            else {
                cout << "FAIL\n";
                for (int j = 0; j < bad_names.size(); j++) {
                    if (name_set.find(bad_names[j]) == name_set.end())
                        cout << bad_names[j] << ' ';

                    name_set.insert(bad_names[j]);
                }
                cout << '\n';
            }
        }

        if (command[0] == 'P') {
            int day; string name;
            ss >> day >> name;

            sort(table[day].begin(), table[day].end(), comp);
            for (int j = 0; j < table[day].size(); j++) {
                if (table[day][j].second.first.find(name) != table[day][j].second.first.end()) {
                    printf("%02d:%02d", table[day][j].first.first / 60, table[day][j].first.first % 60);
                    cout << ' ' << table[day][j].first.second - table[day][j].first.first;
                    
                    for (int l = 0; l < table[day][j].second.second.size(); l++) {
                        cout << ' ' << table[day][j].second.second[l];
                    }
                    cout << '\n';
                }
            }
        }
    }
}