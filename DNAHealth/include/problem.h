#pragma once
#include <vector>
#include <string>

class Problem {
    std::vector<std::string> genes;
    std::vector<int> health;

    int64_t sum_health(const int from, const int to,
                       const std::string dna) const;
};
