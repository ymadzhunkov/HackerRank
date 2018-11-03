#pragma once
#include <cstdint>

class Range {
  public:
    Range() : min(INT64_MAX), max(INT64_MIN) {}
    Range &add(int64_t v) {
        if (v < min) min = v;
        if (v > max) max = v;
        return *this;
    }
    int64_t min, max;
};
