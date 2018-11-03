#pragma once

class Range {
  public:
    Range() : min(0), max(0) {}
    Range &add(int64_t v) {
        if (v < min) min = v;
        if (v > max) max = v;
        return *this;
    }
    int64_t min, max;
};
