#pragma once
#include <array>
#include <string>
#include <vector>
#include "CyclicHash.h"

class Problem {
  public:
    Problem(std::vector<std::string> &&genes,
            std::vector<int> &&health);

    int64_t sum_health(const int from, const int to,
                       const std::string &dna) ;

  private:
    int64_t sum_small(const int from, const int to,
                      const std::string &dna);
    bool match (const int ind, const char * dna) const;
    bool add(int key, int val);
    uint32_t check(uint32_t hash, const char *dna,
                   const int from, const int to) const;
    std::vector<std::string> genes;
    std::vector<int> health;
    std::array<int, 1 << 20> table;
    std::vector<int> small;
    CyclicHash hf;
};
