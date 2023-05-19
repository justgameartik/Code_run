#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

int main() 
{
    std::string a, b;
    std::cin >> a >> b;
    
    std::unordered_set<char> treasure;
    for (int i = 0; i < a.size(); i++)
        treasure.insert(a[i]);

    int res = 0;
    for (int i = 0; i < b.size(); i++)
    {
        if (treasure.find(b[i]) != treasure.end())
            res += 1;
    }

    std::cout << res;

	return 0;
}