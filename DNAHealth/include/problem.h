#pragma once
#include <array>
#include <string>
#include <vector>
#include "CyclicHash.h"
#include "SumTree.h"

class Problem {
  public:
    Problem(std::vector<std::string> &&genes,
            std::vector<int> &&health);

    int64_t sum_health(const int from, const int to,
                       const std::string &dna) ;

  private:
    bool match (const int ind, const char * dna) const;
    bool add_big(int val);
    bool add_big(int key, int val);
    bool add_small(int val);
    uint32_t check(uint32_t hash, const char *dna,
                   const int from, const int to) const;
    int code_small(const std::string & gene) const;
    std::vector<std::string> genes;
    std::vector<int> health;
    std::array<int, 1 << 20> table;
    std::array<SumTree, 26 * 27 * 27> small_table;
    CyclicHash hf;
    void feed(const char c);
    void feed(const char c, const int from, const int to,
              int64_t &res);
    char p1, p2;
};
