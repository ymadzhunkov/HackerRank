#include "problem.h"
#include <iostream>
#include <cstring>

Problem::Problem(std::vector<std::string> &&genes_,
                 std::vector<int> &&health_)
    : genes(std::move(genes_)), health(std::move(health_)),
      hf(4, 20) {
    for (auto &v : table) v = -1;
    for (int i = 0; i < genes.size(); i++) {
        if (genes[i].size() >= 4)
            add(hf.init(genes[i].c_str()), i); 
        else 
            small.push_back(i);
    }
}

bool Problem::add(int key, int val) {
    for (size_t i = key; i < table.size(); i++)
        if (table[i] < 0) {
            table[i] = val;
            return true;
        }
    for (size_t i = 0; i < key; i++)
        if (table[i] < 0) {
            table[i] = val;
            return true;
        }
    return false;
}

uint32_t next(const uint32_t v) {
    return (v + 1) & ((1 << 20) - 1);
}

uint32_t Problem::check(uint32_t hash, const char *dna,
                        const int from,
                        const int to) const {
    uint32_t res = 0;
    if (table[hash] >= 0) {
        for (auto j = table[hash]; j >= 0;
             j = table[(hash = next(hash))]) {
            if (j >= from && j <= to) {
                if (match(j, dna))
                    res += health[j];
            }
        }
    }
    return res;
}

bool Problem::match(const int ind, const char *dna) const {
    return strncmp(genes[ind].c_str(), dna,
                   genes[ind].length()) == 0;
}

int64_t Problem::sum_small(const int from, const int to,
                           const std::string &dna) {
    int64_t res = 0;
    for (size_t i = 0; i < dna.length(); i++)
        for (const auto &ind : small)
            if (ind >= from && ind <= to) {
                if (match(ind, &dna[i]))
                    res += health[ind];
            }
    return res;
}

int64_t Problem::sum_health(const int from, const int to,
                            const std::string &dna) {

    int64_t res = 0;
    if (dna.length() >= 4) {
        auto v = hf.init(dna.c_str());
        for (size_t i = 0; i < dna.length() - 4; i++) {
            res += check(v, &dna[i], from, to);
            v = hf.update(dna[i], dna[i + 4]);
        }
        res += check(v, &dna[dna.length() - 4], from, to);
    }
    res += sum_small(from, to, dna);
    return res;
}
