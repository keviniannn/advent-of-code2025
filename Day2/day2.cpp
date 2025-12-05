
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

std::vector<std::pair<long long, long long>> example = {
    {11, 22},
    {95, 115},
    {998, 1012},
    {1188511880, 1188511890},
    {222220, 222224},
    {1698522, 1698528},
    {446443, 446449},
    {38593856, 38593862}
};

std::vector<std::pair<long long, long long>>
get_ranges(const std::string& path) {
    std::ifstream in(path);
    if (!in) throw std::runtime_error("cannot open " + path);

    std::string line;
    std::getline(in, line);

    std::vector<std::pair<long long, long long>> ranges;
    std::stringstream ss(line);
    std::string token;

    while (std::getline(ss, token, ',')) {
        const auto dash = token.find('-');
        if (dash == std::string::npos) continue;

        const long long first = std::stoll(token.substr(0, dash));
        const long long last = std::stoll(token.substr(dash + 1));
        ranges.emplace_back(first, last);
    }

    return ranges;
}

// two pointer helper
bool is_invalid(long long id) {
    std::string sid = std::to_string(id); // convert id to string
    int n = sid.size();

    // only non-negative even lengthed ids can be invalid
    if (id < 0 || n % 2 != 0) return false;

    int l = 0;
    int r = static_cast<int>(n / 2); // middle

    while (r < n) {
        if (sid[l] != sid[r]) return false; // id is valid
        ++l;
        ++r;
    }

    return true; // invalid id
}

// get invalid ids and store in array
std::vector<long long>
get_invalid_ids(const std::vector<std::pair<long long, long long>>& ranges) {
    std::vector<long long> invalid_ids;

    for (const auto& pair: ranges) {
        long long first = pair.first;
        long long last = pair.second;
        if (is_invalid(first)) {
            invalid_ids.push_back(first++);
        }
        if (is_invalid(last)) {
            invalid_ids.push_back(last--);
        }
        for (long long i = first; i < last; ++i) {
            if (is_invalid(i)) {
                invalid_ids.push_back(i);
            }
        }
    }

    return invalid_ids;
}

// the answer we want
// take in vector of invalid ids and sum them together
long long sum_invalid_ids(const std::vector<long long>& invalid_ids) {
    long long invalid_id_sum = 0;
    for (const auto& id: invalid_ids) {
        invalid_id_sum += id;
    }
    return invalid_id_sum;
}

int main() {
    /*
    std::vector<int> test_arr = get_invalid_ids(example);
    for (const auto& val: test_arr) {
        std::cout << val << '\n';
    }
    */

    std::cout << "should be false: " << is_invalid(123124) << '\n';
    std::cout << "should be true: " << is_invalid(123123) << '\n';

    std::cout << "should be 1227775554: "
        << sum_invalid_ids(get_invalid_ids(example)) << '\n';

    std::vector<std::pair<long long, long long>>
    input = get_ranges("input.txt");

    /*
    for (const auto& val: input) {
        std::cout << val.first << '\n';
        std::cout << val.second << '\n';
    }
    */

    std::cout << "answer: "
        << sum_invalid_ids(get_invalid_ids(input)) << '\n';

    return 0;
}
