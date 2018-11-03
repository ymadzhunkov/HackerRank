#include "problem.h"
#include <iostream>

Problem::Problem(std::vector<std::string> &&genes,
            std::vector<int> &&health)
        : genes(std::move(genes)),
          health(std::move(health)) {}

int64_t Problem::sum_health(const int from, const int to,
                            const std::string &dna) const {
    int64_t res = 0;
    for (size_t i = 0; i < dna.size(); i++)
        for (int j = from; j <= to; j++)
            if (dna.compare(i, genes[j].size(), genes[j]) ==
                0)
                res += health[j];
    return res;
}
