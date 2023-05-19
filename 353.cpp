#include <iostream>
#include <string>
#include <functional>
#include <algorithm>
#include <vector>

#include <curl/curl.h>
#include "json.hpp"
using json = nlohmann::json;

std::string data;

size_t writeCallback(char* buf, size_t size, size_t nmemb, void* up) {
    for (int c = 0; c < size * nmemb; ++c)
    {
        data.push_back(buf[c]);
    }
    return size * nmemb;
}

int main() {
    std::string host, port, a, b;
    std::cin >> host >> port >> a >> b;

    const std::string url = host + ":" + port + "/?a=" + a + "&b=" + b;
    curl_global_init(CURL_GLOBAL_ALL);
    
    CURL* curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    std::vector<int> values;

    auto jData = json::parse(data);
    for (json::iterator it = jData.begin(); it != jData.end(); ++it) {
        if (*it > 0) {
            values.push_back(*it);
        }
    }

    sort(values.begin(), values.end(), std::greater<int>());
    for (int value : values) {
        std::cout << value << '\n';
    }

    curl_global_cleanup();

    return 0;
}