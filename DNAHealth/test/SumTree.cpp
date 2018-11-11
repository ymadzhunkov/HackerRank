#include "SumTree.h"
#include <parts/doctest_fwd.h>
#include <limits>

TEST_CASE("Test sum with zero element") {
    SumTree s;
    REQUIRE(s.sum(std::numeric_limits<int>::max()) == 0);
}

TEST_CASE("Test sum with one element") {
    SumTree s;
    s.add(2, 10);
    REQUIRE(s.sum(2) == 10);
    REQUIRE(s.sum(1) == 0);
}

TEST_CASE("Test sum with two elements") {
    SumTree s;
    s.add(2, 10);
    s.add(6, 12);
    REQUIRE(s.sum(1) == 0);
    REQUIRE(s.sum(2) == 10);
    REQUIRE(s.sum(6) == 22);
}

TEST_CASE("Test sum_range with two elements") {
    SumTree s;
    s.add(2, 10);
    s.add(6, 12);
    REQUIRE(s.sum_range(-10, 1) == 0);
    REQUIRE(s.sum_range(1, 3) == 10);
    REQUIRE(s.sum_range(1, 10) == 22);
    REQUIRE(s.sum_range(5, 6) == 12);
    REQUIRE(s.sum_range(6, 6) == 12);
}
