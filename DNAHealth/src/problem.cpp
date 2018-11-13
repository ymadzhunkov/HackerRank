#include "problem.h"
#include <cstring>
#include <iostream>

Problem::Problem(std::vector<std::string> &&genes_,
                 std::vector<int> &&health_)
    : genes(std::move(genes_)), health(std::move(health_)),
      table(*new (std::array<SumTree, 1 << 20>)),
      hf(4, 20) {
    for (int i = 0; i < genes.size(); i++) {
        if (genes[i].size() >= 4)
            add_big(i);
        else
            add_small(i);
    }
}

bool Problem::check_add_big(int key, int val) const {
    if (table[key].is_empty()) return true;
    if (match(table[key].sample(), genes[val].c_str()))
        return true;
    return false;
}

bool Problem::add_big(int key, int val) {
    bool res = check_add_big(key, val);
    if (res) table[key].add(val, health[val]);
    return res;
}

bool Problem::add_big(int val) {
    auto key = hf.init(genes[val].c_str());
    for (size_t i = key; i < table.size(); i++)
        if (add_big(i, val)) return true;
    for (size_t i = 0; i < key; i++)
        if (add_big(i, val)) return true;
    return false;
}

int Problem::code_small(const std::string &gene) const {
    int index = gene[0] - 'a';
    index *= 27;
    if (gene.length() > 1) index += 1 + gene[1] - 'a';
    index *= 27;
    if (gene.length() > 2) index += 1 + gene[2] - 'a';
    return index;
}

bool Problem::add_small(int i) {
    int code = code_small(genes[i]);
    small_table[code].add(i, health[i]);
}

uint32_t next(const uint32_t v) {
    return (v + 1) & ((1 << 20) - 1);
}

uint32_t Problem::check(uint32_t hash, const char *dna,
                        const int from,
                        const int to) const {

    uint32_t res = 0;
    for (; !table[hash].is_empty(); hash = next(hash)) {
        auto h = table[hash].sum_range(from, to);
        if (h > 0)
            if (match(table[hash].sample(), dna)) res += h;
    }
    return res;
}

bool Problem::match(const int ind, const char *dna) const {
    return strncmp(genes[ind].c_str(), dna,
                   genes[ind].length()) == 0;
}

void Problem::feed(const char c, const int from,
                   const int to, int64_t &res) {
    if (p2 != '\0') {
        int index = p2 - 'a';
        index *= 27;
        index += 1 + p1 - 'a';
        index *= 27;
        index += 1 + c - 'a';
        res += small_table[index].sum_range(from, to);
    }
    if (p1 != '\0') {
        int index = p1 - 'a';
        index *= 27;
        index += 1 + c - 'a';
        index *= 27;
        res += small_table[index].sum_range(from, to);
    }
    {
        int index = c - 'a';
        index *= 27 * 27;
        res += small_table[index].sum_range(from, to);
    }
    p2 = p1;
    p1 = c;
}

int64_t Problem::sum_health(const int from, const int to,
                            const std::string &dna) {

    p1 = '\0';
    p2 = '\0';
    int64_t res = 0;
    if (dna.length() >= 4) {
        auto v = hf.init(dna.c_str());
        for (size_t i = 0; i < dna.length() - 4; i++) {
            feed(dna[i], from, to, res);
            res += check(v, &dna[i], from, to);
            v = hf.update(dna[i], dna[i + 4]);
        }
        res += check(v, &dna[dna.length() - 4], from, to);
    }
    for (size_t i = dna.length() - 4; i < dna.length(); i++)
        feed(dna[i], from, to, res);
    return res;
}
